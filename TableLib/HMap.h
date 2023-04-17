#pragma once

#include <stdlib.h>
#include "List.h"
#include "Item.h"
#include "IMap.h"

template<class Key, class Data>
class THMap : public IMap<Key, Data>
{
protected:
	TList<TItem<Key, Data>*>* items;
	int Hash(Key* k);
	const int Hash(const Key* k) const;
	int count;
	int size;
public:
	THMap(int s = 100);
	THMap(const THMap<Key, Data>& p);
	~THMap();

	const Data& operator[](Key* k) const;
	Data& operator[](Key* k);
	const void Add(Key* k, Data* d) const;
	void Add(Key* k, Data* d);
	void Delete(Key* k);
	Data& Find(Key* k);
	const Data& Find(Key* k) const;

	int GetCount();
	int GetSize();
};

template<class Key, class Data>
inline int THMap<Key, Data>::Hash(Key* k)
{
	std::hash<Key> i;
	return i(*k) % size;
}

template<class Key, class Data>
inline const int THMap<Key, Data>::Hash(const Key* k) const
{
	std::hash<Key> i;
	return i(*k) % size;
}

template<class Key, class Data>
inline THMap<Key, Data>::THMap(int s)
{
	if (s > 0)
	{
		size = s;
		count = 0;
		items = new TList<TItem<Key, Data>*>[size];
	}
	else
		throw "size < 0";
}

template<class Key, class Data>
inline THMap<Key, Data>::THMap(const THMap<Key, Data>& p)
{
	if (p.items == 0)
	{
		size = 0;
		count = 0;
		items = nullptr;
	}
	else
	{
		size = p.size;
		count = p.count;
		items = new TList<TItem<Key, Data>*>[size];

		for (int i = 0; i < size; i++)
		{
			items[i] = p.items[i];
		}
	}
}

template<class Key, class Data>
inline THMap<Key, Data>::~THMap()
{
	if (items != nullptr)
	{
		for (int i = 0; i < size; i++)
		{
			if (items[i].GetStartNode() != nullptr)
			{
				TListNode<TItem<Key, Data>*>* j = items[i].GetStartNode();
				while (j != nullptr)
				{
					TListNode<TItem<Key, Data>*>* tmp = j;
					j = j->GetNext();
					delete tmp;
				}
				items[i].GetStartNode() = nullptr;
				items[i].GetEndNode() = nullptr;
			}
		}

		delete[] items;
		items = nullptr;
	}
	size = 0;
	count = 0;
}

template<class Key, class Data>
inline const Data& THMap<Key, Data>::operator[](Key* k) const
{
	int i = Hash(k);

	for (int j = 0; j < items[i].GetCount(); j++)
	{
		if (items[i][j]->GetKeyAddress() == k)
		{
			return items[i][j]->GetData();
		}
	}
	throw "err";
}

template<class Key, class Data>
inline Data& THMap<Key, Data>::operator[](Key* k)
{
	int i = Hash(k);

	for (int j = 0; j < items[i].GetCount(); j++)
	{
		if (items[i][j]->GetKeyAddress() == k)
		{
			return items[i][j]->GetData();
		}
	}
	throw "err";
}

template<class Key, class Data>
inline const void THMap<Key, Data>::Add(Key* k, Data* d) const
{
	int i = Hash(k);
	items[i].Push(new TItem<Key, Data>(k, d));
	count++;
}

template<class Key, class Data>
inline void THMap<Key, Data>::Add(Key* k, Data* d)
{
	int i = Hash(k);
	items[i].Push(new TItem<Key, Data>(k, d));
	count++;
}

template<class Key, class Data>
inline void THMap<Key, Data>::Delete(Key* k)
{
	int i = Hash(k);
	int c = items[i].GetCount();
	for (int j = c - 1; j > 0; j--)
	{
		if (items[i][j]->GetKeyAddress() == k)
		{
			if (items[i].GetCount() != 1)
				(items[i]).Del(j);
			else
			{
				items[i].GetStartNode() = nullptr;
				items[i].GetEndNode() = nullptr;
				count = 0;
				break;
			}
			count--;
		}
	}
}

template<class Key, class Data>
inline Data& THMap<Key, Data>::Find(Key* k)
{
	int i = Hash(k);

	for (int j = 0; j < items[i].GetCount(); j++)
	{
		if (items[i][j]->GetKeyAddress() == k)
		{
			return items[i][j]->GetData();
		}
	}
	throw "err";
}

template<class Key, class Data>
inline const Data& THMap<Key, Data>::Find(Key* k) const
{
	int i = Hash(k);

	for (int j = 0; j < items[i].GetCount(); j++)
	{
		if (items[i][j]->GetKeyAddress() == k)
		{
			return items[i][j]->GetData();
		}
	}
	throw "err";
}

template<class Key, class Data>
inline int THMap<Key, Data>::GetCount()
{
	return count;
}

template<class Key, class Data>
inline int THMap<Key, Data>::GetSize()
{
	return size;
}

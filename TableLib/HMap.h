#include "List.h"
#include "Item.h"
#include "IMap.h"

template<class Key, class Data>
class THMap : public IMap<Key, Data>
{
protected:
	TList<TItem<Key, Data*>> items;
	int Hash(const Key& k);
	int count;
	int size;

public:
	THMap(int s = 100);
	THMap(const THMap<Key, Data>& p);
	~THMap();
	Data& operator[](const Key& k);
	void Add(Key* k, Data* d);
	void Delete(const Key& k);
	Data* Find(const Key& k);
};

template<class Key, class Data>
inline int THMap<Key, Data>::Hash(const Key& k)
{
	return 0;
}

template<class Key, class Data>
inline THMap<Key, Data>::THMap(int s)
{
	if (s > 0)
	{
		size = s;
		count = 0;

		items = new TList<TItem<KEy, Data>>[size];
	}
	else
	{
		throw "err";
	}
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
		Titems = new TList<Titem<Key, Data>>[size];

		for (int i = 0; i < size; i++)
		{
			items[i] = p.intems[i];
		}
	}
}

template<class Key, class Data>
inline THMap<Key, Data>::~THMap()
{
	if (items != nullptr)
		delete[] items;
	size = 0;
	cout = 0;
}

template<class Key, class Data>
inline Data& THMap<Key, Data>::operator[](const Key& k)
{
	int i = Hash(k);

	for (int j = 0; j < items[i].count; j++)						// (int j = 0; j < items[i]; count? j++)
	{
		if (items[i][j] == k)
		{
			return intems[i][j].getData();
		}
	}
	throw "err";
}

template<class Key, class Data>
inline void THMap<Key, Data>::Add(Key* k, Data* d)
{
	int i = Hash(k);
	items[i].push_back(new TItems<Key*, Data*>(k, d));
	count++;
}

template<class Key, class Data>
inline void THMap<Key, Data>::Delete(const Key& k)
{
	int i = Hash(k);
	for (int j = 0; j < items[i]; j++)									//???
	{
		if (items[i][j] == k)
		{
			intems[i].Delete(items(i));
			count--;
		}
	}
}

template<class Key, class Data>
inline Data* THMap<Key, Data>::Find(const Key& k)
{
	int i = Hash(k);

	for (int j = 0; j < items[i].count; j++)						// (int j = 0; j < items[i]; count? j++)
	{
		if (items[i][j] == k)
		{
			return intems[i][j].getData();
		}
	}
	throw "err";
}

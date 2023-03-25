#pragma once

template<typename Key,typename Data>
class TItem
{
protected:
	Key* key;
	Data* data;
public:
	TItem(Key* k = nullptr, Data* d = nullptr);
	Key& GetKey();
	Key*& GetKeyAddress();
	void SetKey(Key* k);
	Data& GetData();
	Data*& GetDataAddress();
	void SetData(Data* d);
	bool operator==(const TItem<Key, Data>& p);
	bool operator<(const TItem<Key, Data>& p);
	bool operator>(const TItem<Key, Data>& p);
};

template<typename Key, typename Data>
inline TItem<Key, Data>::TItem(Key* k, Data* d)
{
	key = k;
	data = d;
}

template<typename Key, typename Data>
inline Key& TItem<Key, Data>::GetKey()
{
	return *key;
}

template<typename Key, typename Data>
inline Key*& TItem<Key, Data>::GetKeyAddress()
{
	return key;
}

template<typename Key, typename Data>
inline void TItem<Key, Data>::SetKey(Key* k)
{
	key = k;
}

template<typename Key, typename Data>
inline Data& TItem<Key, Data>::GetData()
{
	return *data;
}

template<typename Key, typename Data>
inline Data*& TItem<Key, Data>::GetDataAddress()
{
	return data;
}

template<typename Key, typename Data>
inline void TItem<Key, Data>::SetData(Data* d)
{
	data = d;
}

template<typename Key, typename Data>
inline bool TItem<Key, Data>::operator==(const TItem<Key, Data>& p)
{
	if (this->key == p.key)
		return true;
	return false;
}

template<typename Key, typename Data>
inline bool TItem<Key, Data>::operator<(const TItem<Key, Data>& p)
{
	if (this->key < p.key)
		return true;
	return false;
}

template<typename Key, typename Data>
inline bool TItem<Key, Data>::operator>(const TItem<Key, Data>& p)
{
	if (this->key > p.key)
		return true;
	return false;
}

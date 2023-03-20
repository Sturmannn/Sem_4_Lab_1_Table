#pragma once
#include "IMap.h"

template <typename Key, typename Data>
class TItem
{
protected:

  Key* key;
  Data* data;

public:

  TItem(Key* _key = nullptr, Data* _data = nullptr);
  
  Key* GetKey();
  Data* GetData();
  void SetKey(Key* _key);
  void SetData(Data* _data);
  
  bool operator < (const TItem<Key, Data>& p);
  bool operator > (const TItem<Key, Data>& p);
  bool operator == (const TItem<Key, Data>& p);
  bool operator >= (const TItem<Key, Data>& p);
  bool operator <= (const TItem<Key, Data>& p);

  ~TItem();

};

template<typename Key, typename Data>
inline TItem<Key, Data>::TItem(Key* _key, Data* _data)
{
  key = _key;
  data = _data;
}

template<typename Key, typename Data>
inline Key* TItem<Key, Data>::GetKey()
{
  return key;
}

template<typename Key, typename Data>
inline Data* TItem<Key, Data>::GetData()
{
  return data;
}

template<typename Key, typename Data>
inline void TItem<Key, Data>::SetKey(Key* _key)
{
  key = _key;
}

template<typename Key, typename Data>
inline void TItem<Key, Data>::SetData(Data* _data)
{
  data = _data;
}

template<typename Key, typename Data>
inline bool TItem<Key, Data>::operator<(const TItem<Key, Data>& p)
{
  if (this->key < p.key) return true;
  return false;
}

template<typename Key, typename Data>
inline bool TItem<Key, Data>::operator>(const TItem<Key, Data>& p)
{
  (!TItem<Key, Data>::operator<(const TItem<Key, Data>&p);
}

template<typename Key, typename Data>
inline bool TItem<Key, Data>::operator==(const TItem<Key, Data>& p)
{
  if (this->key == p.key) return true;
  return false;
}

template<typename Key, typename Data>
inline bool TItem<Key, Data>::operator>=(const TItem<Key, Data>& p)
{
  if (this->key >= p.key) return true;
  return false;
}

template<typename Key, typename Data>
inline bool TItem<Key, Data>::operator<=(const TItem<Key, Data>& p)
{
  if (this->key <= p.key) return true;
  return false;
}

template<typename Key, typename Data>
inline TItem<Key, Data>::~TItem()
{
  if (key != nullptr) delete[] key;
  if (data != nullptr) delete[] data;
}

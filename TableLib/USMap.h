#pragma once

#include "IMap.h"
#include <iostream>

template <typename Key, typename Data>
class TUSMap : public TIMap<Key, Data>
{
protected:
  
  int size;
  int count;
  Key** keys;
  Data** items;
  int FindID(Key* _key) const;
  const int FindID(const Key* _key) const;

public:

  TUSMap(int _size = 100);
  TUSMap(const TUSMap<Key, Data>& p);
  ~TUSMap();

  const Data* operator[](const Key* _key) const override;
  const Data* Find(const Key* _key) const override;
  Data* operator[](Key* _key) override;
  Data* Find(Key* _key) override;
  void Add(Key* _key, Data* _data) override;
  void Delete(const Key* _key) override;
  bool IsEmpty() const override;
  bool IsFull() const override;

  friend std::ostream& operator<<(std::ostream& ostr, const TUSMap<Key, Data>& table)
  {
    if (table.count == 0) return ostr;
    for (int i = 0; i < table.count - 1; i++)
    {
      ostr << *(table.keys[i]) << " - " << *(table.items[i]) << ", ";
    }
    ostr << *(table.keys[table.count - 1]) << " - " << *(table.items[table.count - 1]);
    return ostr;
  }

};

template<typename Key, typename Data>
inline int TUSMap<Key, Data>::FindID(Key* _key) const
{
  for (int i = 0; i < count; i++)
  {
    if (*(keys[i]) == *_key) return i;
  }
  throw "Key doesn't exist!";
}

template<typename Key, typename Data>
inline const int TUSMap<Key, Data>::FindID(const Key* _key) const
{
  for (int i = 0; i < count; i++)
  {
    if (*(keys[i]) == *_key) return i;
  }
  throw "Key doesn't exist!";
}

template<typename Key, typename Data>
inline TUSMap<Key, Data>::TUSMap(int _size)
{
  if (_size <= 0) throw "Size <= 0!";
  this->size = _size;
  this->count = 0;
  keys = new Key * [size];
  items = new Data * [size];
  for (int i = 0; i < size; i++)
  {
    items[i] = nullptr;
    keys[i] = nullptr;
  }
}

template<typename Key, typename Data>
inline TUSMap<Key, Data>::TUSMap(const TUSMap<Key, Data>& p)
{
  size = p.size;
  count = p.count;
  keys = new Key * [size];
  items = new Data * [size];
  for (int i = 0; i < size; i++)
  {
    items[i] = p.items[i];
    keys[i] = p.items[i];
  }
}

template<typename Key, typename Data>
inline TUSMap<Key, Data>::~TUSMap()
{
  if (keys != nullptr) delete[] keys;
  if (items != nullptr) delete[] items;
}

template<typename Key, typename Data>
inline const Data* TUSMap<Key, Data>::operator[](const Key* _key) const
{
  return items[FindID(_key)];
}

template<typename Key, typename Data>
inline const Data* TUSMap<Key, Data>::Find(const Key* _key) const
{
  return items[FindID(_key)];
}

template<typename Key, typename Data>
inline Data* TUSMap<Key, Data>::operator[](Key* _key)
{
  return items[FindID(_key)];
}

template<typename Key, typename Data>
inline Data* TUSMap<Key, Data>::Find(Key* _key)
{
  return items[FindID(_key)];
}

template<typename Key, typename Data>
inline void TUSMap<Key, Data>::Add(Key* _key, Data* _data)
{
  if (count == size) throw "The table is overloaded";
  for (int i = 0; i < count; i++)
  {
    if (*(keys[i]) == *_key)
    {
      throw "Can't add duplicate key!";
    }
  }
  keys[count] = _key;
  items[count] = _data;
  count++;
}

template<typename Key, typename Data>
inline void TUSMap<Key, Data>::Delete(const Key* _key)
{
  int index = FindID(_key);
  items[index] = items[count - 1];
  keys[index] = keys[count - 1];
  count--;
}

template<typename Key, typename Data>
inline bool TUSMap<Key, Data>::IsEmpty() const
{
  if (count == 0) return true;
  return false;
}

template<typename Key, typename Data>
inline bool TUSMap<Key, Data>::IsFull() const
{
  if (count == size) return true;
  return false;
}

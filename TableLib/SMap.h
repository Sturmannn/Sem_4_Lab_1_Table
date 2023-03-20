#pragma once

#include "IMap.h"
#include "Item.h"
#include <iostream>

template <typename Key, typename Data>
class TSMap : public IMap<Key, Data>
{
protected:
  
  int size;
  int count;
  TItem<Key, Data>* items;
  
public:

  TSMap(int _size = 100);
  TSMap(const TSMap<Key, Data>& p);
  ~TSMap() = default;

  const Data* operator[](const Key* _key) const override;
  const Data* Find(const Key* _key) const override;
  Data* operator[](Key* _key) override;
  Data* Find(Key* _key) override;
  void Add(Key* _key, Data* _data) override;
  void Delete(const Key* _key) override;
  bool IsEmpty() const override;
  bool IsFull() const override;

  friend std::ostream& operator<<(std::ostream& ostr, const TSMap<Key, Data>& table)
  {
    for (int i = 0; i < table.count - 1; i++)
    {
      ostr << *(table.items[i].GetKey()) << " - " << *(table.items[i].GetData()) << ", ";
    }
    ostr << *(table.items[table.count - 1].GetKey()) << " - " << *(table.items[table.count - 1].GetData()) << " .\n";
    return ostr;
  }

};

template<typename Key, typename Data>
inline TSMap<Key, Data>::TSMap(int _size)
{
  if (_size <= 0) throw "Size <= 0!";
  this->size = _size;
  this->count = 0;
  items = new Item<Key, Data>[size];
}

template<typename Key, typename Data>
inline TSMap<Key, Data>::TSMap(const TSMap<Key, Data>& p)
{
  this->size = p.size;
  this->count = p.count;
  items = new TItem<Key, Data>[size];
  for (int i = 0; i < size; i++)
    items[i] = p.items[i];
}

template<typename Key, typename Data>
inline TSMap<Key, Data>::~TSMap()
{

}

template<typename Key, typename Data>
inline const Data* TSMap<Key, Data>::operator[](const Key* _key) const
{
  this->Find(_key);
}

template<typename Key, typename Data>
inline const Data* TSMap<Key, Data>::Find(const Key* _key) const
{
  int left = 0;
  int right = count - 1; // изначально границы - весь наш массив
  while (left <= right)
  {
    int middle = (left + right) * 0.5; // Середина области поиска
    if (*(items[middle].GetKey()) == *key)
      return items[middle].GetData();
    if (*(items[middle].GetKey()) < *key)
      left = middle + 1;
    else
      right = middle - 1;
  }
  throw "Key doesn't exist";
}

template<typename Key, typename Data>
inline Data* TSMap<Key, Data>::operator[](Key* _key)
{
  this->Find(_key);
}

template<typename Key, typename Data>
inline Data* TSMap<Key, Data>::Find(Key* _key)
{
  this->Find(_key);
}



template<typename Key, typename Data>
inline void TSMap<Key, Data>::Add(Key* _key, Data* _data)
{
  if (count == size) throw "The Map is overloaded!";
  int left = 0;
  int right = count - 1; // изначально границы - весь наш массив
  int middle;
  while (left <= right)
  {
    middle = (left + right) * 0.5; // Середина области поиска
    if (*(items[middle].GetKey()) == *key)
      throw "Key already exists!"
    if (*(items[middle].GetKey()) < *key)
      left = middle + 1;
    else
      right = middle - 1;
  }

  for (int i = count; i != middle; i--)
    items[i] = items[i - 1];

  items[middle].SetKey(_key);
  items[middle].SetData(_data);
  count++;
}

template<typename Key, typename Data>
inline void TSMap<Key, Data>::Delete(const Key* _key)
{
  int left = 0;
  int right = count - 1; // изначально границы - весь наш массив
  bool flag = false;
  int middle = 0;
  while (left <= right)
  {
    middle = (left + right) * 0.5; // Середина области поиска
    if (*(items[middle].GetKey()) == *key)
    {
      flag = true;
      break;
    }
    if (*(items[middle].GetKey()) < *key)
      left = middle + 1;
    else
      right = middle - 1;
  }
  if (!flag) throw "Key doesn't exist yet!"
  items[middle].SetKey(nullptr);
  items[middle].SetData(nullptr);
  for (int i = midd; i != count - 1; i++)
    items[i] = items[i + 1];
  count--;
}

template<typename Key, typename Data>
inline bool TSMap<Key, Data>::IsEmpty() const
{
  if (count == 0) return true;
  return false;
}

template<typename Key, typename Data>
inline bool TSMap<Key, Data>::IsFull() const
{
  if (count == size) return true;
  return false;
}

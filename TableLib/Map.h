#pragma once

#include "IMap.h"
#include <iostream>

template<class Key, class Data>
class TMap : public IMap<Key, Data>
{
protected:
  int size;
  mutable int count;
  Key** keys;
  Data** items;
public:
  TMap(int sz = 20);
  TMap(const TMap<Key, Data>& p);
  ~TMap();
  
  Data& Find(Key* k);
  const Data& Find(Key* k) const ;
  Data& operator [](Key* k);
  const Data& operator [](Key* k) const ;
  
  int FindId(Key* k);
  void Add(Key* k, Data* d);
  void Delete(Key* k);
  bool IsEmpty();
  bool IsFull();

  friend std::ostream& operator << (std::ostream& o, const TMap<Key, Data>& p)
  {
    for (int i = 0; i < m.count - 1; i++)
      o << *(p.keys[i]) << " - " << *(p.items[i]) << std::endl;
    return o;
  }
};

template<class Key, class Data>
inline TMap<Key, Data>::TMap(int sz)
{
  if (sz < 1)
    throw "Size < 0";
  size = sz;
  count = 0;
  keys = new Key* [size];
  items = new Data* [size];
  for (int i = 0; i < size; i++)
  {
    keys[i] = nullptr;
    items[i] = nullptr;
  }
}

template<class Key, class Data>
inline TMap<Key, Data>::TMap(const TMap<Key, Data>& p)
{
  size = p.size;
  count = p.count;
  keys = new Key * [size];
  items = new Data * [size];
  for (int i = 0; i < size; i++)
  {
    keys[i] = p.keys[i];
    items[i] = p.items[i];
  }
}

template<class Key, class Data>
inline TMap<Key, Data>::~TMap()
{
  if(!keys)
    delete[]keys;
  if (!keys)
    delete[]items;
  keys = nullptr;
  items = nullptr;
  count = 0;
  size = 0;
}

template<class Key, class Data>
inline Data& TMap<Key, Data>::Find(Key* k)
{
  for (int i = 0; i < count; i++)
  {
    if ((keys[i]) == k)
      return *(items[i]);
  }
  throw "Cant find Data with Key k";
}

template<class Key, class Data>
inline const Data& TMap<Key, Data>::Find(Key* k) const
{
  for (int i = 0; i < count; i++)
  {
    if ((keys[i]) == k)
      return *(items)[i];
  }
  throw "Cant find Data with Key k";
}

template<class Key, class Data>
inline Data& TMap<Key, Data>::operator[](Key* k)
{
  try 
  {
    return Find(k);//проверяем, можно ли вернуть данные с ключом k
  }
  catch(const char* msg)//если не получилось, заходим в обработчик исключений
  {
    Add(k, new Data());//добавляем в таблицу данные с ключом k
    return *(items[count]);//возвращаем новые данные и выводим сообщение, написанное в операторе throw метода Find(Key& k)
  }
}

template<class Key, class Data>
inline const Data& TMap<Key, Data>::operator[](Key* k) const 
{
  try
  {
    return Find(k);
  }
  catch (const char* msg)
  {
    keys[count] = k;
    items[count] = new Data();
    count++;
    return *(items[count]);
  }
}

template<class Key, class Data>
inline int TMap<Key, Data>::FindId(Key* k)
{
  for (int i = 0; i < count; i++)
  {
    if ((keys[i]) == k)
      return i;
  }
  throw "Cant find Data with Key k";
}

template<class Key, class Data>
inline void TMap<Key, Data>::Add(Key* k, Data* d)
{
  keys[count] = k;
  items[count] = d;
  count++;
}

template<class Key, class Data>
inline void TMap<Key, Data>::Delete(Key* k)
{
  int i = FindId(k);
  for (; i < count - 1; i++)
  {
    keys[i] = keys[i + 1];
    items[i] = items[i + 1];
  }
  keys[count - 1] = nullptr;
  items[count - 1] = nullptr;
  count--;
}

template<class Key, class Data>
inline bool TMap<Key, Data>::IsEmpty()
{
  return count == 0;
}

template<class Key, class Data>
inline bool TMap<Key, Data>::IsFull()
{
  return count == size;
}
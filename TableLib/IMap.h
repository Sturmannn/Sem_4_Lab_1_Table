#pragma once

template <typename Key, typename Data>
class IMap
{
public:
  virtual Data& Find(Key* k) = 0;
  virtual const Data& Find(Key* k) const = 0;
  virtual Data& operator[](Key* k) = 0;
  virtual const Data& operator[](Key* k) const = 0;
  virtual void Add(Key* k, Data* d) = 0;
  virtual void Delete(Key* k) = 0;
};
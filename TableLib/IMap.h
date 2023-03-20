#pragma once

template <typename Key, typename Data>
class TIMap
{
public:
  virtual const Data* operator[](const Key* _key) const = 0;
  virtual const Data* Find(const Key* _key) const = 0;
  virtual Data* operator[](Key* _key) = 0;
  virtual Data* Find(Key* _key) = 0;
  virtual void Add(Key* _key, Data* _data) = 0;
  virtual void Delete(const Key* _key) = 0;
  virtual bool IsEmpty() const = 0;
  virtual bool IsFull() const = 0;
};
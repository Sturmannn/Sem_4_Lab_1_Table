#pragma once

#include "Item.h"

template <typename Key, typename Data>
class TTreeItem : public TItem<Key,Data>
{
protected:
  TTreeItem<Key, Data>* left;
  TTreeItem<Key, Data>* right;
public:
  TTreeItem();
  TTreeItem(Data* d, Key* k);
  TTreeItem(TTreeItem<Key, Data>* l, TTreeItem<Key, Data>* r, Key* k = nullptr, Data* d = nullptr);
  TTreeItem(const TTreeItem<Key, Data>& p);
  TTreeItem<Key, Data>* GetLeft();
  TTreeItem<Key, Data>* GetRight();
  void SetLeft(TTreeItem<Key, Data>* l);
  void SetRight(TTreeItem<Key, Data>* r);
};

template<typename Key, typename Data>
inline TTreeItem<Key, Data>::TTreeItem()
{
  key = nullptr;
  data = nullptr;
  left = nullptr;
  right = nullptr;
}

template<typename Key, typename Data>
inline TTreeItem<Key, Data>::TTreeItem(Data* d, Key* k)
{
  key = k;
  data = d;
  left = nullptr;
  right = nullptr;
}

template<typename Key, typename Data>
inline TTreeItem<Key, Data>::TTreeItem(TTreeItem<Key, Data>* l, TTreeItem<Key, Data>* r, Key* k, Data* d)
{
  this = new TItem<Key, Data>(k, d);//?? 
  if (left == nullptr)
    left = l;
  else
    throw "can't build left part, because its already built";
  if (right == nullptr)
    right = r;
  else
    throw "can't build right part, because its already built";
}

template<typename Key, typename Data>
inline TTreeItem<Key, Data>::TTreeItem(const TTreeItem<Key, Data>& p)
{
  key = p.key;
  data = p.data;
  left = p.left;
  right = p.right;
}

template<typename Key, typename Data>
inline TTreeItem<Key, Data>* TTreeItem<Key, Data>::GetLeft()
{
  return left;
}

template<typename Key, typename Data>
inline TTreeItem<Key, Data>* TTreeItem<Key, Data>::GetRight()
{
  return right;
}

template<typename Key, typename Data>
inline void TTreeItem<Key, Data>::SetLeft(TTreeItem<Key, Data>* l)
{
  left = l;
}

template<typename Key, typename Data>
inline void TTreeItem<Key, Data>::SetRight(TTreeItem<Key, Data>* r)
{
  right = r;
}

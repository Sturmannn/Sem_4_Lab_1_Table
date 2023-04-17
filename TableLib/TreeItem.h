#pragma once

#include "Item.h"
#define MAX_SIZE 2147483

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

  TTreeItem<Key, Data>* Copy(TTreeItem<Key, Data>* p);
  int GetCount();
  int BalanceFactor();
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
  this = new TItem<Key, Data>(k, d);
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

template<typename Key, typename Data>
inline TTreeItem<Key, Data>* TTreeItem<Key, Data>::Copy(TTreeItem<Key, Data>* tree)
{
  TTreeItem<Key, Data>* A, * B, * temp;
  TStack<TTreeItem<Key, Data>*> Stack1, Stack2;
  Data* d1 = new Data(tree->GetData());
  Key* k1 = new Key(tree->GetKey());
  temp = new TTreeItem<Key, Data>(d1, k1);
  Stack1.Push(temp);
  Stack2.Push(tree);
  while (!Stack2.isEmpty())
  {
    A = Stack1.Pop();
    B = Stack2.Pop();

    if ((*B).GetLeft() != nullptr)
    {
      Data* d = new Data(B->GetLeft()->GetData());
      Key* k = new Key(B->GetLeft()->GetKey());
      A->SetLeft(new TTreeItem<Key, Data>(d, k));
      Stack1.Push((*A).GetLeft());
      Stack2.Push((*B).GetLeft());
    }
    if ((*B).GetRight() != nullptr)
    {
      Data* d = new Data(B->GetRight()->GetData());
      Key* k = new Key(B->GetRight()->GetKey());
      A->SetRight(new TTreeItem<Key, Data>(d, k));
      Stack1.Push((*A).GetRight());
      Stack2.Push((*B).GetRight());
    }
  }
  return temp;
}

template<typename Key, typename Data>
inline int TTreeItem<Key, Data>::GetCount()
{
  TTreeItem<Key, Data>* temp1 = this;
  TStack<TTreeItem<Key, Data>*> s(MAX_SIZE);
  int count = 1;
  s.Push(nullptr);

  while (1)
  {
    if (temp1->GetLeft() != nullptr)
      s.Push(temp1->GetLeft());
    if (temp1->GetRight() != nullptr)
      s.Push(temp1->GetRight());
    temp1 = s.Pop();
    if (temp1 == nullptr)
      break;
    else
      count++;
  }
  return count;
}

template<typename Key, typename Data>
inline int TTreeItem<Key, Data>::BalanceFactor()
{
  return this->GetRight()->GetCount() - this->GetLeft()->GetCount();
}

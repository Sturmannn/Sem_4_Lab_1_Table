#pragma once

#include "IMap.h"
#include "TreeItem.h"
#include "Stack.h"
#include "Queue.h"

template<typename Key, typename Data>
class TTreeMap : public IMap<Key, Data>
{
protected:
  mutable int count;
  mutable TTreeItem<Key, Data>* root;
public:
  TTreeMap();
  TTreeMap(const TTreeMap<Key, Data>& p);
  ~TTreeMap();
  Data& operator[](Key* k);
  Data& Find(Key* k);
  const Data& operator[](Key* k) const;
  const Data& Find(Key* k) const;
  void Add(Key* k, Data* d);
  const void Add(Key* k, Data* d) const;
  void Delete(Key* k);
  void Add(TTreeItem<Key, Data>* tree);
};

template<typename Key, typename Data>
inline TTreeMap<Key, Data>::TTreeMap()
{
  count = 0;
  root = nullptr;
}

template<typename Key, typename Data>
inline TTreeMap<Key, Data>::TTreeMap(const TTreeMap<Key, Data>& p)
{
  if (p.root == nullptr)
  {
    root = nullptr;
    count = p.count;
  }
  else 
  {
    TTreeItem<Key, Data> *A, *B;
    TStack<TTreeItem<Key, Data>*> Stack1, Stack2;
    root = new TTreeItem<Key, Data>(*p.root);
    Stack1.Push(root);
    Stack2.Push(p.root);
    while (!Stack2.isEmpty())
    {
      A = Stack1.Pop();
      B = Stack2.Pop();

      if ((*B).GetLeft() != nullptr)
      {
        A->SetLeft(new TTreeItem<Key, Data>(*B->GetLeft()));
        Stack1.Push((*A).GetLeft());
        Stack2.Push((*B).GetLeft());
      }
      if ((*B).GetRight() != nullptr)
      {
        A->SetRight(new TTreeItem<Key, Data>(*B->GetRight()));
        Stack1.Push((*A).GetRight());
        Stack2.Push((*B).GetRight());
      }
    }
    count = p.count;
  }
}

template<typename Key, typename Data>
inline TTreeMap<Key, Data>::~TTreeMap()
{
  if (root != nullptr)
  {
    TQueue<TTreeItem<Key, Data>*> q(count);
    while (count != 0)
    {
      if (root->GetLeft() != nullptr)
        q.Push(root->GetLeft());
      if (root->GetRight() != nullptr)
        q.Push(root->GetRight());
      if (root->GetRight() != nullptr || root->GetLeft() != nullptr)
      {
        delete root;
        root = q.Pop();
      }
      else
        delete root;
      count--;
    }
    root = nullptr;
  }
}

template<typename Key, typename Data>
inline Data& TTreeMap<Key, Data>::operator[](Key* k)
{
  try 
  {
    this->Find(k);
  }
  catch (const char* msg)
  {
    this->Add(k, new Data());
    return Find(k);
  }
}

template<typename Key, typename Data>
inline Data& TTreeMap<Key, Data>::Find(Key* k)
{
  if (root != nullptr)
  {
    TTreeItem<Key, Data>* temp = root;
    while (temp != nullptr)
    {
      if (temp->GetKey() == *k)
        return temp->GetData();
      else if (temp->GetKey() < *k)
        temp = temp->GetRight();
      else if (temp->GetKey() > *k)
        temp = temp->GetLeft();
    }
  }
  throw "Root == nullptr/cant find data with key k";
}

template<typename Key, typename Data>
inline const Data& TTreeMap<Key, Data>::operator[](Key* k) const
{
  try
  {
    this->Find(k);
  }
  catch (const char* msg)
  {
    this->Add(k, new Data());
    return Find(k);
  }
}

template<typename Key, typename Data>
inline const Data& TTreeMap<Key, Data>::Find(Key* k) const
{
  if (root != nullptr)
  {
    TTreeItem<Key, Data>* temp = root;
    while (temp != nullptr)
    {
      if (temp->GetKey() == *k)
        return temp->GetData();
      else if (temp->GetKey() < *k)
        temp = temp->GetRight();
      else if (temp->GetKey() > *k)
        temp = temp->GetLeft();
    }
  }
  throw "Root == nullptr/cant find data with key k";
}

template<typename Key, typename Data>
inline void TTreeMap<Key, Data>::Add(Key* k, Data* d)
{
  if (root == nullptr)
  {
    root = new TTreeItem<Key, Data>();
    root->SetData(d);
    root->SetKey(k);
  }
  else
  {
    char flag;
    TTreeItem<Key, Data>* temp = root;
    while (temp != nullptr)
    {
      if (temp->GetKey() == *k)
        throw "Data with key K is already exist";
      else if (temp->GetKey() < *k)
      {
        if (temp->GetRight() != nullptr)
          temp = temp->GetRight();
        else
        {
          flag = 'r';
          break;
        }
      }
      else if (temp->GetKey() > *k)
      {
        if (temp->GetLeft() != nullptr)
          temp = temp->GetLeft();
        else
        {
          flag = 'l';
          break;
        }
      }
    }
    if (flag == 'r')
    {
      temp->SetRight(new TTreeItem<Key, Data>());
      temp->GetRight()->SetData(d);
      temp->GetRight()->SetKey(k);
    }
    else if (flag == 'l')
    {
      temp->SetLeft(new TTreeItem<Key, Data>());
      temp->GetLeft()->SetData(d);
      temp->GetLeft()->SetKey(k);
    }
  }
  count++;
}

template<typename Key, typename Data>
inline const void TTreeMap<Key, Data>::Add(Key* k, Data* d) const
{
  if (root == nullptr)
  {
    root = new TTreeItem<Key, Data>();
    root->SetData(d);
    root->SetKey(k);
  }
  else
  {
    char flag;
    TTreeItem<Key, Data>* temp = root;
    while (temp != nullptr)
    {
      if (temp->GetKey() == *k)
        throw "Data with key K is already exist";
      else if (temp->GetKey() < *k)
      {
        if (temp->GetRight() != nullptr)
          temp = temp->GetRight();
        else
        {
          flag = 'r';
          break;
        }
      }
      else if (temp->GetKey() > *k)
      {
        if (temp->GetLeft() != nullptr)
          temp = temp->GetLeft();
        else
        {
          flag = 'l';
          break;
        }
      }
    }
    if (flag == 'r')
    {
      temp->SetRight(new TTreeItem<Key, Data>());
      temp->GetRight()->SetData(d);
      temp->GetRight()->SetKey(k);
    }
    else if (flag == 'l')
    {
      temp->SetLeft(new TTreeItem<Key, Data>());
      temp->GetLeft()->SetData(d);
      temp->GetLeft()->SetKey(k);
    }
  }
  count++;
}

template<typename Key, typename Data>
inline void TTreeMap<Key, Data>::Delete(Key* k)
{
  if (root == nullptr)
    throw "Error : root == nullptr";

  TTreeItem<Key, Data>* temp = root;
  if (temp->GetKey() == *k)
  {
    this->TTreeMap::~TTreeMap();
  }
  else
  {
    while (temp != nullptr)
    {
      if (temp->GetKey() < *k)
      {
        if (temp->GetRight()->GetKey() == *k)
        {
          //
        }
        temp = temp->GetRight();
      }
      else if (temp->GetKey() > *k)
      {

        if (temp->GetLeft()->GetKey() == *k)
        {
          //
        }
        temp = temp->GetLeft();
      }
    }
  }
}

template<typename Key, typename Data>
inline void TTreeMap<Key, Data>::Add(TTreeItem<Key, Data>* tree)
{
  //
}
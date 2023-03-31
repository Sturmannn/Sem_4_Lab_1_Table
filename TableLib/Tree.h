#pragma once

#include <iostream>
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

  TTreeItem<Key, Data>* GetRoot() { return root; }

  Data& operator[](Key* k);
  Data& Find(Key* k);
  const Data& operator[](Key* k) const;
  const Data& Find(Key* k) const;

  void Add(Key* k, Data* d);
  const void Add(Key* k, Data* d) const;
  void Delete(Key* k);
  void DeleteSubTree(Key* k);
  void Add(TTreeItem<Key, Data>* tree);
  void Add(TTreeMap<Key, Data>& tree);

  TTreeItem<Key, Data>*& FindItem(Key* k);
  TQueue<char> Path(Key* k);
  TTreeItem<Key, Data>*& FindItem(TQueue<char>& p);
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

  try
  {
    this->Find(k);
  }
  catch (const char* msg)
  {
    std::cout << msg << std::endl;
    this->Add(k, new Data());
  }

  TTreeItem<Key, Data>* temp = root;
  TTreeItem<Key, Data>* temp1 = nullptr;

  while (1) 
  {
    if (temp->GetRight() != nullptr)
    {
      if (temp->GetRight()->GetKey() == *k)
      {
        if (temp->GetRight()->GetLeft() == nullptr)
        {
          temp1 = temp->GetRight()->GetRight();
          delete temp->GetRight();
          temp->SetRight(temp1);
          count--;
          break;
        }
        else
          throw "can't delete key";
      }
    }

    if (temp->GetLeft() != nullptr)
    {
      if (temp->GetLeft()->GetKey() == *k)
      {
        if (temp->GetLeft()->GetRight() == nullptr)
        {
          temp1 = temp->GetLeft()->GetLeft();
          delete temp->GetLeft();
          temp->SetLeft(temp1);
          count--;
          break;
        }
        else
          throw "can't delete key";
      }
    }

    else if (temp->GetKey() < *k)
      temp = temp->GetRight();
    else if (temp->GetKey() > *k)
      temp = temp->GetLeft();
  }
}

template<typename Key, typename Data>
inline void TTreeMap<Key, Data>::DeleteSubTree(Key* k)
{
  if (root == nullptr)
    throw "Error : root == nullptr";

  try
  {
    this->Find(k);
  }
  catch (const char* msg)
  {
    std::cout << msg << std::endl;
    this->Add(k, new Data());
  }

  TTreeItem<Key, Data>* temp = root;
  TTreeItem<Key, Data>* temp1 = root;
  TQueue<char> path(this->Path(k));
  TQueue<TTreeItem<Key, Data>*> q(count);

  if (temp->GetKey() == *k)
    this->TTreeMap::~TTreeMap();
  else
  {
    while (temp != nullptr)
    {
      if (temp->GetKey() < *k)
        temp = temp->GetRight();
      else if (temp->GetKey() > *k)
        temp = temp->GetLeft();
      if (temp->GetKey() == *k)
      {
        while (1)
        {
          if (temp->GetLeft() != nullptr)
            q.Push(temp->GetLeft());
          if (temp->GetRight() != nullptr)
            q.Push(temp->GetRight());
          if (temp->GetRight() != nullptr || temp->GetLeft() != nullptr)
          {
            delete temp;
            temp = q.Pop();
          }
          else
          {
            delete temp;
            while (temp1 != nullptr)
            {
              if (path.Size() == 1)
              {
                if (path.Pop() == 'r')
                {
                  temp1->SetRight(nullptr);
                  break;
                }
                else if (path.Pop() == 'l')
                {
                  temp1->SetLeft(nullptr);
                  break;
                }
              }
              if (path.Pop() == 'r')
                temp1 = temp1->GetRight();
              else if (path.Pop() == 'l')
                temp1 = temp1->GetLeft();
            }
            count--;
            goto exit;
          }
          count--;
        }
      }
    }
  }
exit:;
}

template<typename Key, typename Data>
inline void TTreeMap<Key, Data>::Add(TTreeItem<Key, Data>* tree)
{
  if (tree == nullptr)
    throw "Nothing to add";

  TTreeItem<Key, Data>* temp = root, * temp1 = nullptr, * temp2 = tree;
  temp1 = temp1->Copy(tree);//full copy of tree, but with another address
  TStack<TTreeItem<Key, Data>*> s(temp2->GetCount());
  s.Push(nullptr);
  char flag = '\0';

  while (1)
  {
    if (flag != '\0')
    {
      while (1)
      {
        if (temp2->GetLeft() != nullptr)
          s.Push(temp2->GetLeft());
        if (temp2->GetRight() != nullptr)
          s.Push(temp2->GetRight());
        temp2 = s.Pop();
        if (temp2 == nullptr)
          break;
        try 
        {
          this->Find(temp2->GetKeyAddress());
        }
        catch (...)
        {
          goto exit;
        }
        throw "New tree can't contain the same Keys";
      exit:;
      }
      if (flag == 'r')
        temp->SetRight(temp1);
      else if (flag == 'l')
        temp->SetLeft(temp1);
      count += temp1->GetCount();
      break;
    }

    else if (temp->GetKey() < temp1->GetKey())
    {
      if (temp->GetRight() != nullptr)
        temp = temp->GetRight();
      else
        flag = 'r';
    }
    else if (temp->GetKey() > temp1->GetKey())
    {
      if (temp->GetLeft() != nullptr)
        temp = temp->GetLeft();
      else
        flag = 'l';
    }
    else if (temp->GetKey() == temp1->GetKey())
      throw "Keys can't be equal";
  }
}

template<typename Key, typename Data>
inline void TTreeMap<Key, Data>::Add(TTreeMap<Key, Data>& p)
{
  (*this).Add(p.GetRoot());
}

template<typename Key, typename Data>
inline TTreeItem<Key, Data>*& TTreeMap<Key, Data>::FindItem(Key* k)
{
  if (root == nullptr)
    throw "Error : root == nullptr";
  TTreeItem<Key, Data>* temp = root;
  while (temp != nullptr)
  {
    if (temp->GetKey() == *k)
      return temp;
    else if (temp->GetKey() < *k)
      temp = temp->GetRight();
    else if (temp->GetKey() > *k)
      temp = temp->GetLeft();
  }
}

template<typename Key, typename Data>
inline TQueue<char> TTreeMap<Key, Data>::Path(Key* k)
{
  if (root == nullptr)
    throw "Error : root == nullptr";
  TQueue<char> tmp(count);
  TTreeItem<Key, Data>* temp = root;
  while (temp != nullptr)
  {
    if (temp->GetKey() == *k)
      return tmp;
    else if (temp->GetKey() < *k)
    {
      temp = temp->GetRight();
      tmp.Push('r');
    }
    else if (temp->GetKey() > *k)
    {
      temp = temp->GetLeft();
      tmp.Push('l');
    }
  }
}

template<typename Key, typename Data>
inline TTreeItem<Key, Data>*& TTreeMap<Key, Data>::FindItem(TQueue<char>& p)
{
  if (root == nullptr)
    throw "Error : root == nullptr";
  TTreeItem<Key, Data>* temp = root;
  while (temp != nullptr)
  {
    if (p.isEmpty())
      return temp;
    if (p.Pop() == 'r')
      temp = temp->GetRight();
    else if (p.Pop() == 'l')
      temp = temp->GetLeft();
  }
}
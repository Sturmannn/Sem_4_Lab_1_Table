#pragma once
#include "TreeItem.h"
#include "IMap.h"
#include <queue>
#include <stack>

template<typename Key, typename Data>
class TTreeMap : public TIMap<Key, Data>
{

protected:

  int count;
  TTreeItem<Key, Data>* root;
  
public:

  TTreeMap<Key, Data>(void) = default;
  TTreeMap<Key, Data>(const TTreeMap<Key, Data>& _tree);
  ~TTreeMap<Key, Data>(void);
  
  const Data& operator[] (const Key& _key) const;
  const Data* Find(const Key& _key) const;
  
  void Add(Key* _key, Data* _data);
  void Add(TTreeItem<Key, Data>* _tree);
  void Delete(const Key& _key);

};

//template<typename Key, typename Data>
//inline TTreeMap<Key, Data>::TTreeMap(void)
//{
//  count = 0;
//  root = nullptr;
//}

template<typename Key, typename Data>
inline TTreeMap<Key, Data>::TTreeMap(const TTreeMap<Key, Data>& _tree)
{
  if (_tree.root == nullptr)
  {
    TTreeMap<Key, Data>::TTreeMap(void);
    return;
  }
  std::stack<TTreeItem<Key, Data>*> stack1(_tree.count), stack2(_tree.count);
  TTreeItem<Key, Data>* A, * B;
  root = new TTreeItem<Key, Data>(*_tree.root);
  stack1.push(root);
  stack2.push(_tree.root);
  while (!stack2.empty())
  {
    A = stack1.top();
    stack1.pop();
    B = stack2.top();
    stack2.pop();
    if ((*B).GetLeft() != nullptr)
    {
      A->SetLeft(new TTreeItem<Key, Data>((*B).GetLeft()));
      stack1.push((*A).GetLeft());
      stack2.push((*B).GetLeft());
    }
    if ((*B).GetRight() != nullptr)
    {
      A->SetRight(new TTreeItem<Key, Data>((*B).GetLeft()));
      stack1.push((*A).GetRight());
      stack2.push((*B).GetRight());
    }
  }
  count = *_tree.count;
}

template<typename Key, typename Data>
inline TTreeMap<Key, Data>::~TTreeMap(void)
{
  if (root != nullptr)
  {
    std::queue<TTreeItem<Key, Data>*> q(count);
    q.push(root);
    while (count != 0)
    {
      if (root->GetLeft() != nullptr)
      {
        q.push(root->GetLeft());
      }
      if (root->GetRight() != nullptr)
      {
        q.push(root->GetRight());
      }
      delete root;
      root = q.pop();
      count--;
    }
    delete root;
    root = nullptr;
  }
}

template<typename Key, typename Data>
inline const Data& TTreeMap<Key, Data>::operator[](const Key& _key) const
{
  if (root != nullptr)
  {
    TTreeItem<Key, Data>* temp = root;
    while (temp != nullptr)
    {
      if (*temp == _key) return temp;
      else if (*temp < _key)
        temp = root->GetRight();
      else
        temp = root->GetLeft();
    }
  }
  throw "Key doesn't exist!";
}

template<typename Key, typename Data>
inline const Data* TTreeMap<Key, Data>::Find(const Key& _key) const
{
  TTreeItem<Key, Data>* rt = root;
  while (rt != nullptr)
  {
    if (*rt == _key)
      return rt->GetData();
    else if (*rt > k)
      rt = rt->GetLeft();
    else
      rt = rt->GetRight();
  }
  throw "Key doesn't exist!";
}

template<typename Key, typename Data>
inline void TTreeMap<Key, Data>::Add(Key* _key, Data* _data)
{
  TTreeItem<Key, Data>* rt = root;
  while (rt != nullptr)
  {
    if ((*rt).GetKey() == *_key) throw "Key is already exist!";
    else if ((*rt).GetKey() < *_key)
    {
      if ()
    }
  }
}

template<typename Key, typename Data>
inline void TTreeMap<Key, Data>::Add(TTreeItem<Key, Data>* _tree)
{
}

template<typename Key, typename Data>
inline void TTreeMap<Key, Data>::Delete(const Key& _key)
{
}

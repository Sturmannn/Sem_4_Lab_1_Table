#pragma once

#include <cmath>
#include "IMap.h"
#include "TreeItem.h"
#include "Stack.h"
#include "Queue.h"

template<class Key, class Data>
class TAVLTree : public IMap<Key, Data>
{
protected:
  mutable TTreeItem<Key, Data>* root;
  mutable size_t count;
  void Balance(TTreeItem<Key, Data>* p);
  const void Balance(TTreeItem<Key, Data>* p) const {};
  TTreeItem<Key, Data>* GetRoot() { return root; };
public:
  TAVLTree();
  ~TAVLTree();
  TAVLTree(const TAVLTree<Key, Data>& p);

  Data& operator[](Key* k);
  Data& Find(Key* k);
  const Data& operator[](Key* k) const;
  const Data& Find(Key* k) const;

  void Add(Key* k, Data* d);
  const void Add(Key* k, Data* d) const;
  void Add(TTreeItem<Key, Data>* tree);
  void Add(TAVLTree<Key, Data> tree);

  TQueue<char> Path(Key* k);

  void Delete(Key* k);
  void DeleteSubTree(Key* k);

  void SmallRightRotate(TTreeItem<Key, Data>* p);
  void RightRotate(TTreeItem<Key, Data>* p);
  void SmallLeftRotate(TTreeItem<Key, Data>* p);
  void LeftRotate(TTreeItem<Key, Data>* p);
};

template<class Key, class Data>
inline void TAVLTree<Key, Data>::Balance(TTreeItem<Key, Data>* p)
{
  TTreeItem<Key, Data>* tmp = root, *tmp1 = root;
  TQueue<char> q(Path(p->GetKeyAddress()));
  TStack<TTreeItem<Key, Data>*> s(tmp->GetCount());
  s.Push(nullptr);

  while (!q.isEmpty()) {
    s.Push(tmp);
    if (q.Pop() == 'r')
      tmp = tmp->GetRight();
    else
      tmp = tmp->GetLeft();
  }

  while (tmp != nullptr) {
    if (abs(tmp->GetRight()->GetHeight(tmp) - tmp->GetLeft()->GetHeight(tmp)) == 2) {
      if (tmp->GetRight() != nullptr && tmp->GetRight()->GetRight()->GetHeight(tmp) >= tmp->GetRight()->GetLeft()->GetHeight(tmp))
        SmallLeftRotate(tmp);

      else if (tmp->GetLeft() != nullptr && tmp->GetLeft()->GetLeft()->GetHeight(tmp) >= tmp->GetLeft()->GetRight()->GetHeight(tmp))
        SmallRightRotate(tmp);

      else if (tmp->GetRight() != nullptr && tmp->GetRight()->GetRight() != nullptr && tmp->GetRight()->GetRight()->GetHeight(tmp) < tmp->GetRight()->GetLeft()->GetHeight(tmp))
        LeftRotate(tmp);

      else if (tmp->GetLeft() != nullptr && tmp->GetLeft()->GetRight() != nullptr && tmp->GetLeft()->GetLeft()->GetHeight(tmp) < tmp->GetLeft()->GetRight()->GetHeight(tmp))
        RightRotate(tmp);
    }
    tmp = s.Pop();
  }
}

template<class Key, class Data>
inline TAVLTree<Key, Data>::TAVLTree()
{
  root = nullptr;
  count = 0;
}

template<class Key, class Data>
inline TAVLTree<Key, Data>::~TAVLTree()
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
      delete root;
      if (q.Top() != nullptr)
        root = q.Pop();
      count--;
    }
    root = nullptr;
  }
}

template<class Key, class Data>
inline TAVLTree<Key, Data>::TAVLTree(const TAVLTree<Key, Data>& p)
{
  if (p.root == nullptr)
  {
    root = nullptr;
    count = 0;
  }
  else
  {
    TTreeItem<Key, Data>* A, * B;
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

template<class Key, class Data>
inline Data& TAVLTree<Key, Data>::operator[](Key* k)
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

template<class Key, class Data>
inline Data& TAVLTree<Key, Data>::Find(Key* k)
{
  if (root != nullptr)
  {
    TTreeItem<Key, Data>* temp = root;
    while (temp != nullptr)
    {
      if (temp->GetKey() == *k)
        return temp->GetData();
      if (temp->GetKey() < *k)
        temp = temp->GetRight();
      if (temp->GetKey() > *k)
        temp = temp->GetLeft();
    }
  }
  throw "Root == nullptr/cant find data with key k";
}

template<class Key, class Data>
inline const Data& TAVLTree<Key, Data>::operator[](Key* k) const
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

template<class Key, class Data>
inline const Data& TAVLTree<Key, Data>::Find(Key* k) const
{
  if (root != nullptr)
  {
    TTreeItem<Key, Data>* temp = root;
    while (temp != nullptr)
    {
      if (temp->GetKey() == *k)
        return temp->GetData();
      if (temp->GetKey() < *k)
        temp = temp->GetRight();
      if (temp->GetKey() > *k)
        temp = temp->GetLeft();
    }
  }
  throw "Root == nullptr/cant find data with key k";
}

template<class Key, class Data>
inline void TAVLTree<Key, Data>::Add(Key* k, Data* d)
{
  char flag;
  TTreeItem<Key, Data>* temp = root;
  if (root == nullptr) {
    root = new TTreeItem<Key, Data>();
    root->SetData(d);
    root->SetKey(k);
    count++;
    Balance(root);
  }
  else {
    while (temp != nullptr) {
      if (temp->GetKey() == *k)
        throw "Data with key K is already exist";

      if (temp->GetKey() < *k) {
        if (temp->GetRight() != nullptr)
          temp = temp->GetRight();
        else {
          flag = 'r';
          break;
        }
      }
      if (temp->GetKey() > *k) {
        if (temp->GetLeft() != nullptr)
          temp = temp->GetLeft();
        else {
          flag = 'l';
          break;
        }
      }
    }
    if (flag == 'r') {
      temp->SetRight(new TTreeItem<Key, Data>());
      temp->GetRight()->SetData(d);
      temp->GetRight()->SetKey(k);
      count++;
      Balance(temp->GetRight());
    }
    else if (flag == 'l') {
      temp->SetLeft(new TTreeItem<Key, Data>());
      temp->GetLeft()->SetData(d);
      temp->GetLeft()->SetKey(k);
      count++;
      Balance(temp->GetLeft());
    }
  }
}

template<class Key, class Data>
inline const void TAVLTree<Key, Data>::Add(Key* k, Data* d) const
{
  char flag;
  TTreeItem<Key, Data>* temp = root;
  if (root == nullptr) {
    root = new TTreeItem<Key, Data>();
    root->SetData(d);
    root->SetKey(k);
    count++;
    Balance(root);
  }
  else {
    while (temp != nullptr) {
      if (temp->GetKey() == *k)
        throw "Data with key K is already exist";

      if (temp->GetKey() < *k) {
        if (temp->GetRight() != nullptr)
          temp = temp->GetRight();
        else {
          flag = 'r';
          break;
        }
      }
      if (temp->GetKey() > *k) {
        if (temp->GetLeft() != nullptr)
          temp = temp->GetLeft();
        else {
          flag = 'l';
          break;
        }
      }
    }
    if (flag == 'r') {
      temp->SetRight(new TTreeItem<Key, Data>());
      temp->GetRight()->SetData(d);
      temp->GetRight()->SetKey(k);
    }
    else if (flag == 'l') {
      temp->SetLeft(new TTreeItem<Key, Data>());
      temp->GetLeft()->SetData(d);
      temp->GetLeft()->SetKey(k);
    }
    count++;
    Balance(temp);
  }
 
}

template<class Key, class Data>
inline void TAVLTree<Key, Data>::Add(TTreeItem<Key, Data>* tree)
{
  if (tree == nullptr)
    return;

  TTreeItem<Key, Data>* temp = root, * temp1 = nullptr, * temp2 = tree;
  temp1 = temp1->Copy(tree);                                            //full copy of tree, but with another address
  TStack<TTreeItem<Key, Data>*> s(temp2->GetCount());
  s.Push(nullptr);
  char flag = '\0';

  while (1) {
    if (flag != '\0') {
      while (1) {
        if (temp2->GetLeft() != nullptr)
          s.Push(temp2->GetLeft());
        if (temp2->GetRight() != nullptr)
          s.Push(temp2->GetRight());

        temp2 = s.Pop();
        if (temp2 == nullptr)
          break;

        try {
          this->Find(temp2->GetKeyAddress());
        }
        catch (...) {
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

    else if (temp->GetKey() < temp1->GetKey()) {
      if (temp->GetRight() != nullptr)
        temp = temp->GetRight();
      else
        flag = 'r';
    }
    else if (temp->GetKey() > temp1->GetKey()) {
      if (temp->GetLeft() != nullptr)
        temp = temp->GetLeft();
      else
        flag = 'l';
    }
    else if (temp->GetKey() == temp1->GetKey())
      throw "Keys can't be equal";
  }
}

template<class Key, class Data>
inline void TAVLTree<Key, Data>::Add(TAVLTree<Key, Data> tree)
{
  (*this).Add(tree.GetRoot());
}

template<class Key, class Data>
inline TQueue<char> TAVLTree<Key, Data>::Path(Key* k)
{
  if (root == nullptr)
    throw "Error : root == nullptr";
  TQueue<char> tmp(count);
  TTreeItem<Key, Data>* temp = root;
  while (temp != nullptr) {
    if (temp->GetKey() == *k)
      return tmp;

    else if (temp->GetKey() < *k) {
      temp = temp->GetRight();
      tmp.Push('r');
    }
    else if (temp->GetKey() > *k) {
      temp = temp->GetLeft();
      tmp.Push('l');
    }
  }
}

template<class Key, class Data>
inline void TAVLTree<Key, Data>::Delete(Key* k)
{
  if (root == nullptr)
    throw "Error : root == nullptr";

  try {
    this->Find(k);
  }
  catch (const char* msg) {
    std::cout << msg << std::endl;
    this->Add(k, new Data());
  }

  TTreeItem<Key, Data>* temp = root;
  TTreeItem<Key, Data>* temp1 = nullptr;

  if (temp->GetKey() == *k && temp->GetRight() == nullptr && temp->GetLeft() == nullptr) {
    this->TAVLTree::~TAVLTree();
    return;
  }

  while (temp != nullptr) {
    if (temp->GetRight() != nullptr) {
      if (temp->GetRight()->GetKey() == *k) {
        if (temp->GetRight()->GetLeft() == nullptr) {
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

    if (temp->GetLeft() != nullptr) {
      if (temp->GetLeft()->GetKey() == *k) {
        if (temp->GetLeft()->GetRight() == nullptr) {
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

    if (temp->GetKey() < *k)
      temp = temp->GetRight();
    else if (temp->GetKey() > *k)
      temp = temp->GetLeft();
  }
}

template<class Key, class Data>
inline void TAVLTree<Key, Data>::DeleteSubTree(Key* k)
{
  if (root == nullptr)
    throw "Error : root == nullptr";

  try {
    this->Find(k);
  }
  catch (const char* msg) {
    std::cout << msg << std::endl;
    this->Add(k, new Data());
  }

  TTreeItem<Key, Data>* temp = root;
  TTreeItem<Key, Data>* temp1 = root;
  TQueue<char> path(Path(k));
  TQueue<TTreeItem<Key, Data>*> q(count);

  if (temp->GetKey() == *k)
    this->TAVLTree::~TAVLTree();
  else {
    while (temp != nullptr) {
      if (temp->GetKey() < *k)
        temp = temp->GetRight();
      if (temp->GetKey() > *k)
        temp = temp->GetLeft();

      if (temp->GetKey() == *k) {
        while (1) {
          if (temp->GetLeft() != nullptr)
            q.Push(temp->GetLeft());
          if (temp->GetRight() != nullptr)
            q.Push(temp->GetRight());

          if (temp->GetRight() != nullptr || temp->GetLeft() != nullptr) {
            delete temp;
            temp = q.Pop();
          }
          else {
            delete temp;
            if (q.isEmpty()) {
              while (temp1 != nullptr) {
                if (path.Size() == 1) {
                  if (path.Pop() == 'r') {
                    temp1->SetRight(nullptr);
                    break;
                  }

                  else {
                    temp1->SetLeft(nullptr);
                    break;
                  }
                }
                if (path.Pop() == 'r')
                  temp1 = temp1->GetRight();
                else
                  temp1 = temp1->GetLeft();
              }
              count--;
              goto exit;
            }
            temp = q.Pop();
          }
          count--;
        }
      }
    }
  }
exit:;
  Balance(temp1);
}

template<class Key, class Data>
inline void TAVLTree<Key, Data>::SmallRightRotate(TTreeItem<Key, Data>* p)
{
  // Use if (abs(Height(R) - Height(b)) == 2 && Height(C) <= Height(L))
  //   r            r             
  //    \            \
  //     a            b
  //    / \    ->    / \
  //   b   R        L   a
  //  / \              / \ 
  // L   C            C   R
  try {
    Find(p->GetKeyAddress());
  }
  catch (...) {
    return;
  }

  TTreeItem<Key, Data>* tmp = root, *tmp1;

  if (root->GetKey() == p->GetKey()) {
    tmp1 = root->GetLeft()->GetRight();
    root->GetLeft()->SetRight(root);
    root = root->GetLeft();
    root->GetRight()->SetLeft(tmp1);
    return;
  }

  while (1) {
    if (tmp->GetRight()->GetKey() == p->GetKey()) {
      tmp1 = tmp->GetRight()->GetLeft()->GetRight();
      tmp->GetRight()->GetLeft()->SetRight(tmp->GetRight());
      tmp->SetRight(tmp->GetRight()->GetLeft());
      tmp->GetRight()->GetRight()->SetLeft(tmp1);
      break;
    }

    if (tmp->GetLeft()->GetKey() == p->GetKey()) {
      tmp1 = tmp->GetLeft()->GetLeft()->GetRight();
      tmp->GetLeft()->GetLeft()->SetRight(tmp->GetLeft());
      tmp->SetLeft(tmp->GetLeft()->GetLeft());
      tmp->GetLeft()->GetRight()->SetLeft(tmp1);
      break;
    }

    if (tmp->GetKey() > p->GetKey())
      tmp = tmp->GetLeft();
    else if (tmp->GetKey() < p->GetKey())
      tmp = tmp->GetRight();
  }
}

template<class Key, class Data>
inline void TAVLTree<Key, Data>::RightRotate(TTreeItem<Key, Data>* p)
{
  // Use if (abs(Height(R) - Height(b)) == 2 && Height(c) > Height(L))
  //    r           r 
  //     \           \
  //      a           c
  //     / \         /  \
  //    b   R  ->   b     a
  //   / \         / \   / \
  //  L   c       L   M  N  R
  //     / \
  //    M   N

  try {
    Find(p->GetKeyAddress());
  }
  catch (...) {
    return;
  }

  TTreeItem<Key, Data>* tmp = root, *tmp1;

  if (root->GetKey() == p->GetKey()) {
    tmp1 = root->GetLeft()->GetRight();                                // c
    tmp1->SetLeft(root->GetLeft());                                    // c.left = b
    tmp1->SetRight(root);                                              // c.right = a
    tmp1->GetRight()->SetLeft(root->GetLeft()->GetRight()->GetRight());// c.right.left = N
    tmp1->GetLeft()->SetRight(root->GetLeft()->GetRight()->GetLeft()); // c.left.right = M
    root = tmp1;                                                       // a = c
    return;
  }

  while (1)
  {
    if (tmp->GetRight()->GetKey() == p->GetKey()) {
      tmp1 = tmp->GetRight()->GetLeft()->GetRight();
      tmp1->SetLeft(tmp->GetRight()->GetLeft());
      tmp1->SetRight(tmp->GetRight());
      tmp1->GetRight()->SetLeft(tmp->GetRight()->GetLeft()->GetRight()->GetRight());
      tmp1->GetLeft()->SetRight(tmp->GetRight()->GetLeft()->GetRight()->GetRight());
      tmp->SetRight(tmp1);
      break;
    }

    if (tmp->GetLeft()->GetKey() == p->GetKey()) {
      tmp1 = tmp->GetLeft()->GetLeft()->GetRight();
      tmp1->SetLeft(tmp->GetLeft()->GetLeft());
      tmp1->SetRight(tmp->GetLeft());
      tmp1->GetRight()->SetLeft(tmp->GetLeft()->GetLeft()->GetRight()->GetRight());
      tmp1->GetLeft()->SetRight(tmp->GetLeft()->GetLeft()->GetRight()->GetRight());
      tmp->SetLeft(tmp1);
      break;
    }

    if (tmp->GetKey() > p->GetKey())
      tmp = tmp->GetLeft();
    else if (tmp->GetKey() < p->GetKey())
      tmp = tmp->GetRight();
  }
}

template<class Key, class Data>
inline void TAVLTree<Key, Data>::SmallLeftRotate(TTreeItem<Key, Data>* p)
{
  // Use if (abs(Height(L) - Height(b)) == 2 && Height(C) <= Height(R))
  //   r            r             
  //    \            \
  //     a            b
  //    / \    ->    / \
  //   L   b        a   R
  //      / \      / \ 
  //     C   R    L   C
  try {
    Find(p->GetKeyAddress());
  }
  catch (...) {
    return;
  }

  TTreeItem<Key, Data>* tmp = root, *tmp1;

  if (root->GetKey() == p->GetKey()) {
    tmp1 = root->GetRight()->GetLeft();
    root->GetRight()->SetLeft(root);
    root = root->GetRight();
    root->GetLeft()->SetRight(tmp1);
    return;
  }
  while (1) {
    if (tmp->GetRight()->GetKey() == p->GetKey()) {
      tmp1 = tmp->GetRight()->GetRight()->GetLeft();
      tmp->GetRight()->GetRight()->SetLeft(tmp->GetRight());
      tmp->SetRight(tmp->GetRight()->GetRight());
      tmp->GetRight()->GetLeft()->SetRight(tmp1);
      break;
    }

    if (tmp->GetLeft()->GetKey() == p->GetKey()) {
      tmp1 = tmp->GetLeft()->GetRight()->GetLeft();
      tmp->GetLeft()->GetRight()->SetLeft(tmp->GetLeft());
      tmp->SetLeft(tmp->GetLeft()->GetRight());
      tmp->GetLeft()->GetLeft()->SetRight(tmp1);
      break;
    }

    if (tmp->GetKey() > p->GetKey())
      tmp = tmp->GetLeft();
    else if (tmp->GetKey() < p->GetKey())
      tmp = tmp->GetRight();
  }
}

template<class Key, class Data>
inline void TAVLTree<Key, Data>::LeftRotate(TTreeItem<Key, Data>* p)
{
  // Use if (abs(Height(L) - Height(b)) == 2 && Height(c) > Height(R))
  //    r            r 
  //     \            \
  //      a            c
  //     / \          /  \
  //    L   b  ->    a     b
  //       / \      / \   / \
  //      c   R    L   M  N  R
  //     / \
  //    M   N

  try {
    Find(p->GetKeyAddress());
  }
  catch (...) {
    return;
  }

  TTreeItem<Key, Data>* tmp = root, *tmp1;

  if (root->GetKey() == p->GetKey()) {
    tmp1 = root->GetRight()->GetLeft();                                // c
    tmp1->SetLeft(root);                                               // c.left = b
    tmp1->SetRight(root->GetRight());                                  // c.right = a
    tmp1->GetRight()->SetLeft(root->GetRight()->GetLeft()->GetRight());// c.right.left = N
    tmp1->GetLeft()->SetRight(root->GetRight()->GetLeft()->GetLeft()); // c.left.right = M
    root = tmp1;                                                       // a = c
    return;
  }
  while (1) {
    if (tmp->GetRight()->GetKey() == p->GetKey()) {
      tmp1 = tmp->GetRight()->GetRight()->GetLeft();
      tmp1->SetLeft(tmp->GetRight());
      tmp1->SetRight(tmp->GetRight()->GetRight());
      tmp1->GetRight()->SetLeft(tmp->GetRight()->GetRight()->GetLeft()->GetRight());
      tmp1->GetLeft()->SetRight(tmp->GetRight()->GetRight()->GetLeft()->GetLeft());
      tmp = tmp1;
      break;
    }

    if (tmp->GetLeft()->GetKey() == p->GetKey()) {
      tmp1 = tmp->GetLeft()->GetRight()->GetLeft();
      tmp1->SetLeft(tmp->GetLeft());
      tmp1->SetRight(tmp->GetLeft()->GetRight());
      tmp1->GetRight()->SetLeft(tmp->GetLeft()->GetRight()->GetLeft()->GetRight());
      tmp1->GetLeft()->SetRight(tmp->GetLeft()->GetRight()->GetLeft()->GetLeft());
      tmp = tmp1;
      break;
    }

    if (tmp->GetKey() > p->GetKey())
      tmp = tmp->GetLeft();
    else if (tmp->GetKey() < p->GetKey())
      tmp = tmp->GetRight();
  }
}
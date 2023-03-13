#include "TableLib.h"
#include "TreeItem.h"
#include "Stack.h"
#include <queue>
template<typename key,typename data>
class TTreeMap : public TMap<key, data>
{
protected:
  int count;
  TTreeItem<key, data>* root;
public:
  TTreeMap();
  TTreeMap(const TTreeMap<key, data>& p);
  ~TTreeMap();
  data& operator[](const key& k);
  data* Find(const key& k);
  void Add(key* k, data* d);
  void Delete(const key& k);
  void Add(TTreeItem<key, data>* tree);
};

template<typename key, typename data>
inline TTreeMap<key, data>::TTreeMap()
{
  count = 0;
  root = nullptr;
}

template<typename key, typename data>
inline TTreeMap<key, data>::TTreeMap(const TTreeMap<key, data>& p)
{
  if (p.root == nullptr)
  {
    root = nullptr;
    return*this;
  }
  TTreeItem *A, *B;
  TStack Stack1, Stack2;
  root = new TTreeItem(p.root);
  Stack1.Push(root);
  Stack2.Push(p.root);
  while (!Stack2.IsEmpty())
  {
    A = Stack1.Pop();
    B = Stack2.Pop();
    if (B->GetLeft() != nullptr)
    {
      A->SetLeft(new TTreeItem(*B->GetLeft()));
      Stack1.Push(A.GetLeft());
      Stack2.Push(B.GetLeft());
    }
    if (B->GetRight() != nullptr)
    {
      A->SetRight(new TTreeItem(*B->GetRight()));
      Stack1.Push(A.GetRight());
      Stack2.Push(B.GetRight());
    }
  }
  count = p.count;
  return*this;
}

template<typename key, typename data>
inline TTreeMap<key, data>::~TTreeMap()
{
  if (root != nullptr)
  {
    Queue<TTreeItem<k, d>> q(count);
    q.Push(root);
    while (count != 0)
    {
      if (root->GetLeft() != nullptr)
        q.Push(root->GetLeft());
      if (root->GetRight() != nullptr)
        q.Push(root->GetRight());
      delete root;
      root = q.Pop();
    }
    delete root;
    root = nullptr;
  }
}

template<typename key, typename data>
inline data& TTreeMap<key, data>::operator[](const key& k)
{
}

template<typename key, typename data>
inline data* TTreeMap<key, data>::Find(const key& k)
{
  return nullptr;
}

template<typename key, typename data>
inline void TTreeMap<key, data>::Add(key* k, data* d)
{
}

template<typename key, typename data>
inline void TTreeMap<key, data>::Delete(const key& k)
{
}

template<typename key, typename data>
inline void TTreeMap<key, data>::Add(TTreeItem<key, data>* tree)
{
}

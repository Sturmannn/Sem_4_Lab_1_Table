#pragma once
#include "Item.h"
#include <stack>

//using std::stack;


template <typename Key, typename Data>
class TTreeItem : public TItem<Key, Data>
{
protected:

  TTreeItem<Key, Data>* left;
  TTreeItem<Key, Data>* right;

public:

  TTreeItem<Key, Data>();
  TTreeItem<Key, Data>(TTreeItem<Key, Data>* _left, TTreeItem<Key, Data>* _right, Key* _key = nullptr, Data* _data = nullptr);
  TTreeItem<Key, Data>(const TTreeItem<Key, Data>& _item);
  ~TTreeItem<Key, Data>() = default;


  const TTreeItem<Key, Data>* GetLeft(void) const;
  const TTreeItem<Key, Data>* GetRight(void) const;

  void SetLeft(TTreeItem<Key, Data>* _left);
  void SetRight(TTreeItem<Key, Data>* _right);

};

template<typename Key, typename Data>
inline TTreeItem<Key, Data>::TTreeItem()
{
  this->left = nullptr;
  this->right = nullptr;
  this->key = nullptr;
  this->data = nullptr;
}

template<typename Key, typename Data>
inline TTreeItem<Key, Data>::TTreeItem(TTreeItem<Key, Data>* _left, TTreeItem<Key, Data>* _right, Key* _key, Data* _data)
{
  this->key = _key;
  this->data = _data;
  this->left = _left;
  this->right = _right;
}

template<typename Key, typename Data>
inline TTreeItem<Key, Data>::TTreeItem(const TTreeItem<Key, Data>& _item)
{
  this->left = _item.left;
  this->right = _item.right;
  this->key = _item.key;
  this->data = _item.data;
}

template<typename Key, typename Data>
inline const TTreeItem<Key, Data>* TTreeItem<Key, Data>::GetLeft(void) const
{
  return left;
}

template<typename Key, typename Data>
inline const TTreeItem<Key, Data>* TTreeItem<Key, Data>::GetRight(void) const
{
  return right;
}

template<typename Key, typename Data>
inline void TTreeItem<Key, Data>::SetLeft(TTreeItem<Key, Data>* _left)
{
  this->left = _left;
}

template<typename Key, typename Data>
inline void TTreeItem<Key, Data>::SetRight(TTreeItem<Key, Data>* _right)
{
  this->right = _right;
}

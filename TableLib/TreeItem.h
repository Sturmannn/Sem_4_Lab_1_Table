#pragma once
#include "Item.h"


template <typename Key, typename Data>
class TTreeItem : public TItem<Key, Data>
{
protected:

  TTreeItem<Key, Data>* left;
  TTreeItem<Key, Data>* right;

public:

  TTreeItem(Key* _key = nullptr, Data* _data = nullptr);
  TTreeItem<Key, Data>
};
#include "Item.h"
template <typename key, typename data>
class TTreeItem : public TItem<key,data>
{
protected:
  TTreeItem<key, data>* left;
  TTreeItem<key, data>* right;
public:
  TTreeItem(TTreeItem<key, data>* l, TTreeItem<key, data>* r, key* k = nullptr, data* d = nullptr);
  TTreeItem(const TTreeItem<key, data>& p);
  TTreeItem<key, data>* GetLeft();
  TTreeItem<key, data>* GetRight();
  void SetLeft(TTreeItem<key, data>* l);
  void SetRight(TTreeItem<key, data>* r);
};

template<typename key, typename data>
inline TTreeItem<key, data>::TTreeItem(TTreeItem<key, data>* l, TTreeItem<key, data>* r, key* k, data* d)
{

}

template<typename key, typename data>
inline TTreeItem<key, data>::TTreeItem(const TTreeItem<key, data>& p)
{

}

template<typename key, typename data>
inline TTreeItem<key, data>* TTreeItem<key, data>::GetLeft()
{
  return nullptr;
}

template<typename key, typename data>
inline TTreeItem<key, data>* TTreeItem<key, data>::GetRight()
{
  return nullptr;
}

template<typename key, typename data>
inline void TTreeItem<key, data>::SetLeft(TTreeItem<key, data>* l)
{
}

template<typename key, typename data>
inline void TTreeItem<key, data>::SetRight(TTreeItem<key, data>* r)
{
}

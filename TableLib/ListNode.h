#pragma once

template <class T>
class TListNode
{
protected:
  T data;
  TListNode<T>* next;
  TListNode<T>* prev;
public:
  TListNode();
  TListNode(T d);
  TListNode(T d, TListNode<T>* n, TListNode<T>* p);
  TListNode(const TListNode<T>& p);
  
  T& GetData();
  TListNode<T>* GetNext();
  TListNode<T>* GetPrev();

  void SetData(T d);
  void SetNext(TListNode<T>* n);
  void SetPrev(TListNode<T>* p);
};

template<class T>
inline TListNode<T>::TListNode()
{
  next = nullptr;
  prev = nullptr;
}

template<class T>
inline TListNode<T>::TListNode(T d)
{
  next = nullptr;
  prev = nullptr;
  data = d;
}

template<class T>
inline TListNode<T>::TListNode(T d, TListNode<T>* n, TListNode<T>* p)
{
  next = n;
  prev = p;
  data = d;
}

template<class T>
inline TListNode<T>::TListNode(const TListNode<T>& p)
{
  data = p.data;
  prev = p.prev;
  next = p.next;

}

template<class T>
inline T& TListNode<T>::GetData()
{
  return data;
}

template<class T>
inline TListNode<T>* TListNode<T>::GetNext()
{
  return next;
}

template<class T>
inline TListNode<T>* TListNode<T>::GetPrev()
{
  return prev;
}

template<class T>
inline void TListNode<T>::SetData(T d)
{
  data = d;
}

template<class T>
inline void TListNode<T>::SetNext(TListNode<T>* n)
{
  next = n;
}

template<class T>
inline void TListNode<T>::SetPrev(TListNode<T>* p)
{
  prev = p;
}

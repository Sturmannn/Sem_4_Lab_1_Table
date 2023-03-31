#pragma once

#include "ListNode.h"

template <typename T>
class TList
{
protected:
  TListNode<T>* start;
  TListNode<T>* end;
  int count;
public:
  TList();
  TList(const TList<T>& p);
  ~TList();

  void PushStart(T data);
  void PushEnd(T data);
  void Push(T data, size_t i);

  T GetStart();
  T GetEnd();
  T& Get(size_t i);
  int GetCount();

  void DelStart();
  void DelEnd();
  void Del(size_t i);
  bool IsEmp();
  bool IsFull();

  T& operator[](const size_t i);
};

template<typename T>
inline TList<T>::TList()
{
  start = nullptr;
  end = nullptr;
  count = 0;
}

template<typename T>
inline TList<T>::TList(const TList<T>& p)
{
  start = new TListNode<T>(*(p.start));
  TListNode<T>* i = p.start->GetNext();
  TListNode<T>* j = start;

  while (i != nullptr)
  {
    j->SetNext(new TListNode<T>(*i));
    j->GetNext()->SetPrev(j);
    j = j->GetNext();
    i = i->GetNext();
  }
  end = j;
  count = p.count;
}

template<typename T>
inline TList<T>::~TList()
{
  if (start != nullptr)
  {
    TListNode<T>* j = start;

    while (j != nullptr)
    {
      TListNode<T>* tmp = j;
      j = j->GetNext();
      delete tmp;
    }
    start = nullptr;
    end = nullptr;
  }
}

template<typename T>
inline void TList<T>::PushStart(T data)
{
  if (IsFull())
    throw "Array is full";
  TListNode<T>* tmp = new TListNode<T>(data);
  tmp->SetNext(start);
  if (start != nullptr)
    start->SetPrev(tmp);
  start = tmp;
  count++;
}

template<typename T>
inline void TList<T>::PushEnd(T data)
{
  if (IsFull())
    throw "Full";
  TListNode<T>* tmp = new TListNode<T>(data);
  tmp->SetPrev(start);
  if (end != nullptr)
    end->SetNext(tmp);
  end = tmp;
  count++;
}

template<typename T>
inline void TList<T>::Push(T data, size_t i)
{
  if (IsFull())
    throw "Full";
  if (i < 0 || i > count)
    throw "Error index";

  TListNode<T>* j = start;
  int k = 0;
  while (j != nullptr)
  {
    if (k == i)
      break;

    j = j->GetNext();
    k++;
  }
  return j->GetData();
}

template<typename T>
inline T TList<T>::GetStart()
{
  return start->GetData();
}

template<typename T>
inline T TList<T>::GetEnd()
{
  return end->GetData();
}

template<typename T>
inline T& TList<T>::Get(size_t i)
{
  if (IsEmp())
    throw "Empty";
  if (i<0 || i> count)
    throw "Error index";

  TListNode<T>* j = start;
  int k = 0;
  while (j != nullptr)
  {
    if (k == i)
      break;

    j = j->GetNext();
    k++;
  }
  return j->GetData();
}

template<typename T>
inline void TList<T>::DelStart()
{
  if (IsEmp())
    throw "Empty";
  TListNode<T>* tmp = start;
  start = start->GetNext();
  if (start != nullptr)
    start->SetPrev(nullptr);
  delete tmp;
  count--;
}

template<typename T>
inline void TList<T>::DelEnd()
{
  if (IsEmp())
    throw "Empty";
  TListNode<T>* tmp = end;
  end = end->GetPrev();
  if (end != nullptr)
    end->SetNext(nullptr);
  delete tmp;
  count--;
}

template<typename T>
inline void TList<T>::Del(size_t i)
{
}

template<typename T>
inline bool TList<T>::IsEmp()
{
  return count <= 0;
}

template<typename T>
inline bool TList<T>::IsFull()
{
  return false;
}

template<typename T>
inline T& TList<T>::operator[](const size_t i)
{
  
}

template<typename T>
inline int TList<T>::GetCount()
{
  return count;
}

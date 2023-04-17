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
  void Push(T data);

  T GetStart();
  TListNode<T>*& GetStartNode();
  T GetEnd();
  TListNode<T>*& GetEndNode();
  T& Get(size_t i);
  int GetCount();

  void DelStart();
  void DelEnd();
  void Del(size_t i);
  bool IsEmp();
  bool IsFull();

  TList<T>& operator=(const TList<T>& L);
  T& operator[](size_t i);
  bool operator!=(const TList<T>& L);
  bool operator==(const TList<T>& L);
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
  tmp->SetPrev(end);
  if (end != nullptr)
    end->SetNext(tmp);
  end = tmp;
  count++;
}

template<typename T>
inline void TList<T>::Push(T data)
{
  if (IsFull())
    throw "Full";

  if (start == nullptr)
    start = new TListNode<T>(data);
  else if (end == nullptr)
  {
    end = new TListNode<T>(data);
    start->SetNext(end);
    end->SetPrev(start);
  }
  else
  {
    TListNode<T>* tmp = new TListNode<T>(data);
    tmp->SetPrev(end);
    end->SetNext(tmp);
    end = tmp;
  }
  count++;
}

template<typename T>
inline T TList<T>::GetStart()
{
  return start->GetData();
}

template<typename T>
inline TListNode<T>*& TList<T>::GetStartNode()
{
  return start;
}

template<typename T>
inline T TList<T>::GetEnd()
{
  return end->GetData();
}

template<typename T>
inline TListNode<T>*& TList<T>::GetEndNode()
{
  return end;
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
  if (j == nullptr)
    throw "Error";
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
  if (IsEmp())
    throw "Empty";
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

  TListNode<T>* tmp = j;
  if (j->GetNext() != nullptr && j->GetPrev() != nullptr)
  {
    tmp->GetPrev()->SetNext(tmp->GetNext());
    tmp->GetNext()->SetPrev(tmp->GetPrev());
  }
  else if (j->GetPrev() != nullptr)
  {
    tmp->GetPrev()->SetNext(nullptr);
    this->GetEndNode() = tmp->GetPrev();
  }

  if (j != nullptr)
  {
    count--;
    delete j;
    j = nullptr;
  }
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
inline TList<T>& TList<T>::operator=(const TList<T>& L)
{
  if (start == L.start || end == L.end)
    return *this;

  if (count != 0)
  {
    TListNode<T>* tmp = start;
    while (tmp != end)
    {
      tmp = tmp->GetNext();
      delete tmp->GetPrev();
    }
    delete end;
    count = 0;
  }
  start = nullptr;
  end = nullptr;

  if (L.count != 0)
  {
    TListNode<T>* tmp = L.start;
    for (size_t i = 0; i < L.count; i++)
    {
      this->Push(tmp->GetData());
      tmp = tmp->GetNext();
    }
  }
  return *this;
}

template<typename T>
inline T& TList<T>::operator[](size_t i)
{
  if (IsEmp())
    throw;
  int tmpi = (i < count) ? i : i % count;
  TListNode<T>* tmp;
  tmp = start;
  for (size_t k = 0; k < tmpi; k++)
    tmp = tmp->GetNext();
  return tmp->GetData();
}

template<typename T>
inline bool TList<T>::operator!=(const TList<T>& L)
{
  return !(operator==(L));
}

template<typename T>
inline bool TList<T>::operator==(const TList<T>& L)
{
  if (IsEmpty() && l.IsEmpty())
    return true;
  if (count != l.count)
    return false;
  TListItem<T>* i = start;
  TListItem<T>* j = l.start;
  while (i != end)
  {
    if (i->data != j->data)
      return false;
    i = i->next;
    j = j->next;
  }
  return (end->data == l.end->data);
}

template<typename T>
inline int TList<T>::GetCount()
{
  return count;
}

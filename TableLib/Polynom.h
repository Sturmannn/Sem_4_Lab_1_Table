#pragma once

#include "Monom.h"
#include "List.h"

class TPolynom : public TList<TMonom>
{
protected:
  int N;
  void Delete();
public:
  TPolynom(int n);
  TPolynom(const TPolynom& p);
  virtual ~TPolynom();

  size_t GetN();
  TPolynom operator + (const TPolynom& p);
  TPolynom operator - (const TPolynom& p);
  TPolynom operator * (const TPolynom& p);
  TPolynom& operator = (const TPolynom& p);
  TPolynom& operator += (const TMonom& p);
  TMonom& operator[](const size_t i);
};

inline void TPolynom::Delete()
{
  TPolynom::~TPolynom();
}

TPolynom::TPolynom(int n)
{
  if (n < 1)
    throw "N < 1";
  N = n;
}

TPolynom::TPolynom(const TPolynom& p) : TList::TList(p)
{
  N = p.N;
}

TPolynom::~TPolynom(){}

size_t TPolynom::GetN()
{
  return N;
}

TPolynom TPolynom::operator+(const TPolynom& p)
{
  TPolynom res(N);
  TListNode<TMonom>* i = start;
  TListNode<TMonom>* j = p.start;

  while (i != nullptr || j != nullptr)
  {
    if (i->GetData() == j->GetData())
    {
      TMonom tmp(i->GetData().GetK() + j->GetData().GetK(), i->GetData().GetA(), N);
      res.PushEnd(tmp);
      i = i->GetNext();
      j = j->GetNext();
    }
    else if (i->GetData() > j->GetData())
    {
      res.PushEnd(i->GetData());
      i = i->GetNext();
    }
    else
    {
      res.PushEnd(j->GetData());
      j = j->GetNext();
    }
  }
  if (i == nullptr)
  {
    while (j != nullptr)
    {
      res.PushEnd(j->GetData());
      j = j->GetNext();
    }
  }
  if (j == nullptr)
    while (i != nullptr)
    {
      res.PushEnd(i->GetData());
      i = i->GetNext();
    }
  return res;
}

TPolynom TPolynom::operator-(const TPolynom& p)
{
  TPolynom res(N);
  TListNode<TMonom>* i = start;
  TListNode<TMonom>* j = p.start;

  while (i != nullptr || j != nullptr)
  {
    if (i->GetData() == j->GetData())
    {
      double newk = i->GetData().GetK() - j->GetData().GetK();
      if (newk != 0)
      {
        TMonom tmp(newk, i->GetData().GetA(), N);
        res.PushEnd(tmp);
        i = i->GetNext();
        j = j->GetNext();
      }
    }
    else if (i->GetData() > j->GetData())
    {
      res.PushEnd(i->GetData());
      i = i->GetNext();
    }
    else
    {
      res.PushEnd(j->GetData());
      j = j->GetNext();
    }
  }
  if (i == nullptr)
  {
    while (j != nullptr)
    {
      res.PushEnd(j->GetData());
      j = j->GetNext();
    }
  }
  if (j == nullptr)
    while (i != nullptr)
    {
      res.PushEnd(i->GetData());
      i = i->GetNext();
    }
  return res;
}

TPolynom TPolynom::operator*(const TPolynom& p)
{
  TPolynom res(N);
  TListNode<TMonom>* i = start;
  TListNode<TMonom>* j = p.start;

  while (i != nullptr)
  {
    while (j != nullptr)
    {
      int* newA = new int[N];
      for (size_t k = 0; k < N; k++)
        newA[k] = j->GetData()[k] + i->GetData()[k];
      
      TMonom tmp(i->GetData().GetK() * j->GetData().GetK(), newA, N);
      delete[] newA;

      res += tmp;
    }
  }
  return res;
}

TPolynom& TPolynom::operator=(const TPolynom& p)
{
  if (this == &p)
    return *this;
  Delete();
  TList::TList(p);
}

inline TPolynom& TPolynom::operator+=(const TMonom& p)
{
  TListNode<TMonom>* i = this->start;
  if (IsEmp())
    this->PushStart(p);
  TListNode<TMonom>* tmp = new TListNode<TMonom>(p);
  while (i != nullptr)
  {
    if (i->GetData() < p)
    {
      TListNode<TMonom>* a = i->GetPrev();
      if (a == nullptr)
        this->PushStart(p);

      tmp->SetNext(i);
      tmp->SetPrev(a);
      i->SetPrev(tmp);
      a->SetNext(tmp);
      return *this;
    }
    i = i->GetNext();
  }
  this->PushEnd(p);
}

inline TMonom& TPolynom::operator[](const size_t i)
{
  return this->Get(i);
}

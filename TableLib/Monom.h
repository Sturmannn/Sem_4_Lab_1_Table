#pragma once

#include <iostream>

class TMonom
{
protected:
  double K;
  int* A;
  int N;
public:
  TMonom(int n = 1);
  TMonom(const TMonom& p);
  TMonom(double k, int* a, int n);
  TMonom(TMonom&& p) noexcept;
  ~TMonom();

  void SetN(int n);
  void SetK(double k);
  void SetA(int* a);

  double GetK();
  int GetN();
  int* GetA();

  TMonom& operator = (const TMonom& p);
  TMonom& operator = (TMonom&& p) noexcept;
  int& operator [] (const int i);
  bool operator > (const TMonom& p);
  bool operator < (const TMonom& p);
  bool operator == (const TMonom& p);
  friend std::ostream& operator << (std::ostream& o, const TMonom& p)
  {
    o << p.K << " * ";
    for (int i = 0; i < p.N; i++)
    {
      if (i == p.N - 1)
      {
        o << "x^" << p.A[i];
        break;
      }
      if (p.A[i] != 0)
        o << "x^" << p.A[i] << " * ";
    }
    o << std::endl;
    return o;
  }
};
TMonom::TMonom(int n)
{
  if (n < 1)
    throw "Error n";
  K = 0;
  N = n;
  A = new int[n];
  for (size_t i = 0; i < N; i++)
    A[i] = 0;
}

TMonom::TMonom(const TMonom& p)
{
  K = p.K;
  N = p.N;
  if (N == 0)
    A = nullptr;
  else
    A = new int[N];
  for (size_t i = 0; i < N; i++)
    A[i] = p.A[i];
}

TMonom::TMonom(double k, int* a, int n)
{
  if (n < 1)
    throw "Error n";
  if (k < 0)
    throw "Error k";
  K = k;
  N = n;
  A = new int[n];
  for (size_t i = 0; i < N; i++)
    A[i] = a[i];
}

TMonom::TMonom(TMonom&& p) noexcept
{
  K = p.K;
  A = p.A;
  N = p.N;
  p.A = nullptr;
}

TMonom::~TMonom()
{
  if (A != nullptr)
    delete[] A;
  A = nullptr;
}

void TMonom::SetN(int n)
{
  if (A == nullptr)
    delete[] A;
  if (n == 0)
    A = nullptr;
  else
    A = new int[n];
  N = n;
  for (size_t i = 0; i < N; i++)
    A[i] = 0;
}

void TMonom::SetK(double k)
{
  K = k;
}

void TMonom::SetA(int* a)
{
  for (size_t i = 0; i < N; i++)
    A[i] = a[i];
}

double TMonom::GetK()
{
  return K;
}

int TMonom::GetN()
{
  return N;
}

int* TMonom::GetA()
{
  return A;
}

TMonom& TMonom::operator=(const TMonom& p)
{
  if (this == &p)
    return *this;

  if (N != p.N)
  {
    if (A != nullptr)
      delete[] A;
    if (N == 0)
      A = nullptr;
    else
      A = new int[N];
  }

  K = p.K;
  N = p.N;
  for (size_t i = 0; i < N; i++)
    A[i] = p.A[i];
  return *this;
}

TMonom& TMonom::operator=(TMonom&& p) noexcept
{
  K = p.K;
  N = p.N;
  A = p.A;
  p.A = nullptr;
  return *this;
}

int& TMonom::operator[](const int i)
{
  if (i<0 || i>N)
    throw "Error i";
  else
    return A[i];
}

bool TMonom::operator>(const TMonom& p)
{
  if (N != p.N)
    throw "Error N";
  for (size_t i = 0; i < N; i++)
  {
    if (A[i] == p.A[i])
      continue;
    else if (A[i] > p.A[i])
      return true;
    else
      return false;
  }
  return true;
}

bool TMonom::operator<(const TMonom& p)
{
  if (N != p.N)
    throw "Error N";
  bool tmp = true;
  for (size_t i = 0; i < N; i++)
  {
    if (A[i] == p.A[i])
      continue;
    else if (A[i] > p.A[i])
      return false;
    else
      return true;
  }
  return false;
}

bool TMonom::operator==(const TMonom& p)
{
  if (N != p.N)
    throw "Error N";
  bool tmp = true;
  for (size_t i = 0; i < N; i++)
  {
    if (A[i] == p.A[i])
      continue;
    else
      return false;
  }
  return true;;
}
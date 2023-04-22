#pragma once

template <class T>
class TStack
{
protected:
  T* pMem;
  size_t size;
  int top;

public:
  TStack(int sz = 1);
  TStack(const TStack<T>& p);
  TStack(TStack<T>&& p);
  ~TStack();

  size_t Size() const;

  bool isEmpty() const;
  bool isFull() const;

  void Push(const T& val);
  T Pop();
  T Top();
};

template<class T>
inline TStack<T>::TStack(int sz)
{
  if (sz < 1)
    throw "sz < 1";
  size = sz;
  top = -1;
  pMem = new T[size];
}

template<class T>
inline TStack<T>::TStack(const TStack<T>& p)
{
  if (p.pMem == nullptr)
  {
    pMem = nullptr;
    size = 0;
    top = -1;
  }
  else
  {
    size = p.size;
    top = p.top;
    pMem = new T[size];
    for (int i = 0; i < top; i++)
      pMem[i] = p.pMem[i];
  }
}

template<class T>
inline TStack<T>::TStack(TStack<T>&& p)
{
  size = p.size;
  top = p.top;
  pMem = p.pMem;

  p.pMem = nullptr;
  p.size = 0;
  p.top = -1;
}

template<class T>
inline TStack<T>::~TStack()
{
  if (pMem != nullptr)
  {
    delete[] pMem;
    pMem = nullptr;
  }
  size = 0;
  top = -1;
}

template<class T>
inline size_t TStack<T>::Size() const
{
  return top + 1;
}

template<class T>
inline bool TStack<T>::isEmpty() const
{
  if (top == -1)
    return true;
  return false;
}

template<class T>
inline bool TStack<T>::isFull() const
{
  if (top == size - 1)
    return true;
  return false;
}

template<class T>
inline void TStack<T>::Push(const T& val)
{
  if (isFull() == true)
    throw "pMem is full";
  pMem[++top] = val;
}

template<class T>
inline T TStack<T>::Pop()
{
  if (isEmpty() == true)
    throw "pMem is empty";
  return pMem[top--];
}

template<class T>
inline T TStack<T>::Top()
{
  return pMem[top];
}
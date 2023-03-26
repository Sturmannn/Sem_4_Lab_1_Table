#pragma once

template <class T>
class TQueue
{
protected:
  T* pMem;
  size_t sz;//overall size
  size_t size;//count of elements
  size_t head;//first element id
  size_t tail;//last element id
public:
  TQueue(int sz = 1);
  TQueue(const TQueue<T>& p);
  TQueue(TQueue<T>&& p);
  ~TQueue();

  size_t Size() const;

  bool isEmpty() const;
  bool isFull() const;

  void Push(const T& val);
  T Pop();
  T Top();
};

template<typename T>
inline TQueue<T>::TQueue(int sz)
{
  if (sz < 1)
    throw "sz < 1";
  head = 0;
  tail = 0;
  size = 0;
  this->sz = sz;
  pMem = new T[sz];
  for (int i = 0; i < sz; i++)
    pMem[i] = T(0);
}

template<typename T>
inline TQueue<T>::TQueue(const TQueue<T>& p)
{
  if (p.pMem == nullptr)
  {
    pMem = nullptr;
    head = 0;
    tail = 0;
    sz = 0;
    size = 0;
  }
  else
  {
    size = p.size;
    head = p.head;
    tail = p.tail;
    sz = p.sz;
    pMem = new T[sz];
    for (int i = 0; i < tail; i++)
      pMem[i] = p.pMem[i];
  }
}

template<typename T>
inline TQueue<T>::TQueue(TQueue<T>&& p)
{
  size = p.size;
  head = p.head;
  tail = p.tail;
  sz = p.sz;
  pMem = p.pMem;

  p.pMem = nullptr;
  p.head = 0;
  p.size = 0;
  p.sz = 0;
  p.tail = 0;
}

template<typename T>
inline TQueue<T>::~TQueue()
{
  if (pMem != nullptr)
  {
    delete[] pMem;
    pMem = nullptr;
  }
  head = 0;
  size = 0;
  sz = 0;
  tail = 0;
}

template<typename T>
inline size_t TQueue<T>::Size() const
{
  return size;
}

template<typename T>
inline bool TQueue<T>::isEmpty() const
{
  if (size == 0)
    return true;
  return false;
}

template<typename T>
inline bool TQueue<T>::isFull() const
{
  if (size == sz)
    return true;
  return false;
}

template<typename T>
inline void TQueue<T>::Push(const T& val)
{
  if (isFull() == true)
    throw "pMem is full";
  pMem[tail] = val;
  tail = (tail + 1) % sz;
  size++;
}

template<typename T>
inline T TQueue<T>::Pop()
{
  if (isEmpty() == true)
    throw "pMem is empty";
  T val = pMem[head];
  head = (head + 1) % sz;
  size--;
  return val;
}

template<class T>
inline T TQueue<T>::Top()
{
  return pMem[head];
}

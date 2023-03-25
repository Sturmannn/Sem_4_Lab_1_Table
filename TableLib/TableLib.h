template<class Key, class Data>
class TMap
{
protected:
  size_t size;
  size_t count;
  Key** keys;
  Data** items;

public:
  TMap(size_t sz = 20);
  TMap(const TMap<Key, Data>& p);
  ~TMap();
  
  Data& operator [](const Key* k);
  Data& Find(const Key& k);
  int FindId(Key* K);
  void Add(Key* k, Data* d);
  void Del(Key* k);
};

template<class Key, class Data>
inline TMap<Key, Data>::TMap(size_t sz)
{
  size = sz;
  count = 0;
  keys = new Key* [size];
  items = new Data* [size];
  for (int i = 0; i < size; i++)
  {
    keys[i] = nullptr;
    items[i] = nullptr;
  }
}

template<class Key, class Data>
inline TMap<Key, Data>::TMap(const TMap<Key, Data>& p)
{
  size = p.size;
  count = p.count;
  keys = new Key * [size];
  items = new Data * [size];
  for (int i = 0; i < size; i++)
  {
    keys[i] = p.keys[i];
    items[i] = p.items[i];
  }
}

template<class Key, class Data>
inline TMap<Key, Data>::~TMap()
{
  if(!keys)
    delete[]keys;
  if (!keys)
    delete[]items;
  keys = nullptr;
  items = nulltptr;
  count = 0;
  size = 0;
}

template<class Key, class Data>
inline Data& TMap<Key, Data>::operator[](const Key* k)
{
  try 
  {
    return Find(*k);//проверяем, можно ли вернуть данные с ключом k
  }
  catch(const char* msg)//если не получилось, заходим в обработчик исключений
  {
    Add(k, new Data());//добавляем в таблиу данные с ключом k
    return *(items[count]);//возвращаем новые данные и выводим сообщение, написанное в операторе throw метода Find(const Key& k)
  }
}

template<class Key, class Data>
inline Data& TMap<Key, Data>::Find(const Key& k)
{
  for (int i = 0; i < count; i++)
  {
    if ((keys[i]) == k)
      return *(items[i]);
  }
  throw "Cant find Data with Key k";
}

template<class Key, class Data>
inline int TMap<Key, Data>::FindId(Key* K)
{
  for (int i = 0; i < count; i++)
  {
    if ((keys[i]) == k)
      return i;
  }
  throw "Cant find Data with Key k";
}

template<class Key, class Data>
inline void TMap<Key, Data>::Add(Key* k, Data* d)
{
  keys[count] = k;
  items[count] = d;
  count++;
}

template<class Key, class Data>
inline void TMap<Key, Data>::Del(Key* k)
{
  int i = FindId(k);
  for (; i < count - 1; i++)
  {
    keys[i] = keys[i + 1];
    items[i] = items[i + 1];
  }
  keys(count) :nullptr;
  count--;
}

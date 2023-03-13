template<typename key, typename data>
class TMap
{
protected:
  size_t size;
  size_t count;
  key** keys;
  data** items;

public:
  TMap(size_t sz = 20);
  TMap(const TMap<key, data>& p);
  ~TMap();
  
  data& operator [](const key* k);
  data& Find(const key& k);
  int FindId(key* K);
  void Add(key* k, data* d);
  void Del(key* k);
};

template<typename key, typename data>
inline TMap<key, data>::TMap(size_t sz)
{
  size = sz;
  count = 0;
  keys = new key* [size];
  items = new data* [size];
  for (int i = 0; i < size; i++)
  {
    keys[i] = nullptr;
    items[i] = nullptr;
  }
}

template<typename key, typename data>
inline TMap<key, data>::TMap(const TMap<key, data>& p)
{
  size = p.size;
  count = p.count;
  keys = new key * [size];
  items = new data * [size];
  for (int i = 0; i < size; i++)
  {
    keys[i] = p.keys[i];
    items[i] = p.items[i];
  }
}

template<typename key, typename data>
inline TMap<key, data>::~TMap()
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

template<typename key, typename data>
inline data& TMap<key, data>::operator[](const key* k)
{
  try 
  {
    return Find(*k);//проверяем, можно ли вернуть данные с ключом k
  }
  catch(const char* msg)//если не получилось, заходим в обработчик исключений
  {
    Add(k, new Data());//добавляем в таблиу данные с ключом k
    return *(items[count]);//возвращаем новые данные и выводим сообщение, написанное в операторе throw метода Find(const key& k)
  }
}

template<typename key, typename data>
inline data& TMap<key, data>::Find(const key& k)
{
  for (int i = 0; i < count; i++)
  {
    if ((keys[i]) == k)
      return *(items[i]);
  }
  throw "Cant find data with key k";
}

template<typename key, typename data>
inline int TMap<key, data>::FindId(key* K)
{
  for (int i = 0; i < count; i++)
  {
    if ((keys[i]) == k)
      return i;
  }
  throw "Cant find data with key k";
}

template<typename key, typename data>
inline void TMap<key, data>::Add(key* k, data* d)
{
  keys[count] = k;
  items[count] = d;
  count++;
}

template<typename key, typename data>
inline void TMap<key, data>::Del(key* k)
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

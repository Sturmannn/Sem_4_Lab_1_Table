
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
  void Add(key* k, data* d);
  void Del(key* k);
};

template<typename key, typename data>
inline TMap<key, data>::TMap(size_t sz)
{
  size = sz;
  count = 0;
  keys = new key * [size];
  items = new data * [size];
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
}

template<typename key, typename data>
inline data& TMap<key, data>::operator[](const key* k)
{
  
}

template<typename key, typename data>
inline data& TMap<key, data>::Find(const key& k)
{
  // TODO: вставьте здесь оператор return
}

template<typename key, typename data>
inline void TMap<key, data>::Add(key* k, data* d)
{
}

template<typename key, typename data>
inline void TMap<key, data>::Del(key* k)
{
}

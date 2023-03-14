template<typename key,typename data>
class TItem
{
protected:
	key* ke;
	data* dat;
public:
	TItem(key* k = nullptr, data* d = nullptr);
	key* GetKey();
	void SetKey(key* k);
	data* GetData();
	void SetData(data* d);
	bool operator==(const TItem<key, data>& p);

};

template<typename key, typename data>
inline TItem<key, data>::TItem(key* k, data* d)
{
	key = k;
	data = d;
}

template<typename key, typename data>
inline key* TItem<key, data>::GetKey()
{
	return ke;
}

template<typename key, typename data>
inline void TItem<key, data>::SetKey(key* k)
{
	ke = k;
}

template<typename key, typename data>
inline data* TItem<key, data>::GetData()
{
	return dat;
}

template<typename key, typename data>
inline void TItem<key, data>::SetData(data* d)
{
	dat = d;
}

template<typename key, typename data>
inline bool TItem<key, data>::operator==(const TItem<key, data>& p)
{
	if (this->ke == p.key)
		return true;
	return false;
}

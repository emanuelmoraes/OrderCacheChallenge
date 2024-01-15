#include <iostream>
#include <unordered_map>
#include <list>
#include <utility>
#include <shared_mutex>

template <typename Key, typename Value>
class ThreadSafeCache
{
private:
	struct CacheItem
	{
		Value value;
		typename std::list<Key>::iterator it;
	};

	std::unordered_map<Key, CacheItem> cacheMap;
	std::list<Key> itemList;
	size_t capacity;
	mutable std::shared_mutex mutex;
	unsigned int index;

public:
	ThreadSafeCache(size_t cap) : capacity(cap)
	{
		cacheMap.reserve(size);
		index = 1;
	}

	unsigned int getIndex() { return index; }

	void put(const Key& key, const Value& value);
	bool get(const Key& key, Value& value);
	bool exists(const Key& key);
	void remove(const Key& key);
	size_t size() const;
};

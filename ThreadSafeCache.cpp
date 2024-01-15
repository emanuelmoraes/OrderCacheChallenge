#include "ThreadSafeCache.h"

template<typename Key, typename Value>
void ThreadSafeCache<Key, Value>::put(const Key & key, const Value & value)
{
	std::unique_lock lock(mutex); // Lock for writing
	auto it = cacheMap.find(key);

	if (it != cacheMap.end()) {
		// Update existing item
		itemList.erase(it->second.it);
		itemList.push_front(key);
		it->second.value = value;
		it->second.it = itemList.begin();
	}
	else {
		// Insert new item
		if (itemList.size() >= capacity) {
			// Remove least recently used item
			cacheMap.erase(itemList.back());
			itemList.pop_back();
		}
		itemList.push_front(key);
		cacheMap[key] = { value, itemList.begin() };
	}
}

template<typename Key, typename Value>
bool ThreadSafeCache<Key, Value>::get(const Key& key, Value& value)
{
	std::shared_lock lock(mutex); // Lock for reading
	auto it = cacheMap.find(key);
	if (it == cacheMap.end()) {
		return false; // Not found
	}

	// Move the accessed item to the front
	itemList.splice(itemList.begin(), itemList, it->second.it);
	value = it->second.value;
	return true;
}

template<typename Key, typename Value>
bool ThreadSafeCache<Key, Value>::exists(const Key& key)
{
	std::shared_lock lock(mutex); // Lock for reading
	return cacheMap.find(key) != cacheMap.end();
}

template<typename Key, typename Value>
void ThreadSafeCache<Key, Value>::remove(const Key& key)
{
	std::unique_lock lock(mutex); // Lock for writing
	auto it = cacheMap.find(key);
	if (it != cacheMap.end()) {
		itemList.erase(it->second.it);
		cacheMap.erase(it);
	}
}

template<typename Key, typename Value>
size_t ThreadSafeCache<Key, Value>::size() const
{
	std::shared_lock lock(mutex); // Lock for reading
	return cacheMap.size();
}

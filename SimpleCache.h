#pragma once
#include <iostream>
#include <unordered_map>
#include <list>
#include <utility>
#include "OrderCache.h"
#include <algorithm>

class SimpleCache
{
private:
	std::unordered_map<int, std::pair<Order, std::list<int>::iterator>> cacheMap;
	std::list<int> itemList;
	size_t capacity;
	unsigned int index;

public:
	SimpleCache(size_t size) : capacity(size)
	{
		cacheMap.reserve(size);
		index = 1;
	}

	unsigned int getIndex() { return index; }

	void put(int key, const Order& value)
	{
		auto it = cacheMap.find(key);

		if (it != cacheMap.end()) 
		{
			it->second.first = std::ref(value);
			itemList.erase(it->second.second);
			itemList.push_front(key);
			it->second.second = itemList.begin();
		}
		else
		{
			if (cacheMap.size() == capacity)
			{
				cacheMap.erase(itemList.back());
				itemList.pop_back();
			}

			itemList.push_front(key);
			cacheMap[key] = { value, itemList.begin() };
		}

		index++;
	}

	bool get(int key, Order& value)
	{
		auto it = cacheMap.find(key);

		if (it == cacheMap.end())
		{
			return false;
		}

		itemList.erase(it->second.second);
		itemList.push_front(key);
		it->second.second = itemList.begin();
		value = it->second.first;
		return true;
	}

	bool find_by_orderid(std::string orderid, Order& value)
	{
		auto it = std::find_if(cacheMap.begin(), cacheMap.end(), [orderid](const auto& pair) {
			return pair.second.first.orderId() == orderid;
		});

		if (it != cacheMap.end()) {
			value = it->second.first;
			return true;
		}
		else {
			return false;
		}
	}

	bool remove_by_orderid(const std::string& orderid)
	{
		auto it = std::find_if(cacheMap.begin(), cacheMap.end(), [&orderid](const auto& pair) {
			return pair.second.first.orderId() == orderid;
		});

		if (it != cacheMap.end()) {
			itemList.erase(it->second.second);
			cacheMap.erase(it);
			index--;
			return true;
		}

		return false;
	}

	bool find_by_user(std::string user, Order& value)
	{
		auto it = std::find_if(cacheMap.begin(), cacheMap.end(), [user](const auto& pair) {
			return pair.second.first.user() == user;
		});

		if (it != cacheMap.end())
		{
			value = it->second.first;
			return true;
		}
		else
		{
			return false;
		}
	}

	void remove_by_user(const std::string& user)
	{
		while (true)
		{
			auto it = std::find_if(cacheMap.begin(), cacheMap.end(), [&user](const auto& pair) {
				return pair.second.first.user() == user;
			});

			if (it != cacheMap.end())
			{
				itemList.erase(it->second.second);
				cacheMap.erase(it);
				index--;
			}
			else
				break;
		}

	}

	bool find_by_securityid(std::string securityid, Order& value)
	{
		auto it = std::find_if(cacheMap.begin(), cacheMap.end(), [securityid](const auto& pair) {
			return pair.second.first.securityId() == securityid;
		});

		if (it != cacheMap.end())
		{
			value = it->second.first;
			return true;
		}
		else
		{
			return false;
		}
	}

	bool find_by_securityid_with_minimum_qty(std::string securityid, unsigned int qty, Order& value)
	{
		auto it = std::find_if(cacheMap.begin(), cacheMap.end(), [securityid, qty](const auto& pair) {
			return pair.second.first.securityId() == securityid && pair.second.first.qty() == qty;
		});

		if (it != cacheMap.end())
		{
			value = it->second.first;
			return true;
		}
		else
		{
			return false;
		}
	}

	void remove_by_securotyid_with_minimum_qty(const std::string& securityid, unsigned int qty)
	{
		while (true)
		{
			auto it = std::find_if(cacheMap.begin(), cacheMap.end(), [&securityid, qty](const auto& pair) {
				return pair.second.first.securityId() == securityid && pair.second.first.qty() <= qty;
			});

			if (it != cacheMap.end())
			{
				itemList.erase(it->second.second);
				cacheMap.erase(it);
				index--;
			}
			else
				break;
		}
	}

	unsigned int get_matching_size_for_security(const std::string securityid)
	{
		unsigned int count = 0;
		for (auto& pair : cacheMap)
		{
			Order* compareItem = &pair.second.first;
			if (compareItem->securityId() != securityid)
				continue;

			for (const auto & item : cacheMap)
			{
				if (compareItem->orderId() == item.second.first.orderId())
					continue;

				if (compareItem->matchRule(&item.second.first))
					count++;
			}
		}
		return count;
	}

	std::vector<Order> get_all_orders()
	{
		std::vector<Order> list;
		for (auto &item : cacheMap)
		{
			list.push_back(item.second.first);
		}
		return list;
	}
};

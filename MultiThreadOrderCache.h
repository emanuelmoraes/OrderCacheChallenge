#pragma once
#include "OrderCache.h"
#include "ThreadSafeCache.h"

class MultiThreadOrderCache : public OrderCacheInterface
{
private:
	std::shared_ptr<ThreadSafeCache<int, Order>> threadSafeCache;

public:
	virtual void addOrder(Order order);
	virtual void cancelOrder(const std::string& orderId);
	virtual void cancelOrdersForUser(const std::string& user);
	virtual void cancelOrdersForSecIdWithMinimumQty(const std::string& securityId, unsigned int minQty);
	virtual unsigned int getMatchingSizeForSecurity(const std::string& securityId);
	virtual std::vector<Order> getAllOrders() const;

	MultiThreadOrderCache()
	{
		threadSafeCache = std::make_shared<ThreadSafeCache<int, Order>>(10);
	}

	~MultiThreadOrderCache()
	{
		threadSafeCache == nullptr;
	}
};


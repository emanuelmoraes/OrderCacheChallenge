#pragma once
#include "OrderCache.h"
#include "SimpleCache.h"

class LocalOrderCache :	public OrderCacheInterface
{
private:
	std::shared_ptr<SimpleCache> simpleCache;

public:
	virtual void addOrder(Order order);
	virtual void cancelOrder(const std::string& orderId);
	virtual void cancelOrdersForUser(const std::string& user);
	virtual void cancelOrdersForSecIdWithMinimumQty(const std::string& securityId, unsigned int minQty);
	virtual unsigned int getMatchingSizeForSecurity(const std::string& securityId);
	virtual std::vector<Order> getAllOrders() const;

	LocalOrderCache()
	{
		simpleCache = std::make_shared<SimpleCache>(10);
	}

	~LocalOrderCache()
	{
		simpleCache == nullptr;
	}
};


#include "LocalOrderCache.h"

void LocalOrderCache::addOrder(Order order)
{
	simpleCache->put(simpleCache->getIndex(), order);
}

void LocalOrderCache::cancelOrder(const std::string & orderId)
{
	simpleCache->remove_by_orderid(orderId);
}

void LocalOrderCache::cancelOrdersForUser(const std::string & user)
{
	simpleCache->remove_by_user(user);
}

void LocalOrderCache::cancelOrdersForSecIdWithMinimumQty(const std::string & securityId, unsigned int minQty)
{
	simpleCache->remove_by_securotyid_with_minimum_qty(securityId, minQty);
}

unsigned int LocalOrderCache::getMatchingSizeForSecurity(const std::string & securityId)
{
	return simpleCache->get_matching_size_for_security(securityId);
}

std::vector<Order> LocalOrderCache::getAllOrders() const
{
	return simpleCache->get_all_orders();
}

#include "MultiThreadOrderCache.h"

void MultiThreadOrderCache::addOrder(Order order)
{
	threadSafeCache->put(threadSafeCache->getIndex(), order);
}

void MultiThreadOrderCache::cancelOrder(const std::string & orderId)
{
	threadSafeCache->remove_by_orderid(orderId);
}

void MultiThreadOrderCache::cancelOrdersForUser(const std::string & user)
{
	threadSafeCache->remove_by_user(user);
}

void MultiThreadOrderCache::cancelOrdersForSecIdWithMinimumQty(const std::string & securityId, unsigned int minQty)
{
	threadSafeCache->remove_by_securotyid_with_minimum_qty(securityId, minQty);
}

unsigned int MultiThreadOrderCache::getMatchingSizeForSecurity(const std::string & securityId)
{
	return threadSafeCache->get_matching_size_for_security(securityId);
}

std::vector<Order> MultiThreadOrderCache::getAllOrders() const
{
	return threadSafeCache->get_all_orders();
}

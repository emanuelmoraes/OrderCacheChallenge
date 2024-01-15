// RunChallengeTradeweb.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include "SimpleCache.h"
#include "LocalOrderCache.h"
#include "Util.h"

void print_all_orders(std::vector<Order> list)
{
	std::cout << "ALL ORDERS" << std::endl;
	for (auto item : list)
	{
		std::cout << item.toString() << std::endl;
	}
	std::cout << std::endl;
}

void print_empty_line()
{
	std::cout << std::endl;
}

int main()
{
    std::cout << "Challenge Tradeweb\n";
	LocalOrderCache localOrderCache;

	Order order1("59462A1B-6F91-4ABF-B801-FD1CDC93A273", "BDE69D74-777D-4560-A34B-1D2521FBA656", BUY_SIDE, 1, "Emanuel", "Emanuel IT");
	Order order2("4FCA1F85-BA60-4A06-B395-1EB6DB89F581", "30C06FC6-6E62-414D-BA4A-52F62156180B", SELL_SIDE, 2, "Fulano", "Fulano IT");
	Order order3("0086BD40-FD96-4F6B-BCC6-77799A9D5ABE", "050F3838-3AA7-4095-B984-8638FE006102", BUY_SIDE, 25, "Ciclano", "Ciclano IT");
	Order order4("30338B4B-2697-42A1-B38C-1686F3836804", "9A09EF9B-3218-4D06-AA97-86C55DBD3009", SELL_SIDE, 5, "Joao", "Joao IT");
	Order order5("731FC6BC-485B-4773-87C1-4C27304831ED", "92AE9525-ECA1-46E6-AADA-2EB9DE50C32D", BUY_SIDE, 10, "Jose", "Jose IT");
	Order order6("731FC6BC-485B-4773-87C1-4C27304831ED", "92AE9525-ECA1-46E6-AADA-2EB9DE50C32D", SELL_SIDE, 10, "Emanuel", "Jose IT");
	Order order7("731FC6BC-485B-4773-87C1-4C27304831ED", "92AE9525-ECA1-46E6-AADA-2EB9DE50C32D", BUY_SIDE, 10, "Ricardo", "Jose IT");
	Order order8("4FCA1F85-BA60-4A06-B395-1EB6DB89F581", "7E3ACAEA-C8F5-4C20-8CCD-01F798C98964", BUY_SIDE, 100, "Fulano", "Forester IT");
	Order order9("CE5CE838-5785-4391-A4B5-6B2FE5E4C29D", "7E3ACAEA-C8F5-4C20-8CCD-01F798C98964", SELL_SIDE, 1000, "Marco", "Forester IT");
	Order order10("9305A5AB-CDB5-4FA9-8DEC-D801C2D4464B", "7E3ACAEA-C8F5-4C20-8CCD-01F798C98964",BUY_SIDE, 500, "Marco", "Company IT");

	// ADD
	localOrderCache.addOrder(order1);
	localOrderCache.addOrder(order2);
	localOrderCache.addOrder(order3);
	localOrderCache.addOrder(order4);
	localOrderCache.addOrder(order5);
	localOrderCache.addOrder(order6);
	localOrderCache.addOrder(order7);
	localOrderCache.addOrder(order8);
	localOrderCache.addOrder(order9);
	localOrderCache.addOrder(order10);

	print_all_orders(localOrderCache.getAllOrders());

	// MATCH
	auto idMatch1 = localOrderCache.getMatchingSizeForSecurity("7E3ACAEA-C8F5-4C20-8CCD-01F798C98964");
	std::cout << "MATCH SECURITY ID (7E3ACAEA-C8F5-4C20-8CCD-01F798C98964): " << idMatch1 << std::endl;

	auto idMatch2 = localOrderCache.getMatchingSizeForSecurity("92AE9525-ECA1-46E6-AADA-2EB9DE50C32D");
	std::cout << "MATCH SECURITY ID (92AE9525-ECA1-46E6-AADA-2EB9DE50C32D): " << idMatch2 << std::endl;
	print_empty_line();

	// REMOVE
	localOrderCache.cancelOrder("4FCA1F85-BA60-4A06-B395-1EB6DB89F581");
	localOrderCache.cancelOrdersForUser("Emanuel");
	localOrderCache.cancelOrdersForSecIdWithMinimumQty("92AE9525-ECA1-46E6-AADA-2EB9DE50C32D", 15);

	print_all_orders(localOrderCache.getAllOrders());


	Order order11("59462A1B-6F91-4ABF-B801-FD1CDC93A273", "BDE69D74-777D-4560-A34B-1D2521FBA656", BUY_SIDE, 1, "Marlon", "Marlon IT");
	localOrderCache.addOrder(order11);
	print_all_orders(localOrderCache.getAllOrders());
}

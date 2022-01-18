#include <iostream>
#include "Sales_item.h"
int main ()
{
	Sales_item item1, item2;
	std::cin >> item1 >> item2;
	if (item1.isbn() == item2.isbn())
	{
		std::cout << item1 + item2 << std::endl;
		return 0;
	}
	else
	{
		std::cerr << "Data must refer to same ISBN" << std::endl;
		return -1;
	}
}
/**
 * 输入:
 * 	0-201-78345-X 3 20.00
 * 	0-201-78345-X 2 25.00
 * 标准输出:
 * 	0-201-78345-X 5 110 22
 * 输入:
 * 	0-201-78345-X 3 20.00
 * 	0-201-78343-X 2 25.00
 * 错误输出:
 * 	Data must refer to same ISBN
 **/

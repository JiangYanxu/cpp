#ifndef TOOLS_H
#define TOOLS_H

#include <iostream> //for convenience
#include <fstream>
#include <sstream>
#include <string> //for string类
#include <vector> //for vector类
#include <cstdlib> //for std::malloc()

#include <cstddef> //for size_t
#include <cstdio> //for printf...
void byte_view (size_t length, u_char * point)
{
	printf(
		"      Address     "
		"  0  1  2  3  4  5  6  7"
		"  8  9  a  b  c  d  e  f");
	for (size_t i = 0; i<length; i++)
	{
		if(i%0x10 == 0)
			printf("\n%18p",&(point[i]));
		printf(" %02X", point[i]);
	}
	printf("\n");
}

struct Sales_data{
	Sales_data () = default;
	Sales_data (const std::string &s): bookNo(s){}
	Sales_data (const std::string &s, unsigned n, double p):
		bookNo(s), units_sold(n), revenue(p*n){}
	Sales_data (std::istream &);
	std::string isbn() const {return bookNo;}
	Sales_data& combine(const Sales_data&);
	double avg_price() const;
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};
Sales_data add(const Sales_data&, const Sales_data&);
std::ostream &print(std::ostream&, const Sales_data&);
std::istream &read(std::istream&, Sales_data&);

#include <stdexcept>
#include <initializer_list>
#include <cstdarg>
#include <cassert>
#endif //TOOLS_H

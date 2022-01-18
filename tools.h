#ifndef TOOLS_H
#define TOOLS_H

#include <iostream> //for convenience
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

#include <stdexcept>
#include <initializer_list>
#include <cstdarg>
#include <cassert>
#endif //TOOLS_H

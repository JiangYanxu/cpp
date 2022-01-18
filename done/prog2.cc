#include "tools.h"
int main()
{
	const int i = 1;
	//const int &i = 1;
	int *j = (int *)&i;
	*j=22;
	std::cout << &i << " " << j << std::endl;
	std::cout << i << " " << *j << std::endl;
	std::cout << *(&i) << " " << *j << std::endl;
	return 0;
}

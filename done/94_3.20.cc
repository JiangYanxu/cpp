#include "tools.h"
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
int main()
{
	vector<int> i_vec{1,2,3,4,5,6,7,8,9,10,11,12, 13};
	for (decltype(i_vec.size()) i=0; i<i_vec.size()/2; ++i)
		cout << i_vec[i] + i_vec[i_vec.size()-i-1]<< " ";
	if (i_vec.size()%2==1)
		cout << i_vec[i_vec.size()/2] << " ";
	cout << endl;
	return 0;
}

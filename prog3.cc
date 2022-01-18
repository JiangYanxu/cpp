#include "tools.h"
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
struct Sales_data{
	Sales_data () = default;
	Sales_data (const string &s): bookNo(s){}
	Sales_data (const string &s, unsigned n, double p):
		bookNo(s), units_sold(n), revenue(p*n){}
	Sales_data (std::istream &);
	string isbn() const {return bookNo;}
	Sales_data& combine(const Sales_data&);
	double avg_price() const;
	string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};
Sales_data add(const Sales_data&, const Sales_data&);
std::ostream &print(std::ostream&, const Sales_data&);
std::istream &read(std::istream&, Sales_data&);
class Y;
class X
{
	public:
		Y * y;
};
class Y
{
	X x;
};
int main(int argc, char* argv[])
{
	const char *  a = "123";
	const char * b = static_cast<const char *> (a);
	char * c = const_cast<char *> (b);
	cout << a<< endl;
	cout << b<< endl;
	c[1]='5';
	cout << c<< endl;
	return 0;
}
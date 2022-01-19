#include "tools.h"
using std::cout;
using std::cin;
using std::endl;
using std::ends;
using std::flush;
using std::string;
using std::vector;
using std::istream;
using std::ofstream;
using std::ifstream;
using std::istringstream;
struct PersonInfo {
	string name;
	vector<string> phones;
};
int main(int argc, char* argv[])
{
	string line, word;
	vector<PersonInfo> people;
	istringstream record;
	while(getline(cin, line))
	{
		PersonInfo info;
		record.str(line);
		record >> info.name;
		while (record >> word)
			info.phones.push_back(word);
		people.push_back(info);
		record.clear();
	}
	cout << endl;
	for (PersonInfo info:people)
	{
		cout << info.name<< endl;
		for (string phone : info.phones)
			cout << "\t"+phone << endl;
	}
	return 0;
}
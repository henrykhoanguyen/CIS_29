#include <iostream>
#include <iterator>
#include <string>
#include <regex>
#include <fstream>
#include <bitset>
#include <stack>
#include <queue>
#include <list>

using namespace std;

class BarCode
{
public:
	BarCode();
	string checkStringInput(string, string);
private:
	list<string> custBarCode;
	list<string> itemsCode;
};

BarCode::BarCode()
{
	string files[] = {"cart.xml", "BCPRODUCT.xml", "bc3of9.txt"};
	ifstream infile;
	string input, beginTag, endTag, barcode;

	//for (int i = 0; i < 3; i++)
	
	infile.open(files[0]);

	if (!infile.is_open()){
		cout << "File " + files [0] + " is corrupted!";
		exit(101);
	}

	while (!infile.eof()){
		getline(infile, input);
		//cout << input << endl;
		//beginTag = checkStringInput(input, "<[a-zA-Z0-9]*>");
		//cout << beginTag;
		
		barcode = checkStringInput(input, "[A-z0-9.]+<");
		cout << barcode;

		//endTag = checkStringInput(input, "<[a-zA-Z\/]*>");
		//cout << endTag;
	}
}

string BarCode::checkStringInput(string input, string regexString){
	regex e(regexString);
	smatch m;
	string value = "";

	bool found = regex_search(input, m, e);
	//cout << m.size() << endl;
	//cout << m.str();
	value = m.str();
	return value;
}

int main()
{
	BarCode barCode;
	system("pause");
	return 0;
}
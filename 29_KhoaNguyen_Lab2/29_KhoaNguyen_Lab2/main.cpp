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

class Code3of9
{
private:
	char alphabet; ///MAKE THIS LIST OR SOMETHING
	string barCode;
public:
	Code3of9(){}
	Code3of9(char, string);
};

Code3of9::Code3of9(char a, string bc)
{
	this->alphabet = a;
	this->barCode = bc;
}

class Carts
{
private:
	string barCode;
public:
	Carts(){}
	Carts(string);
};

Carts::Carts(string bc)
{
	this->barCode = bc;
}

class Storages
{
private:
	string itemName;
	string itemBarCode;
	string itemPrice;
public:
	Storages(){}
	Storages(string, string, string);

};

Storages::Storages(string n, string bc, string p)
{
	this->itemBarCode = n;
	this->itemBarCode = bc;
	this->itemPrice = p;
}


class BarCode
{
private:
	queue<string> tempQueue;
	stack<string> tempStack;
	list<Storages> storages;
	list<Carts> carts;
public:
	BarCode();
	string checkStringInput(string, string);
	void openFile();
	void openCode39();
	void intoStorages();
	void intoCarts();
};

BarCode::BarCode()
{
	openCode39();
	openFile();
}

void BarCode::openCode39(){
	ifstream infile;
	Code3of9 *code39 = new Code3of9();
	char alpha;
	string bar = "";
	infile.open("bc3of9.txt");
	if (!infile.is_open()){
		cout << "File cannot be opened!\n";
		exit(101);
	}

	while (getline(infile, bar))
	{
		if (bar != ""){
			alpha = bar.at(0);
			bar = bar.substr(2, bar.size());
			//cout << alpha << " " << bar << endl;
		}
	}
}

void BarCode::openFile(){
	string files[] = { "cart.xml", "BCPRODUCT.xml"};
	ifstream infile;
	string input, beginTag, endTag, data;

	for (int i = 0; i < 2; i++){
		infile.open(files[i]);

		if (!infile.is_open()){
			cout << "File " + files[i] + " is corrupted!";
			exit(101);
		}

		while (!infile.eof()){
			infile >> input;

			beginTag = checkStringInput(input, "<[a-zA-Z0-9]*>");
			tempStack.push(beginTag);
			//cout << beginTag;

			data = checkStringInput(input, "[A-z0-9.]+<");
			if (data.size() != 0){
				data.pop_back();
				tempQueue.push(data);
			}
			//cout << data;

			endTag = checkStringInput(input, "<\/[A-z]+>");
			if (endTag.size() != 0){
				tempStack.pop();
			}
			//cout << endTag;
		}
		if (i == 0){
			intoCarts();
		}
		else
			intoStorages();
	}
}

void BarCode::intoStorages(){
	while (!tempQueue.empty())
	{
		string n, bc, p;
		n = tempQueue.front();
		//cout << tempQueue.front() << endl;
		tempQueue.pop();
		bc = tempQueue.front();
		//cout << tempQueue.front() << endl;
		tempQueue.pop();
		p = tempQueue.front();
		//cout << tempQueue.front() << endl;
		tempQueue.pop();
		Storages goods(n, bc, p);
		storages.push_back(goods);
	}
}

void BarCode::intoCarts(){
	while (!tempQueue.empty())
	{
		string bc;
		bc = tempQueue.front();
		//cout << tempQueue.front() << endl;
		tempQueue.pop();
		Carts goods(bc);
		carts.push_back(goods);
	}
}

string BarCode::checkStringInput(string input, string regexString){
	regex e(regexString);
	smatch m;

	bool found = regex_search(input, m, e);
	return m.str();
}

void enableDebug(bool bvalue)
{
	if (!bvalue) return;

	int tmpFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);

	// Turn on leak-checking bit.
	tmpFlag |= _CRTDBG_LEAK_CHECK_DF;

	// Turn off CRT block checking bit.
	tmpFlag &= ~_CRTDBG_CHECK_CRT_DF;

	// Set flag to the new value.
	_CrtSetDbgFlag(tmpFlag);
}

int main()
{
	enableDebug(true);
	BarCode barCode;
	system("pause");
	return 0;
}
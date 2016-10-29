#include <iostream>
#include <iterator>
#include <string>
#include <regex>
#include <fstream>
#include <stack>
#include <queue>
#include <list>
#include <cstdlib>

using namespace std;

class Code3of9
{
private:
	char alphabet;
	string barCode;
public:
	Code3of9(){}
	Code3of9(char, string);
	void setAlphabet(char a){ this->alphabet = a; }
	void setBarCode(string bc){ this->barCode = bc; }
	char getAlphabet(){ return alphabet; }
	string getBarCode(){ return barCode; }
};

Code3of9::Code3of9(char a, string bc)
{
	this->alphabet = a;
	this->barCode = bc;
}

/***************** Goods Class ******************/
class Good
{
private:
	string itemName;
	double price;
public:
	Good(){}
	Good(string, double);
	void setItemName(string n){ this->itemName = n; }
	void setPrice(double q){ this->price = q; }
	string getItemName(){ return this->itemName; }
	double getPrice(){ return this->price; }
};

Good::Good(string n, double t)
{
	this->itemName = n;
	this->price = t;
}
/**************** Class End *********************/


/******************** Carts Class *******************/
class Cart
{
private:
	list<Good> goods;
	double total;

public:
	Cart(){}
	Cart(list<Good>);
	void setTotal(double t){ this->total = t; }
	double getTotal(){ return this->total; }
	list<Good> getGoods(){ return this->goods; }
};

Cart::Cart(list<Good> g)
{
	this->goods = g;
}

/**************** Class End *********************/

/****************** Storages Class ********************/
class Storages
{
private:
	string itemName;
	string itemBitCode;
	string itemBarCode;
	string itemPrice;
public:
	Storages(){}
	Storages(string, string, string);
	void setItemBarCode(string b){ this->itemBitCode = b; }
	void setItemBitCode(string bc){ this->itemBarCode = bc; }
	string getItemName(){ return this->itemName; }
	string getItemBarCode(){ return this->itemBarCode; }
	string getItemPrice(){ return this->itemPrice; }
};

Storages::Storages(string n, string bc, string p)
{
	this->itemName = n;
	this->itemBitCode = bc;
	this->itemPrice = p;
}
/********************* Class End ***********************/

/*********************** ProcessData Class **********************/
class ProcessData
{
private:
	queue<string> tempQueue;
	stack<string> tempStack;
	list<Storages> storages;
	list<Cart> carts;
	list<Code3of9> code39;

public:
	ProcessData();
	string checkStringInput(string, string);
	list<Storages> getStorages(){ return this->storages; }
	list<Cart> getCarts(){ return this->carts; }
	list<Code3of9> getCode39(){ return this->code39; }
	void openFile();
	void intoStorages();
	void intoCart();
	void openCode3of9();
	double getPrice(string);
	string bitToString(string);
	string lookUpCode39(string);
	void printReceipt();
};

ProcessData::ProcessData()
{
	cout << "READING IN CODE 3 OF 9...\n";
	openCode3of9();
	openFile();
	cout << "PRINTING RECIEPTS!...\n";
	printReceipt();
	cout << "\nTHANK YOU FOR YOUR PATIENT!";
}

void ProcessData::openCode3of9(){
	ifstream infile;
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
			bar = bar.substr(2,9);
			Code3of9 temp(alpha, bar);
			code39.push_back(temp);
		}
	}
	infile.close();
}

void ProcessData::openFile(){
	string files[] = {"bcproducts.xml", "carts.xml"};
	ifstream infile;
	string input, beginTag, endTag, data;

	for (int i = 0; i < 2; i++){
		infile.open(files[i]);

		if (!infile.is_open()){
			cout << "File " + files[i] + " is corrupted!";
			exit(101);
		}
		cout << "READING IN FILE " << files[i]  << "..." << endl;
		cout << "PLEASE WAIT!\n";
		while (!infile.eof()){
			getline(infile, input);

			beginTag = checkStringInput(input, "<[a-zA-Z0-9]*>");
			if (beginTag.size() != 0){
				tempStack.push(beginTag);
			}
			//cout << beginTag;

			data = checkStringInput(input, "[A-z\-0-9. \&\+\$\%\*\(\)\'A-z]+<");
			if (data.size() != 0){
				data.pop_back();
				tempQueue.push(data);
			}
			//cout << data << endl;

			endTag = checkStringInput(input, "<\/[A-z]+>");
			if (endTag.size() != 0 && endTag == "</Cart>"){
				tempStack.pop();
				intoCart();
			}else if (endTag.size() != 0 && !tempStack.empty()){
				tempStack.pop();
			}
			//cout << endTag;
		}
		if (i == 0)
			intoStorages();

		infile.close();
	}
}

void ProcessData::intoStorages(){
	while (!tempQueue.empty())
	{
		string n, bc, p;
		n = tempQueue.front();
		for (int i = 0; i < n.size(); i++){
			n[i] = toupper(n[i]);
		}
		//cout << n << endl;

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

void ProcessData::intoCart(){
	double total = 0;
	Cart cart;
	Good good;
	list<Good> tempGood;
	while (!tempQueue.empty())
	{

		string name;
		double price = 0;
		name = tempQueue.front();
		//cout << tempQueue.front() << endl;

		name = bitToString(name);
		//cout << name << " ";
		price = getPrice(name);
		//cout << price << endl;
		total += price;
		good = Good(name, price);
		tempGood.push_back(good);
		tempQueue.pop();

	}
	cart = Cart(tempGood);
	//cout << total << endl;
	cart.setTotal(total);
	carts.push_back(cart);
}

double ProcessData::getPrice(string name){
	list<Storages>::const_iterator iterate;
	Storages store;
	for (iterate = storages.begin(); iterate != storages.end(); iterate++)
	{
		store = *iterate;
		if (store.getItemName() == name){
			return stod(store.getItemPrice());
		}
	}
	return 0;
}

string ProcessData::checkStringInput(string input, string regexString){
	regex e(regexString);
	smatch m;

	bool found = regex_search(input, m, e);

	return m.str();
}

string ProcessData::bitToString(string b){
	string temp = "", temp1 = "";

	for (int i = 0; i < b.size(); i++){
		if (b.at(i) == '0'){
			temp += 'n';
		}
		else
			temp += 'w';
	}
	
	for (int i = 0; i < temp.size(); i += 9){
		temp1 += lookUpCode39(temp.substr(i, 9));
	}

	return temp1;
}

string ProcessData::lookUpCode39(string substr){
	string str = "";
	list<Code3of9>::const_iterator iterate;
	Code3of9 code;
	for (iterate = code39.begin(); iterate != code39.end(); iterate++)
	{
		code = *iterate;
		if (code.getBarCode().compare(substr) == 0){
			str = code.getAlphabet();
			//cout << code.getAlphabet();
			return str;
		}
	}
	return str;
}

void ProcessData::printReceipt(){
	list<Cart>::const_iterator iterate;
	list<Good>::const_iterator iterator;

	Cart tempCart;
	Good tempGood;
	int i = 1;
	for ( iterate = carts.begin(); iterate != carts.end(); iterate++, i++)
	{
		tempCart = *iterate;
		list<Good> tempList = tempCart.getGoods();
		cout << "Cart #" << i << endl;
		for (iterator = tempList.begin(); iterator != tempList.end(); iterator++)
		 {
			 tempGood = *iterator;
			 cout << tempGood.getItemName() << ": $" << tempGood.getPrice() << endl;
		 }
		 cout << "\nTotal: $" << tempCart.getTotal() << endl << endl;
	}
}

/************************ Class End *************************/

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
	ProcessData process;
	system("pause");
	return 0;
}
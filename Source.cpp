#include <cstring>
#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <queue>
#include <regex>

using namespace std;
const double pi = 3.141592654;
const double radius = 6372.8;

class Airport
{
	string code, lat, lon, city, state;
public:
	Airport() {}
	Airport(string a) : code(a), lat(NULL), lon(NULL), city(0), state(0) {}
	Airport(string a, string b, string c, string d, string e) : code(a), city(b), state(c), lat(d), lon(e) {}
	string GetCode() { return code; }
	double GetLat() { return atof(lat.c_str()); }
	double GetLon() { return atof(lon.c_str()); }
	string GetCity() { return city; }
	bool operator==(const Airport & a) const { return this->code == a.code; }
	bool operator >(const Airport & a) const { return this->code > a.code; }
	bool operator <(const Airport & a) const { return this->code < a.code; }
	void print() { cout << this->code << endl; }
};




class helper
{
	double lat1, lat2, lon1, lon2;
public:
	helper (Airport a, Airport b)
	{
		lat1 = a.GetLat();
		lat2 = b.GetLat();
		lon1 = a.GetLon();
		lon2 = b.GetLon();
	}

	double GetDistance() //calculate Distance
	{
		return (radius * acos(cos((90 - lat1) * (pi / 180)) * cos((90 - lat2) * (pi / 180)) + sin((90 - lat1) * (pi / 180)) * sin((90 - lat2) * (pi / 180)) * cos((lon1 - lon2) * (pi / 180))));
	}
};
class reader
{
	string filename;
	stack<string> mystack;
	queue<string> myqueue;
	vector<Airport> linked;
public:
	Airport item(int a) { return linked[a]; }
	void printt()
	{
		for (int i = 0; i < linked.size(); i++) { linked[i].print(); }
	}
	void bubble_sort()
	{
		cout << "Records are being sorted. " << endl;
		bool swapOccurred;

		do
		{
			swapOccurred = false;
			for (int i = 0; i < linked.size()-1; i++)
			{
				if (linked[i] > linked[i + 1])
				{
					swap(linked[i], linked[i + 1]);
					swapOccurred = true;
				}
			}
		} while (swapOccurred);
		cout << "Records are sorted. " << endl;
	}


	void swap(Airport& a, Airport& b)
	{
		Airport temp;
		temp = a;
		a = b;
		b = temp;
	}



	int BINARY_SEARCH(int Left, int Right, string Key)
	{
		if (Left > Right) return -1 ;
		int M = (Left + Right) / 2;
		if (linked[M].GetCode() == Key) return M;
		if (linked[M].GetCode() > Key) return BINARY_SEARCH(Left, M - 1, Key);
		return BINARY_SEARCH(M + 1, Right, Key);
	}

	vector<Airport> getlinked() { return linked; }
	int size() { return linked.size(); }
	string popq(queue<string>& myqueue)
	{
		string s = myqueue.front();
		myqueue.pop();
		return s;
	}
	reader(string name) : filename(name) {}
	void populate()
	{
		cout << "Records are being Parsed. " << endl;
		ifstream fin(filename.c_str());
		if (!fin) cerr << "FILE NOT FOUND" << endl;
		string ignore;
		getline(fin, ignore);
		string buffer;
		string a, b, c, d, e;
	    string open, data, close;
		string realdata;
		while (!fin.eof())
		{
			getline(fin, buffer);
			open = lineParser(buffer, "\\<[a-zA-Z]*\\>");
			int sizeD = open.size() - 2;
			if (sizeD != -2) {
				open = open.substr(1, sizeD);
				mystack.push(open);
			}
			data = lineParser(buffer, ">(.*)<");
			sizeD = data.size() - 2;
			if (sizeD != -2) {
				data = data.substr(1, sizeD);
				myqueue.push(data);
			}
			close = lineParser(buffer, "\\<\\/[a-zA-Z]*\\>");
			sizeD = close.size() - 3;
			if (sizeD != -3) {
				close = close.substr(2, sizeD);
			}
			//This creates an airport object
				if (myqueue.size() == 5)
				{
					a = myqueue.front();
					myqueue.pop();
					b = myqueue.front();
					myqueue.pop();
					c = myqueue.front();
					myqueue.pop();
					d = myqueue.front();
					myqueue.pop();
					e = myqueue.front();
					myqueue.pop();
					while(myqueue.size()) myqueue.pop();
					Airport aa(a, b, c, d, e);
					linked.push_back(aa);
				}

		}
		cout << "Records are parsed and Sucessfully stored. " << endl;
	}


	string lineParser(string text, string split)
	{

		string s = "";
		sregex_token_iterator end;
		regex pattern(split);
		for (sregex_token_iterator iter(text.begin(), text.end(), pattern); iter != end; ++iter)
		{
			if ((*iter).length() > 0)
			{
				if ((static_cast<string>(*iter))[0] != 0x20)
					s += *iter;
			}
		}
		return s;
	}
};


int main()
{
	reader read("Airport.xml");
	read.populate();
	read.bubble_sort();
	string a, b;
	cout << "Enter airport 1 code(in uppercase):" << endl;
	cin >> a;
	Airport air1 = read.item(read.BINARY_SEARCH(0, read.size()-1, a));
	if (air1.GetCode() == "NOT FOUND") exit(4);
	cout << "Enter airport 2 code(in uppercase):" << endl;
	cin >> b;
	Airport air2 = read.item(read.BINARY_SEARCH(0, read.size() - 1, b));
	if (air2.GetCode() == "NOT FOUND") exit(5);
	helper finder(air1, air2);
	cout << "The distance is " << finder.GetDistance() << " KMS." << endl;
	cout << endl;
}

// XML Processing Program
// Matthew Mitchell
// CIS 29, Larkin
// April 26, 2016

#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include <stack>
#include <queue>
#include <vector>
#include <regex>
#include <cstring>
#include <cctype>

using namespace std;

#define R 6371
#define TO_RAD (3.1415926536 / 180)

/*******************************************************************/

class Attribute
{
private:
    string subsubtype;
    string data;
public:
    
    Attribute(): subsubtype(""), data() {}
    
    Attribute(string type, string in): subsubtype(type), data(in) {}
    
    void setData(string in) {data = in;}
    
    void setSubsubtype(string type) {subsubtype = type;}
    
    string getSubsubtype() {return subsubtype;}
    
    string getData() {return data;}
    
    friend ostream & operator << (ostream & ostr, const Attribute & obj)
    {
        ostr << obj.subsubtype << ": " << obj.data << endl;
        return ostr;
    }
};

/*******************************************************************/

class Element
{
private:
    string subtype;
    vector<Attribute> sublist;
public:
    
    Element(): subtype("") {sublist.clear();}
    
    Element(Attribute att): subtype("") {sublist.push_back(att);}
    
    Element(string type, vector<Attribute> vatt): subtype(type) {sublist = vatt;}
    
    void setSubtype(string type) {subtype = type;}
    
    void addAttribute(Attribute att) {sublist.push_back(att);}
    
    string getSubtype() {return subtype;}
    
    vector<Attribute> getSublist() {return sublist;}
    
    friend ostream & operator << (ostream & ostr, const Element & obj)
    {
        ostr << obj.subtype << ":\n";
        for(int i = 0; i < (obj.sublist).size(); i++)
            ostr << (obj.sublist)[i];
        return ostr;
    }
};

/*******************************************************************/

class Node
{
private:
    string type;
    vector<Element> list;
public:
    
    Node(): type("") {list.clear();}
    
    Node(Element elem) {list.push_back(elem);}
    
    Node(string type, vector<Element> velem): type(type) {list = velem;}
    
    void setType(string type) {this->type = type;}
    
    void addElement(Element elem) {list.push_back(elem);}
    
    string getType() {return type;}
    
    vector<Element> getList() {return list;}
    
    string getCode() {return (list[0].getSublist())[0].getData();}
    
    double getLat() {return atof((list[1].getSublist())[0].getData().c_str());}
    
    double getLong() {return atof((list[1].getSublist())[1].getData().c_str());}
    
    friend ostream & operator << (ostream & ostr, const Node & obj)
    {
        ostr << "---" << obj.type << "---\n";
        for(int i = 0; i < (obj.list).size(); i++)
            ostr << (obj.list)[i];
        cout << endl;
        return ostr;
    }
};

/*******************************************************************/

class NodeHolder
{
protected:
    vector<Attribute> va;
    vector<Element> ve;
    vector<Node> vn;
public:
    
    NodeHolder() {va.clear(); ve.clear(); vn.clear();}
};

/*******************************************************************/

class RegexFunctions
{
protected:
    
    RegexFunctions() {}
    
    void replace(string & text, string find, string replace)
    {
        regex pattern(find);
        string sresult = regex_replace(text, pattern, replace);
        text = sresult;
    }
    
    bool search(string text, string expr)
    {
        regex pattern(expr);
        bool bvalue = regex_search(text.begin(), text.end(), pattern);
        return bvalue;
    }
    
    vector<string> split(string text, string split)
    {
        sregex_token_iterator end;
        regex pattern(split);
        vector<string> compiler;
        for (sregex_token_iterator iter(text.begin(), text.end(), pattern);iter != end; ++iter)
        {
            if ((*iter).length() > 0)
            {
                if ( (static_cast<string>(*iter))[0] != 0x20)
                    compiler.push_back(*iter);
            }
        }
        return compiler;
    }
    
};

/*******************************************************************/

class ReadXML: public RegexFunctions, public NodeHolder
{
private:
    ifstream infile;
    stack<string> typeHolder;
    queue<string> dataHolder;
public:
    
    ReadXML()
    {
        typeHolder.empty();
        dataHolder.empty();
    }
    
    vector<Node> readFile()
    {
        string filename;
        string temp;
        long pos = 0, pos2 = 0;
        string one, two, three;
        bool slash = false, found = false;
        string capSub, lowSub;
        
        cout << "Enter the name of the input file: ";
        cin >> filename;
        infile.open(filename);
        if(!infile)
            cerr << "Unable to open infile\n";
        
        getline(infile, temp);
        while(!infile.eof())
        {
            getline(infile, temp);
            replace(temp, "[\t\r< ]", "");
            replace(temp, "[>]", " ");
            
            if(temp.find("/", 0) == 0)
                replace(temp, "[ ]", "");
            
            if(temp.find(" ", 0) == temp.size()-1)
                replace(temp, "[ ]", "");
        
            if(!search(temp, "[/]"))
            {
                typeHolder.push(temp);
            }
            else if(search(temp, "[/]") && search(temp, "[ ]"))
            {
                pos = temp.find(" ", 0);
                pos2 = temp.find("/", 0);
                
                if(temp.find("/", pos2+1) != -1)
                    pos2 = temp.find("/", pos2+1);
                
                one = temp.substr(0, pos);
                two = temp.substr(pos+1, pos2-pos-1);
                
                typeHolder.push(one);
                
                for(int i = 1; i < two.size() && found == false && one == "City"; i++)
                {
                    if(isupper(two[i]))
                    {
                        lowSub = two.substr(0, i);
                        capSub = two.substr(i, two.size()-i);
                        two = lowSub + " " + capSub;
                        found = true;
                    }
                }
                found = false;
                dataHolder.push(two);
                slash = true;
            }
            else
            {
                replace(temp, "[/]", "");
                slash = true;
            }
            
            if(slash && typeHolder.size() == 4)
            {
                Attribute d(typeHolder.top(), dataHolder.front());
                typeHolder.pop();
                dataHolder.pop();
                va.push_back(d);
                slash = false;
            }
            else if(slash && typeHolder.size() == 3)
            {
                Element c(typeHolder.top(), va);
                typeHolder.pop();
                va.clear();
                ve.push_back(c);
                slash = false;
            }
            else if(slash && typeHolder.size() == 2)
            {
                Node b(typeHolder.top(), ve);
                typeHolder.pop();
                ve.clear();
                vn.push_back(b);
                slash = false;
            }
            else if(slash && typeHolder.size() == 1)
            {
                typeHolder.pop();
            }
        }
        return vn;
    }

};

/*******************************************************************/

void nodeSort(vector<Node> & vnodes)
{
    int current = 1;
    long last = vnodes.size() - 1;
    Node temp;
    int walker;

    while(current <= last)
    {
        temp = vnodes[current];
        walker = current - 1;
        
        while(walker >= 0 && temp.getCode() < vnodes[walker].getCode())
        {
            vnodes[walker + 1] = vnodes[walker];
            walker = walker - 1;
        }
        vnodes[walker + 1] = temp;
        current = current + 1;
    }
}

long binarySearch(vector<Node> vnodes, long first, long last, string city)
{
    if(first > last)
        return -1;
    long mid = (first + last)/2;
    if(vnodes[mid].getCode() == city)
        return mid;
    if(vnodes[mid].getCode() > city)
        return binarySearch(vnodes, first, mid-1, city);
    else
        return binarySearch(vnodes, mid+1, last, city);
}

long promptSearch(vector<Node> vn)
{
    string city;
    cout << "Enter an airport code to find: ";
    cin >> city;
    return binarySearch(vn, 0, vn.size(), city);
}

double haversine(double th1, double ph1, double th2, double ph2)
{
    double dx, dy, dz;
    ph1 -= ph2;
    ph1 *= TO_RAD, th1 *= TO_RAD, th2 *= TO_RAD;
    
    dz = sin(th1) - sin(th2);
    dx = cos(ph1) * cos(th1) - cos(th2);
    dy = sin(ph1) * cos(th1);
    return asin(sqrt(dx * dx + dy * dy + dz * dz) / 2) * 2 * R;
}

/*******************************************************************/

void enableDebug(bool bvalue);

int main()
{
    enableDebug(true);
    ReadXML airp;
    vector<Node> airports = airp.readFile();
    
    nodeSort(airports);
    
    long airp1;
    long airp2;
    
    airp1 = promptSearch(airports);
    airp2 = promptSearch(airports);
    
    cout << endl << "Airport 1:\n" << airports[airp1];
    cout << "Airport 2:\n" << airports[airp2];
    
    double distance;
    
    distance = haversine(airports[airp1].getLat(), airports[airp1].getLong(), airports[airp2].getLat(), airports[airp2].getLong());
    
    cout << "Distance between the two airports: " << distance << endl << endl;
    
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
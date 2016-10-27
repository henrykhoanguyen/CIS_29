#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <map>
#include <cstdlib>
using namespace std;

const int DOT = 128;
const int DASH = 64;
const int CHAR_TERM = 0;
const int WORD_TERM = 192;

void enableDebug(bool bvalue);

/*****************************************************************/

class MorseLookup
{
protected:
    map<string, string> table;
public:
    MorseLookup();
    virtual map<string, string> getTable();
};

MorseLookup::MorseLookup()
{
    string characters[46] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "0", "1", "2", "3", "4",
     "5", "6", "7", "8", "9", "'", "@", ":", ",", "$", "=", "!", ".", "?", "\""};

    string morse[46] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-",
     ".--", "-..-", "-.--", "--..", "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", ".----.", ".--.-.", "---...", "--..--", "...-..-",
      "-...-", "-.-.--", ".-.-.-", "..--..",".-..-."};

    for(int i = 0; i < 46; i++) {
        table[morse[i]] = characters[i];
    }
}

map<string, string> MorseLookup::getTable()
{
    return table;
}

/*****************************************************************/

class MorseToChar: public MorseLookup
{
protected:
    string s;
    string container;
public:
    MorseToChar();
    virtual void toChars();
};

MorseToChar::MorseToChar()
{
    s = "";
    container = "";
}

void MorseToChar::toChars()
{
    for (int i = 0; i < container.size(); i++)
    {
        if (container[i] == '/')
        {
            cout << getTable()[s];
            s = "";
        }
        else if (container[i] == '\\')
        {
            cout << " ";
        }
        else
        {
            s += container[i];
        }
    }
    cout << endl;
}

/*****************************************************************/

class BitToMorse
{
protected:
    bitset<8> bits;

public:
    BitToMorse();
    virtual string toDotDashTerminator();
};

BitToMorse::BitToMorse()
{
    bits = 0x0;
}

string BitToMorse::toDotDashTerminator()
{
    string s = "";
    bitset<8> comparer = 0xC0;
    bitset<8> bitResult;
    int result = 0;

    for (int i = 0; i < 8; i += 2)
    {
        bitResult = bits & comparer;
        result = static_cast<int>(bitResult.to_ulong());

        switch (result) {
            case (DOT):
                s += ".";
                break;
            case (DASH):
                s += "-";
                break;
            case (CHAR_TERM):
                s += "/";
                break;
            case (WORD_TERM):
                s += "\\";
                break;
            default:
                cout << "error" << endl;
                break;
        }
        bits <<= 2;
    }
    return s;
}


/*****************************************************************/

class AsciiToBit
{
protected:
    char c;
public:
    AsciiToBit();
    virtual bitset<8> toBits();
};

AsciiToBit::AsciiToBit()
{
    c = ' ';
}

bitset<8> AsciiToBit::toBits()
{
    return bitset<8>(c);
}

/*****************************************************************/

class Decrypter: public AsciiToBit, public BitToMorse, public MorseToChar
{
private:
    ifstream inBin;
public:
    Decrypter();
};

Decrypter::Decrypter()
{
    // open file
    inBin.open("Morse.bin", ios::binary);
    if (!inBin)
        cout << "Error opening Morse.bin\n";

    // read in Morse.bin and write out to Morse.txt
    while (inBin >> c)
    {
        bits = toBits();
        container += toDotDashTerminator();
    }
    toChars();

    // close file
    inBin.close();
}

/*****************************************************************/

int main()
{
    //enableDebug(true);

    Decrypter decrypter;
	system("pause");
}
/*
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
}*/

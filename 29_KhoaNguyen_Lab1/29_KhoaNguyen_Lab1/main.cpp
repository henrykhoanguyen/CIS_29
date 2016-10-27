#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <bitset>
#include <vector>

using namespace std;


/******** Class Alphabet that contain all alphabets ********/
class AlphaMorse
{
public:
	AlphaMorse();
	char getAlpha(string);
private:
	vector<char> alphabet;
	vector<string> morse;
};

AlphaMorse::AlphaMorse()
{
	alphabet = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
		'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4',
		'5', '6', '7', '8', '9', '"', '@', ':', ',', '$', '=', '!', '.', '?', '\"' };
	morse = { ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--",
		"-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", "-----",
		".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", ".----.", ".--.-.",
		"---...", "--..--", "...-..-", "-...-", "-.-.--", ".-.-.-", "..--..", ".-..-." };
}

char AlphaMorse::getAlpha(string dotDash){
	for (int i = 0; i < morse.size(); i++){
		if (morse[i] == dotDash){
			return alphabet[i];
		}
	}
	return 8;
}

//Class bitToMorse that will translate morse into english
class morseToChar : public AlphaMorse
{
public:
	morseToChar();
	void setMessage(char m){ message += m; }
	void setMorseCode(string mc){ morseCode = mc; }
	string getMorseCode(){ return morseCode; }
	string getMessages(){ return message; }
	void decodeMessage();

private:
	string message = "";
	string morseCode = "";
};

morseToChar::morseToChar()
{
}

void morseToChar::decodeMessage(){
	string temp = "";
	
	for (int i = 0; i < morseCode.size(); i++){
		if (morseCode.at(i) == '|' && temp != ""){
			setMessage(getAlpha(temp));
			temp = "";
		}
		else if (morseCode.at(i) == '/'){
			setMessage(' ');
		}
		else if(morseCode.at(i) != '|'){
			temp += morseCode[i];
		}
	}

	cout << getMessages() << endl;
}


/********* Class MorseCode contain all morse *********/
class bitToMorse : public morseToChar
{
public:
	bitToMorse();
	void toBits(vector<char>);
	void bitsToMCode(string);

private:
	bitset<8> bit;
	string bitCode;
};

bitToMorse::bitToMorse()
{
	bit = 0x0;
}

void bitToMorse::toBits(vector<char> uniqueChar){

	for (int i = 0; i < uniqueChar.size(); i++){
		bit = uniqueChar[i];
		bitCode += bit.to_string();
	}

	bitsToMCode(bitCode);
	decodeMessage();
}

void bitToMorse::bitsToMCode(string bitCode){
	string temp = "", mCode = "";
	for (int i = 0; i < bitCode.size(); i += 2){
		temp = bitCode.at(i);
		temp += bitCode.at(i + 1);
		if (temp == "01"){
			mCode += "-";
		}
		else if (temp == "10"){
			mCode += ".";
		}
		else if (temp == "00"){
			mCode += "|";
		}
		else if (temp == "11"){
			mCode += "/";
		}
		else{
			cout << "Incorrect Bit Code!\n";
		}
	}
	setMorseCode(mCode);
}

/******** class Unichar contain decrypted message **********/
class Unichar : public bitToMorse
{
public:
	Unichar(){};
	Unichar(unsigned char *file, int);

private:
	vector<char> uniqueChar;
};

Unichar::Unichar(unsigned char *file, int size)
{
	for (int i = 0; i < size; i++){
		uniqueChar.push_back(file[i]);
	}
	
	toBits(uniqueChar);
}

/*******************************************/
class Decrypter
{
public:
	Decrypter();

private:
	ifstream infile;
};

Decrypter::Decrypter()
{
	unsigned char *file;
	int size;

	infile.open("Morse.bin", ios::in | ios::binary);

	if (infile.is_open()){
		infile.seekg(0, ios::end);
		size = infile.tellg();
		file = new unsigned char[size];
		infile.seekg(0, ios::beg);
		infile.read((char*)file, size);
		Unichar unichar(file, size);
		infile.close();
		delete[] file;
	}
	else{
		cout << "File can't be opened!" << endl;
	}
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

void main(){
	enableDebug(true);

	Decrypter decrypter;

	system("pause");
}
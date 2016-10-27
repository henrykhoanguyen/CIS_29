#include "Measurement.h"
#include <vector>

using namespace std;

class mCalculation
{
private:
	int convertee;
	int converted;
	double value;

public:
	mCalculation();
	~mCalculation();
	void setConvertee(int cee);
	void setConverted(int ced);
	void setValue(double v);
	double getConvertee(){ return convertee; }
	double getConverted(){ return converted; }
	double getValue() { return value; }
	double conversion();
};

mCalculation::mCalculation()
{
	convertee = 0;
	converted = 0;
	value = 0.0;
}

mCalculation::~mCalculation()
{

}

void mCalculation::setConvertee(int cee){
	convertee = cee;
}

void mCalculation::setConverted(int ced){
	converted = ced;
}

void mCalculation::setValue(double v){
	value = v;
}

double mCalculation::conversion(){
	double result = value;
	int size1, size2;
	Measurement measurement;

	if (convertee == 3 || convertee == 6){
		size1 = 3;
	}
	else if (convertee == 2 || convertee == 5 || 
		convertee == 8 || convertee == 10 ||
		convertee == 11 || convertee == 13){
		size1 = 2;
	}
	else if (convertee == 1 || convertee == 4 ||
		convertee == 7 || convertee == 9 ||
		convertee == 12){
		size1 = 1;
	}

	if (converted == 1 || converted == 4 || converted == 7 ||
		converted == 9 || converted == 12){
		size2 = 0;
	}
	else if (converted == 2 || converted == 5 || converted == 10 ||
		converted == 8 || converted == 13 || converted == 11){
		size2 = 1;
	}
	else{
		size2 = 2;
	}

	if (convertee == 7 && (converted == 12 || converted == 13)){
		convertee = 11;
	}
	vector <double> arr1 = measurement.getMeasurement(convertee);
	vector <double> arr2 = measurement.getMeasurement(converted);

	for (int i = 0; i < size1; i++){
		result *= arr1[i];
	}

	for (int u = size2; u > 0; u--){
		result /= arr2[u];
	}

	return result;
}

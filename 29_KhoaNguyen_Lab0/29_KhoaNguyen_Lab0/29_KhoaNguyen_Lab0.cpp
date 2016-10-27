#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;

class Measurement
{
private:
	vector<double> metricDistance;
	vector<double> metricWeight;
	vector<double> metricVolume;
	vector<double> usDistance;
	vector<double> usWeight;
	vector<double> usVolume;

public:
	Measurement();
	~Measurement();
	vector <double> getMeasurement(int choice);
};

Measurement::Measurement()
{
	usDistance.push_back(2.54);
	usDistance.push_back(12);
	usDistance.push_back(5280);
	usWeight.push_back(28.375);
	usWeight.push_back(16);
	usVolume.push_back(28.57353);
	usVolume.push_back(128);

	metricDistance.push_back(1 / 2.54);
	metricDistance.push_back(100);
	metricDistance.push_back(1000);
	metricWeight.push_back(1 / 28.375);
	metricWeight.push_back(1000);
	metricVolume.push_back(1 / 29.57353);
	metricVolume.push_back(1000);

}
Measurement::~Measurement()
{
}

vector <double> Measurement::getMeasurement(int choice){
	switch (choice){
	case 1:
	case 2:
	case 3:
		return usDistance;
	case 4:
	case 5:
	case 6:
		return metricDistance;
	case 7:
	case 8:
		return usWeight;
	case 9:
	case 10:
		return metricWeight;
	case 11:
		return usVolume;
	case 12:
	case 13:
		return metricVolume;
	}
}

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

void getFirstUnit();
void getSecondUnit(int choice, double measure);

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

	getFirstUnit();

	system("pause");
}

void getFirstUnit(){
	int choice;
	double measurement;

	do{
		cout << "Choose the First Unit:\n";
		cout << "1. Inch\n";
		cout << "2. Foot\n";
		cout << "3. Mile\n";

		cout << "4. Centermeter\n";
		cout << "5. Meter\n";
		cout << "6. Kilometer\n";

		cout << "7. Ounce\n";
		cout << "8. Pound\n";

		cout << "9. Gram\n";
		cout << "10. Kilogram\n";

		cout << "11. Gallon\n";

		cout << "12. Milliliter\n";
		cout << "13. Liter\n\n";
		cin >> choice;
	} while (choice > 13 || choice < 1);

	do{
		cout << "Enter the Measurement\n";
		cin >> measurement;
	} while (measurement < 0);
	cout << endl;

	getSecondUnit(choice, measurement);
}

void getSecondUnit(int choice, double measure){
	int option;
	mCalculation calculation;

	switch (choice)
	{
	case 1:
	case 2:
	case 3:
		do{
			cout << "Choose the Second Unit:\n";
			cout << "4. Centermeter\n";
			cout << "5. Meter\n";
			cout << "6. Kilometer\n\n";
			cin >> option;
		} while (option < 4 || option > 6);

		break;

	case 4:
	case 5:
	case 6:
		do{
			cout << "Choose the Second Unit:\n";
			cout << "1. Inch\n";
			cout << "2. Foot\n";
			cout << "3. Mile\n\n";
			cin >> option;
		} while (option < 1 || option > 3);
		break;

	case 7:
		do{
			cout << "Choose the Second Unit:\n";
			cout << "9. Gram\n";
			cout << "10. Kilogram\n";
			cout << "12. Milliliter\n";
			cout << "13. Liter\n\n";
			cin >> option;
		} while (option < 9 || option > 13 || option == 11);
		break;

	case 8:
		do{
			cout << "Choose the Second Unit:\n";
			cout << "9. Gram\n";
			cout << "10. Kilogram\n\n";
			cin >> option;
		} while (option != 9 && option != 10);
		break;

	case 9:
	case 10:
		do{
			cout << "Choose the Second Unit:\n";
			cout << "7. Ounce\n";
			cout << "8. Pound\n\n";
			cin >> option;
		} while (option != 7 && option != 8);
		break;

	case 11:
		do{
			cout << "Choose the Second Unit:\n";
			cout << "12. Milliliter\n";
			cout << "13. Liter\n\n";
			cin >> option;
		} while (option != 12 && option != 13);
		break;

	case 12:
	case 13:
		do{
			cout << "Choose the Second Unit:\n";
			cout << "7. Ounce\n";
			cout << "11. Gallon\n\n";
			cin >> option;
		} while (option != 7 && option != 11);
		break;
	default:
		break;
	}

	calculation.setConvertee(choice);
	calculation.setConverted(option);
	calculation.setValue(measure);

	cout << "\nResult: " << calculation.conversion() << endl;
}

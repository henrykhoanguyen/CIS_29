#include <iostream>
#include <cstdlib>
#include <string>
#include "Header.h"

using namespace std; 

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
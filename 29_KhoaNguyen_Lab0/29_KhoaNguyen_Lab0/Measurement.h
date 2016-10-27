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
	usDistance.push_back(2.45);
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
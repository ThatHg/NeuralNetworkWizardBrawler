#include "Values.h"
#include <fstream>

double	Values::nn_errorThreshold			= 0.0;
double	Values::nn_learingRate				= 0.0;
double	Values::nn_bias						= 1.0;
double	Values::nn_momentum					= 0.0;

Values::Values()
{
	if(!Load("values.ini"))
		return;
}

bool Values::Load(char* file)
{
	std::ifstream valueFile(file);
	if(!valueFile)
		return false;

	char nameOfValue[100];

	valueFile >> nameOfValue;
	valueFile >> nn_errorThreshold;
	valueFile >> nameOfValue;
	valueFile >> nn_learingRate;
	valueFile >> nameOfValue;
	valueFile >> nn_bias;
	valueFile >> nameOfValue;
	valueFile >> nn_momentum;

	return true;
}
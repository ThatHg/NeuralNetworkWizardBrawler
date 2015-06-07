#include "Values.h"
#include <fstream>

double	Values::e_constant					= 2.71828182845904523536028747135266250;
int		Values::nn_neuronsPerHiddenLayer	= 0;
int		Values::nn_hiddenLayerCount			= 0;
int		Values::nn_outputCount				= 0;
int		Values::nn_inputCount				= 0;
bool	Values::nn_useSigmoid				= false;
double	Values::nn_errorThreshold			= 0.0;
double	Values::nn_learingRate				= 0.0;
double	Values::nn_bias						= 1.0;

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
	valueFile >> nn_neuronsPerHiddenLayer;
	valueFile >> nameOfValue;
	valueFile >> nn_hiddenLayerCount;
	valueFile >> nameOfValue;
	valueFile >> nn_outputCount;
	valueFile >> nameOfValue;
	valueFile >> nn_inputCount;
	valueFile >> nameOfValue;
	valueFile >> nn_useSigmoid;
	valueFile >> nameOfValue;
	valueFile >> nn_errorThreshold;
	valueFile >> nameOfValue;
	valueFile >> nn_learingRate;
	valueFile >> nameOfValue;
	valueFile >> nn_bias;

	return true;
}
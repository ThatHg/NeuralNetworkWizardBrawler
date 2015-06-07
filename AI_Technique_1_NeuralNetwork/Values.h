/*
	This class grabs values from an ini file and store them in static variables
*/
#ifndef VALUES_H
#define VALUES_H

class Values
{
public:
	static double	e_constant;

	static int		nn_neuronsPerHiddenLayer;
	static int		nn_hiddenLayerCount;
	static int		nn_outputCount;
	static int		nn_inputCount;
	static bool		nn_useSigmoid;
	static double	nn_errorThreshold;
	static double	nn_learingRate;
	static double	nn_bias;
	
	Values();

	bool Load(char* file);
};

#endif
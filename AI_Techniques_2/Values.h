/*
	This class grabs values from an ini file and store them in static variables
*/
#ifndef VALUES_H
#define VALUES_H

class Values
{
public:
	static double	nn_errorThreshold;
	static double	nn_learingRate;
	static double	nn_bias;
	static double	nn_momentum;
	
	Values();

	bool Load(char* file);
};

#endif
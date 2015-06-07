#include "WeightSaver.h"
#include <fstream>
#include <iostream>

using namespace std;

WeightSaver::WeightSaver() :
	m_weights()
{
}

WeightSaver::~WeightSaver()
{

}

WeightSaver::WeightSaver(const WeightSaver& weightS)
{
}

WeightSaver& WeightSaver::operator=(const WeightSaver& weightS)
{
	return *this;
}

bool WeightSaver::Load()
{
	ifstream weightFile("weights.txt");
	double weight = 0;
	m_weights.clear();

	if(weightFile.is_open())
	{
		while(!weightFile.eof())
		{
			weightFile >> weight;
			m_weights.push_back(weight);
		}
	}
	else return false;
	weightFile.close();

	return true;
}

bool WeightSaver::Save(const vector<double>& weights)
{
	ofstream weightFile;
	weightFile.open("weights.txt", ios::trunc);
	if(weightFile.is_open())
	{
		for(int i=0; i<weights.size(); ++i)
		{
			weightFile << weights[i] << endl;
		}
	}
	else return false;
	weightFile.close();

	return true;
}

const vector<double>& WeightSaver::GetWeights() const
{
	return m_weights;
}
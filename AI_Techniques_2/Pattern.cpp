#include "Pattern.h"

using namespace std;

const double number[4][16] =
{
	0,-1, 0,-1, 0,-1, 0,-1, 0,-1, 0,-1, 0,-1, 0,-1,		// Fire pattern		(1,0,0,0)
	-1,0, -1,0, -1,0, -1,0, -1,0, -1,0, -1,0, -1,0,		// Water pattern	(0,1,0,0)
	0,1, 0,1, 0,1, 0,1, 0,1, 0,1, 0,1, 0,1,				// Earth pattern	(0,0,1,0)
	1,0, 1,0, 1,0, 1,0, 1,0, 1,0, 1,0, 1,0				// Air pattern		(0,0,0,1)
};

Pattern::Pattern() :
	m_trainingPatterns(4),
	m_expectedValues(4)
{
	for(int pattern = 0; pattern < 4; ++pattern)
	{
		for(int i=0; i<16; ++i)
		{
			m_trainingPatterns[pattern].push_back(number[pattern][i]);
		}
		for(int i=0; i<4; ++i)
		{
			if(i == pattern)
				m_expectedValues[i].push_back(1);
			else
				m_expectedValues[i].push_back(0);
		}
	}
	m_patternCount		= m_trainingPatterns.size();
	m_valuesPerPattern	= m_trainingPatterns[0].size();
}

Pattern::~Pattern()
{
}

Pattern::Pattern(const Pattern& pattern) :
	m_trainingPatterns(pattern.m_trainingPatterns),
	m_expectedValues(pattern.m_expectedValues)
{
}

Pattern& Pattern::operator=(const Pattern& pattern)
{
	m_trainingPatterns	= pattern.m_trainingPatterns;
	m_expectedValues	= pattern.m_expectedValues;

	return *this;
}

const int Pattern::GetPatternCount() const
{
	return m_patternCount;
}

const int Pattern::GetValuesPerPattern() const
{
	return m_valuesPerPattern;
}

const vector<vector<double>>& Pattern::GetTrainingPatterns() const
{
	return m_trainingPatterns;
}

const vector<vector<double>>& Pattern::GetExpectedValues() const
{
	return m_expectedValues;
}

void Pattern::SetTrainingPatterns(const vector<vector<double>>& trainingPatterns)
{
	m_trainingPatterns = trainingPatterns;
}

void Pattern::SetExpectedValues(const vector<vector<double>>& expectedValues)
{
	m_expectedValues = expectedValues;
}
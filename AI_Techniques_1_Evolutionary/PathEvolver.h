#ifndef PATH_EVOLVER_H
#define PATH_EVOLVER_H
//------------------------------------------------------------------------------
#include <vector>
#include "EALEvolutionaryAlgorithm.h"
#include "VGCVirtualGameConsole.h"
//------------------------------------------------------------------------------
class ObstacleField;
//------------------------------------------------------------------------------
class PathEvolver
{
public:
	PathEvolver(const VGCVector& start, const VGCVector& finish);
	~PathEvolver();
	void Paint();
	void EvolveGeneration(int numberOfGenerations);

private:
	typedef std::vector<VGCVector> PositionVector;
	
	const PositionVector	GetPath(const EALGenome& genome) const;
	double					GetFitness(const EALGenome& genome) const;
	const EALIndividual		GetBestIndividual() const;
	double					CalculatePathCost(const PositionVector& solution) const;
	double					GetLength(const VGCVector& from, const VGCVector& to) const;

	const VGCVector		m_start;
	const VGCVector		m_finish;
	ObstacleField*		m_obstacleField;
	EALPopulation		m_population;
	EALEvolver			m_evolver;
	EALIndividual		m_bestIndividual;
	int					m_evolvedGenerations;
};
//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------
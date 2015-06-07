#include "PathEvolver.h"
#include "ObstacleField.h"
#include "Obstacle.h"
#include <sstream>
//------------------------------------------------------------------------------
const double COST_WITHOUT_OBSTACLE = 1.0;
//------------------------------------------------------------------------------
using namespace std;
//------------------------------------------------------------------------------
PathEvolver::PathEvolver(const VGCVector& start, const VGCVector& finish):
	m_start(start),
	m_finish(finish),
	m_population(),
	m_evolver(),
	m_bestIndividual(),
	m_evolvedGenerations(0)
{
	m_obstacleField = new ObstacleField(20, 600, 400, 20, 100, 200, 1000);

	int pop = 20;
	int geneNumber = 20;

	for(int i = 0; i < pop; i++)
	{
		EALGenome genome(geneNumber);
		genome.randomize();
		m_population.addIndividual(EALIndividual(genome, GetFitness(genome)));
	}

	EALConstMemberEvaluatorImp<PathEvolver> evaluatorImp(*this, &PathEvolver::GetFitness);
	EALEvaluator                        evaluator(evaluatorImp);

	EALTournamentSelectorImp selectorImp(8);
	EALSelector              selector(selectorImp);

	EALDualCombinatorImp combinatorImp;
	EALCombinator        combinator(combinatorImp);

	EALResetMutatorImp mutatorImp;
	EALMutator         mutator(mutatorImp);

	EALBasicEvolverImp evolverImp(
		evaluator, 
		selector, 
		combinator, 
		mutator, 
		0.75, 
		0.09
	);

	m_evolver = EALEvolver(evolverImp);

	m_bestIndividual = GetBestIndividual();
}
//------------------------------------------------------------------------------
PathEvolver::~PathEvolver()
{
	delete(m_obstacleField);
}
//------------------------------------------------------------------------------
void PathEvolver::Paint()
{
	const VGCColor text		= VGCColor(255, 0, 0, 0);
	const VGCColor node		= VGCColor(255, 50, 0, 0);
	const VGCColor edge		= VGCColor(255, 0, 0, 0);
	const VGCColor obstacle = VGCColor(128, 0, 200, 0);

	const int width			= m_obstacleField->GetWidth();
	const int height		= m_obstacleField->GetHeight();

	VGCDisplay::beginFrame();

	VGCFont font = VGCDisplay::openFont("Consolas", 10);
	VGCVector cursor = VGCVector(0, 0);

	// Obstacles
	ObstacleField::ObstacleVector obstacles = m_obstacleField->GetObstacles();
	for(int i=0; i<obstacles.size(); i++)
	{
		const VGCVector &position = obstacles[i]->GetPosition();
		const VGCRectangle rectangle(position, obstacles[i]->GetRadius()*2.0, obstacles[i]->GetRadius()*2.0);
		const VGCAdjustment adjust(0.5, 0.5);
		
		ostringstream generationStream;
		generationStream << obstacles[i]->GetCost();
		VGCDisplay::renderString(font, generationStream.str(), text, position, VGCAdjustment(0.0, 0.0));

		VGCDisplay::renderEllipse(rectangle, obstacle, adjust, true);
	}

	// The Best path found so far
	const PositionVector path = GetPath(m_bestIndividual.getGenome());

	// edges
	for(int i=0; i<path.size()-1; i++)
	{
		VGCDisplay::renderLine(edge, path[i], path[i+1]);
	}

	// nodes
	for(int i=0; i<path.size(); i++)
	{
		const VGCVector &position = path[i];
		const VGCRectangle rectangle(position, 10, 10);
		const VGCAdjustment adjust(0.5, 0.5);
		
		VGCDisplay::renderEllipse(rectangle, node, adjust, true);
	}

	

	

	ostringstream generationStream;
	generationStream << "Generation : " << m_evolvedGenerations;
	VGCDisplay::renderString(font, generationStream.str(), text, cursor, VGCAdjustment(0.0, 0.0));
	cursor += VGCVector(0, 10);

	ostringstream bestStream;
	bestStream << "Best fitness so far : " << m_bestIndividual.getFitness() << " (displayed on screen)";
	VGCDisplay::renderString(font, bestStream.str(), text, cursor, VGCAdjustment(0.0, 0.0));
	cursor += VGCVector(0, 10);

	ostringstream maxStream;
	maxStream << "Maximum fitness : " << m_population.getMaximumFitness();
	VGCDisplay::renderString(font, maxStream.str(), text, cursor, VGCAdjustment(0.0, 0.0));
	cursor += VGCVector(0, 10);

	ostringstream minStream;
	minStream << "Minimum fitness : " << m_population.getMinimumFitness();
	VGCDisplay::renderString(font, minStream.str(), text, cursor, VGCAdjustment(0.0, 0.0));
	cursor += VGCVector(0, 10);

	ostringstream avgStream;
	avgStream << "Average fitness : " << m_population.getAverageFitness();
	VGCDisplay::renderString(font, avgStream.str(), text, cursor, VGCAdjustment(0.0, 0.0));
	cursor += VGCVector(0, 10);

	ostringstream costStream;
	costStream << "Cost to travel path : " << CalculatePathCost(GetPath(m_bestIndividual.getGenome())) << " (displayed on screen)";
	VGCDisplay::renderString(font, costStream.str(), text, cursor, VGCAdjustment(0.0, 0.0));
	cursor += VGCVector(0, 10);

	VGCDisplay::closeFont(font);


	VGCDisplay::endFrame();
}
//------------------------------------------------------------------------------
void PathEvolver::EvolveGeneration(int numberOfGenerations)
{
	EALPopulation childPop;
	while(numberOfGenerations != 0)
	{
		m_evolver.evolve(m_population);
		if(m_bestIndividual.getFitness() < m_population.getMaximumFitness())
			m_bestIndividual = GetBestIndividual();

		numberOfGenerations--;
		m_evolvedGenerations++;
	}
}
//------------------------------------------------------------------------------
double PathEvolver::GetFitness(const EALGenome& genome) const
{
	const PositionVector solution	= GetPath(genome);
	double cost						= CalculatePathCost(solution);
	double minCost					= GetLength(m_start, m_finish) * COST_WITHOUT_OBSTACLE;
	double fitness					= minCost / cost;

	return fitness;
}
//------------------------------------------------------------------------------
const PathEvolver::PositionVector PathEvolver::GetPath(const EALGenome& genome) const
{
	PositionVector path;
	path.push_back(m_start);
	for(int i = 0; i < genome.getGeneCount(); i+=2)
	{
		path.push_back(VGCVector(
			 genome[i].getInteger(0, m_obstacleField->GetWidth()),
			 genome[i+1].getInteger(0, m_obstacleField->GetHeight())));
	}
	path.push_back(m_finish);

	return path;
}
//------------------------------------------------------------------------------
double PathEvolver::CalculatePathCost(const PositionVector& solution) const
{
	double time = 0;
	double length = 0;
	for(int i = 0; i < solution.size()-1; i++)
	{
		//vector<int> indexes = m_obstacleField->GetObstaclesAtPosition(solution[i]);
		vector<int> indexes = m_obstacleField->GetObstaclesBetweenPositions(solution[i], solution[i+1]);
		
		if(indexes.size() == 0)
			time += COST_WITHOUT_OBSTACLE;

		for(int j = 0; j < indexes.size(); j++)
		{
			time += m_obstacleField->GetObstacleCost(indexes[j]);
		}
	}

	for(int i = 0; i < solution.size()-1; i++)
	{	
		length += GetLength(solution[i], solution[i+1]);
	}

	return length + time;
}
//------------------------------------------------------------------------------
const EALIndividual PathEvolver::GetBestIndividual() const
{
	double maxFitness = m_population.getMaximumFitness();
	for(int i = 0; i < m_population.getIndividualCount(); i++)
	{
		if(maxFitness == m_population[i].getFitness())
			return m_population[i];
	}
	return m_population[0];
}
//------------------------------------------------------------------------------
double PathEvolver::GetLength(const VGCVector& from, const VGCVector& to) const
{
	double xd = to.getX() - from.getX();
	double yd = to.getY() - from.getY();

	return sqrt((xd*xd) + (yd*yd));
}
//------------------------------------------------------------------------------

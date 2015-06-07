#ifndef A_STAR_H
#define A_STAR_H

#include <SFML\Graphics.hpp>
#include <vector>
#include <list>
#include "Graph.h"

class Edge;
class Node;

class AStar
{
public:
	typedef std::vector<std::vector<sf::Vertex>> WallVector;

	AStar();
	~AStar();

	std::vector<const Node*> GetPath(sf::Vector2f& root, sf::Vector2f& target);
	const WallVector& GetWalls() const;
	WallVector& GetWalls();
	const Graph& GetGraph() const;
	Graph& GetGraph();
	void GenerateWalls();

private:
	void GenerateGraph(sf::Vector2f& root, sf::Vector2f& target); // Create a graph of every available path between walls
	std::vector<const Node*> CalculatePath(sf::Vector2f& target); // Calculate The Shortest Path from shortest path tree
	std::vector<const Node*> CalculateTree(sf::Vector2f& target); // Use the A-Star-algoritm to calculate the shortest path tree
	double CalculateDistance(const sf::Vector2f& source, const sf::Vector2f& target);
	void Clean();

	std::list<const Node*>		m_priorityNodes;
	std::vector<const Node*>	m_searchedNodes;
	std::vector<const Node*>	m_shortesPath;

	std::vector<Node*>			m_nodes;
	const Node*					m_currentNode;

	Graph						m_graph;

	WallVector m_walls;
};

#endif
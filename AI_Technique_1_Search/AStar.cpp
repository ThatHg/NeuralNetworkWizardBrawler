#include "AStar.h"
#include "Edge.h"
#include "Graph.h"
#include "Node.h"

#include <math.h>

float min(float a, float b)
{
	if(a < b)
		return a;

	return b;
}

float max(float a, float b)
{
	if(a > b)
		return a;

	return b;
}

/* ************************************************************************************
	This code is taken from http://flassari.is/2008/11/line-line-intersection-in-cplusplus/
	and modified to fit my needs.
*/
bool intersection(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3, sf::Vector2f p4) 
{
	// Epsilon to compensate for rounding errors
	const float epsilon = 0.00001f;

	// Store the values for fast access and easy
	// equations-to-code conversion
	float x1 = p1.x, x2 = p2.x, x3 = p3.x, x4 = p4.x;
	float y1 = p1.y, y2 = p2.y, y3 = p3.y, y4 = p4.y;
 
	float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	// If d is zero, there is no intersection
	if (d == 0) return false;
 
	// Get the x and y
	float pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
	float x = ( pre * (x3 - x4) - (x1 - x2) * post ) / d;
	float y = ( pre * (y3 - y4) - (y1 - y2) * post ) / d;
 
	// Check if the x and y coordinates are within both lines
	if (x < (min(x1, x2) - epsilon) ||
		x > (max(x1, x2) + epsilon) ||
		x < (min(x3, x4) - epsilon) ||
		x > (max(x3, x4) + epsilon))
				return false;
	if (y < (min(y1, y2) - epsilon) ||
		y > (max(y1, y2) + epsilon) ||
		y < (min(y3, y4) - epsilon) ||
		y > (max(y3, y4) + epsilon))
				return false;
	/*
	// Point of intersection if needed later
	sf::Vertex* ret = new sf::Vertex();
	ret->position.x = x;
	ret->position.y = y;
	*/
	// Return true if there is an intersection
	return true;
}
/*************************************************************/

AStar::AStar()
{
	srand(unsigned int(time(0)));
}

AStar::~AStar()
{
}

std::vector<const Node*> AStar::GetPath(sf::Vector2f& root, sf::Vector2f& target)
{
	if(m_walls.empty())
		GenerateWalls();

	Clean();

	GenerateGraph(root, target);
	
	return CalculatePath(target);
}

const AStar::WallVector& AStar::GetWalls() const
{
	return m_walls;
}

AStar::WallVector& AStar::GetWalls()
{
	return m_walls;
}

const Graph& AStar::GetGraph() const
{
	return m_graph;
}

Graph& AStar::GetGraph()
{
	return m_graph;
}

void AStar::GenerateGraph(sf::Vector2f& root, sf::Vector2f& target)
{	
	// Initiate with root node
	m_nodes.push_back(m_graph.AddNode(root));
	m_nodes[0]->SetCostToRoot(0);
	m_nodes[0]->SetCostToTarget(CalculateDistance(root, target));
	bool cleanPath = true, doesIntersect = true;

	for(int i=0; i<m_walls.size(); i++)
	{
		// Add first and last wall m_nodes from every wall
		m_nodes.push_back(m_graph.AddNode(m_walls[i][0].position));
		m_nodes.push_back(m_graph.AddNode(m_walls[i][m_walls[i].size()-1].position));
	}
	// End with target node
	m_nodes.push_back(m_graph.AddNode(target));

	// Create a graph
	for(int i=0; i<m_nodes.size(); i++)
	{
		// Add every node inside 
		for(int k=0; k<m_nodes.size(); k++)
		{
			// Skipp if two m_nodes are the same node.
			if(m_nodes[i]->GetIndex() != m_nodes[k]->GetIndex())
			{
				// Create a edges between two m_nodes where there are no walls obstructing the path
				for(int j=0; j<m_walls.size(); j++)
				{
					doesIntersect = intersection(m_nodes[i]->GetPosition(), 
												m_nodes[k]->GetPosition(), 
												m_walls[j][0].position, 
												m_walls[j][m_walls[j].size()-1].position);
					
					// Dont skipp if a node acually exist in a wall segment
					if(doesIntersect &&	(m_walls[j][0].position == m_nodes[k]->GetPosition() || m_walls[j][m_walls[j].size()-1].position == m_nodes[k]->GetPosition() ||
										m_walls[j][0].position == m_nodes[i]->GetPosition() || m_walls[j][m_walls[j].size()-1].position == m_nodes[i]->GetPosition()) == false)
					{
						cleanPath = false;
					}	
				}
				if(cleanPath == true)
				{
					// Only add if the edge does not exist!
					if(m_graph.GetEdge(m_nodes[i], m_nodes[k]) == NULL)
							m_graph.AddEdge(m_nodes[i], m_nodes[k]);
				}
				cleanPath = true;
			}
		}
	}
}

bool Compare(const Node* a, const Node* b)
{
	return (a->GetCostToTarget() < b->GetCostToTarget());  
}

bool AlreadySearched(Node* source, std::vector<const Node*>& node)
{
	for(int i=0; i<node.size(); i++)
	{
		if(source->GetIndex() == node[i]->GetIndex())
			return true;
	}

	return false;
}

bool ExistInList(std::list<const Node*>& list, Node* source)
{
	for(std::list<const Node*>::iterator itr = list.begin(); itr != list.end(); itr++)
	{
		if((*itr)->GetIndex() == source->GetIndex())
			return true;
	}

	return false;
}

std::vector<const Node*> AStar::CalculatePath(sf::Vector2f& target)
{
	std::vector<const Node*> shortestPathTree = CalculateTree(target);
	const Node* current = shortestPathTree[shortestPathTree.size()-1];

	if(current->GetParent() == NULL)
	{
		m_shortesPath.push_back(current);
		return m_shortesPath;
	}

	while(current->GetIndex() != shortestPathTree[0]->GetIndex())
	{
		m_shortesPath.push_back(current);
		current = current->GetParent();
	}
	m_shortesPath.push_back(shortestPathTree[0]);

	std::reverse(m_shortesPath.begin(), m_shortesPath.end());

	return m_shortesPath;
}

std::vector<const Node*> AStar::CalculateTree(sf::Vector2f& target)
{
	// Node with index 0 is always root node
	m_priorityNodes.push_back(m_graph.GetNode(0));
	
	std::vector<Node*> neighbors;
	double costToRoot = 0;
	double costToTarget = 0;
	double heuristicCost = 0;

	while(m_priorityNodes.empty() == false && m_priorityNodes.front()->GetPosition() != target)
	{
		m_currentNode = m_priorityNodes.front();
		m_priorityNodes.pop_front();
		m_searchedNodes.push_back(m_currentNode);

		neighbors = m_graph.GetNeighborNodes(m_currentNode);
		for(int i=0; i<neighbors.size(); i++)
		{
			// Check if nodes are not the same
			if(neighbors[i]->GetIndex() != m_currentNode->GetIndex())
			{
				// Calculate the heuristic cost from this neighboring node to target
				heuristicCost = CalculateDistance(target, neighbors[i]->GetPosition());

				// Calculate the cost from source path to the neigboring node
				costToRoot = m_currentNode->GetCostToRoot() + CalculateDistance(m_currentNode->GetPosition(), neighbors[i]->GetPosition());

				if(AlreadySearched(neighbors[i], m_searchedNodes) && costToRoot >= neighbors[i]->GetCostToRoot())
					continue;

				if(neighbors[i]->GetCostToRoot() == -1 || costToRoot < neighbors[i]->GetCostToRoot())
				{
					neighbors[i]->SetParent(m_currentNode);

					// Calculate the cost from source path to the neigboring node to the target node
					costToTarget = costToRoot + heuristicCost;

					// Store the distances
					neighbors[i]->SetCostToTarget(costToTarget);
					neighbors[i]->SetCostToRoot(costToRoot);

					if(ExistInList(m_priorityNodes, neighbors[i]) == false)
					{
						m_priorityNodes.push_back(neighbors[i]);
					}
				}
			}
		}

		// This part act as the priority queue stage
		// The nodes with nearest distance to targets gets higher priority
		m_priorityNodes.sort(Compare);
	}
	
	// Add the target to the path too
	m_searchedNodes.push_back(m_graph.GetNodesAtPosition(target)[0]);

	return m_searchedNodes;
}

void AStar::GenerateWalls()
{
	if(m_walls.size() > 0)
		m_walls.clear();

	for(int i=0; i<15; i++)
	{
		std::vector<sf::Vertex> temp;
		temp.push_back(sf::Vertex(sf::Vector2f(float(rand()%1120 + 80), float(rand()%560 + 80))));
		temp.push_back(sf::Vertex(sf::Vector2f(float(rand()%1120 + 80), float(rand()%560 + 80))));
		m_walls.push_back(temp);
	}
}

double AStar::CalculateDistance(const sf::Vector2f& source, const sf::Vector2f& target)
{
	double xD = target.x - source.x;
	double yD = target.y - source.y;
	return std::sqrt(xD * xD + yD * yD);
}

void AStar::Clean()
{
	m_graph.Clean();
	m_nodes.clear();
	m_priorityNodes.clear();
	m_searchedNodes.clear();
	m_shortesPath.clear();
}
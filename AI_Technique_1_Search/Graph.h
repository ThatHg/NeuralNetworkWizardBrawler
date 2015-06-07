#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <SFML\Graphics.hpp>

class Node;
class Edge;

class Graph
{
public:
	typedef std::vector<Node*> NodeVector;
	typedef std::vector<Edge*> EdgeVector;

	Graph();
	~Graph();

	NodeVector GetNodesAtPosition(sf::Vector2f& position);
	const Node* GetNode(int index) const;
	const Edge* GetEdge(const Node* first, const Node* second) const;
	const EdgeVector& GetEdges() const;
	EdgeVector& GetEdges();

	Node* AddNode(sf::Vector2f& position);
	void AddEdge(Node* first, Node* second);

	EdgeVector GetConnectingEdgesToNode(const Node* source);
	NodeVector GetNeighborNodes(const Node* source);

	void Clean();
	
	int NumberOfNodes();

private:
	NodeVector m_nodes;
	EdgeVector m_edges;

	int m_nodeIndex;
};

#endif
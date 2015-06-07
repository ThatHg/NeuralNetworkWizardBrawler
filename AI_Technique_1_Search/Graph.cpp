#include "Graph.h"
#include "Edge.h"
#include "Node.h"

Graph::Graph() :
	m_nodeIndex(-1)
{
}

Graph::~Graph()
{
}

Graph::NodeVector Graph::GetNodesAtPosition(sf::Vector2f& position)
{
	NodeVector nodes;
	for(int i=0; i<m_nodes.size(); i++)
	{
		if(m_nodes[i]->GetPosition() == position)
		nodes.push_back(m_nodes[i]);
	}
	return nodes;
}

const Node* Graph::GetNode(int index) const
{
	for(int i=0; i<m_nodes.size(); i++)
	{
		if(m_nodes[i]->GetIndex() == index)
			return m_nodes[i];
	}

	return NULL;
}
const Edge* Graph::GetEdge(const Node* first, const Node* second) const
{
	for(int i=0; i<m_edges.size(); i++)
	{
		// Check if those two nodes exist in an edge
		if(	(m_edges[i]->First() == first && m_edges[i]->Second() == second) ||
			(m_edges[i]->First() == second && m_edges[i]->Second() == first))
			return m_edges[i];
	}

	return NULL;
}

const Graph::EdgeVector& Graph::GetEdges() const
{
	return m_edges;
}

Graph::EdgeVector& Graph::GetEdges()
{
	return m_edges;
}

Node* Graph::AddNode(sf::Vector2f& position)
{
	// Do not add another node at same position
	for(int i=0; i<m_nodes.size(); i++)
		if(m_nodes[i]->GetPosition() == position)
			return m_nodes[i];

	// increment nodeIndex whenever a new node gets created
	m_nodeIndex++;

	Node* node = new Node(m_nodeIndex, position);
	m_nodes.push_back(node);

	return node;
}

void Graph::AddEdge(Node* first, Node* second)
{
	Edge* edge = new Edge(first, second);
	m_edges.push_back(edge);
}

Graph::EdgeVector Graph::GetConnectingEdgesToNode(const Node* source)
{
	EdgeVector ev;
	for(int i=0; i<m_edges.size(); i++)
	{
		if(m_edges[i]->First()->GetIndex() == source->GetIndex() || m_edges[i]->Second()->GetIndex() == source->GetIndex())
			ev.push_back(m_edges[i]);
	}
	return ev;
}

Graph::NodeVector Graph::GetNeighborNodes(const Node* source)
{
	NodeVector nv;
	for(int i=0; i<m_edges.size(); i++)
	{
		if(m_edges[i]->First()->GetIndex() == source->GetIndex())
			nv.push_back(m_edges[i]->Second());
		else if(m_edges[i]->Second()->GetIndex() == source->GetIndex())
			nv.push_back(m_edges[i]->First());
	}
	return nv;
}

int Graph::NumberOfNodes()
{
	return int(m_nodes.size());
}

void Graph::Clean()
{
	while(!m_nodes.empty())
	{
		delete m_nodes.back();
		m_nodes.pop_back();
	}

	while(!m_edges.empty())
	{
		delete m_edges.back();
		m_edges.pop_back();
	}

	m_nodeIndex = -1;
}
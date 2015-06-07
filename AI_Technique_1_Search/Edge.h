#ifndef EDGE_H
#define EDGE_H

class Node;

class Edge
{
public:
	Edge(Node* first, Node* second);
	~Edge();

	void SetFirstNode(Node* first);
	const Node* First() const;
	Node* First();

	void SetSecondNode(Node* second);
	const Node* Second() const;
	Node* Second();

	double Distance(); // Return the distance between the two nodes

private:
	Node* m_first;
	Node* m_second;
};

#endif
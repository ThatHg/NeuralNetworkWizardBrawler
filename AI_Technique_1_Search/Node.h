#ifndef NODE_H
#define NODE_H

#include <SFML\Graphics.hpp>

class Node
{
public:
	Node(int index, sf::Vector2f position);
	~Node();
	
	int GetIndex() const;
	const sf::Vector2f& GetPosition() const;
	const double GetCostToTarget() const;
	double GetCostToTarget();
	const double GetCostToRoot() const;
	double GetCostToRoot();
	const Node* GetParent() const;
	Node* GetParent();
	
	void SetIndex(int index);
	void SetPosition(sf::Vector2f& position);
	void SetCostToTarget(double cost);
	void SetCostToRoot(double cost);
	void SetParent(const Node* node);

private:
	int m_index;
	sf::Vector2f m_position;
	const Node* m_parent;
	double m_costToTarget;
	double m_costToRoot;
};

#endif
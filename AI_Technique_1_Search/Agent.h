#ifndef AGENT_H
#define AGENT_H

#include <SFML/Graphics.hpp>
#include <vector>

class Node;

class Agent
{
public:
	Agent(sf::Vector2f& position, sf::Vector2f& target, std::vector<const Node*> subtargets);
	~Agent();

	void SetPosition(sf::Vector2f& position);
	void SetTarget(sf::Vector2f& target);
	void SetSubtarget(sf::Vector2f& subtarget);
	void SetSubtargets(std::vector<const Node*> & subtargets);

	const sf::Vector2f& GetPosition() const;
	sf::Vector2f& GetPosition();
	const sf::Vector2f& GetTarget() const;
	const Node* GetSubtarget() const;
	const std::vector<const Node*>& GetSubtargets() const;

	void ChangeSubtarget();

private:
	sf::Vector2f m_position;
	sf::Vector2f m_target;
	sf::Vector2f m_subtarget;
	std::vector<const Node*> m_subtargets;

	int m_nodeIndex;
};

#endif
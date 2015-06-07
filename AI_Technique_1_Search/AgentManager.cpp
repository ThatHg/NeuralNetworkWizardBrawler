#include "AgentManager.h"
#include "Agent.h"
#include "Node.h"
#include "Edge.h"
#include "Graph.h"
#include <SFML\Graphics.hpp>

AgentManager::AgentManager():
	m_astar(AStar())
{
	InitiateAgents();
}

AgentManager::~AgentManager()
{
	while(!m_agents.empty())
	{
		delete m_agents.back();
		m_agents.pop_back();
	}
}

void AgentManager::InitiateAgents()
{
	sf::Vector2f root = sf::Vector2f(0.0f, 0.0f);
	sf::Vector2f target = sf::Vector2f(1200.0f, 640.0f);
	m_agents.push_back(new Agent(root, target, m_astar.GetPath(root, target)));
}

void AgentManager::Update(sf::RenderWindow& rw)
{
	// Test the ability to recalculate the graph and shortest path for the first agent
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2f mousePos = sf::Vector2f(float(sf::Mouse::getPosition(rw).x), float(sf::Mouse::getPosition(rw).y));
		sf::Vector2f target = sf::Vector2f(1200.0f, 640.0f);
		m_agents[0]->SetSubtargets(m_astar.GetPath(mousePos, target));
		m_agents[0]->SetPosition(mousePos);
	}

	if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		sf::Vector2f target = sf::Vector2f(1280.0f, 720.0f);
		m_astar.GenerateWalls();
		m_agents[0]->SetSubtargets(m_astar.GetPath(m_agents[0]->GetPosition(), target));
	}
	ManageAgentTargets();
	Move();
	Paint(rw);
}

float Interpolate(float a, float b, float c)
{
	return a*(1-c)+b*c;
}

float Distance(const sf::Vector2f& from, const sf::Vector2f& to)
{
	float xD = to.x - from.x;
	float yD = to.y - from.y;
	return std::sqrt(xD * xD + yD * yD);
}

void AgentManager::Move()
{
	// Interpolate between Agent_startpos and Agent_subpos
	for(int i=0; i<m_agents.size(); i++)
	{
		m_agents[i]->SetPosition(sf::Vector2f(	Interpolate(m_agents[i]->GetPosition().x, m_agents[i]->GetSubtarget()->GetPosition().x, 0.001f),
												Interpolate(m_agents[i]->GetPosition().y, m_agents[i]->GetSubtarget()->GetPosition().y, 0.001f)));
	}
}

void AgentManager::ManageAgentTargets()
{
	for(int i=0; i<m_agents.size(); i++)
	{
		// Check if agents have reached their target or
		// if reached subtarget chage subtarget to next subtarget
		if(Distance(m_agents[i]->GetPosition(), m_agents[i]->GetTarget()) < 1)
			continue;
		if(Distance(m_agents[i]->GetPosition(), m_agents[i]->GetSubtarget()->GetPosition()) < 1)
			m_agents[i]->ChangeSubtarget();
	}	
}

void AgentManager::Paint(sf::RenderWindow& rw)
{
	AStar::WallVector wv = m_astar.GetWalls();
	sf::CircleShape shape(20.0f, 20);
	sf::CircleShape pathShape(8.0f, 20);
	sf::CircleShape graphShape(4.0f, 20);
	sf::Vertex line[2];
	sf::Vertex line2[2];
	sf::Vertex line3[2];
	std::vector<const Node*> nodes;
	int index = 1;
	sf::Vertex vertex;
	sf::Vertex vertex2;
	vertex.color = sf::Color(100,0,100);
	vertex2.color = sf::Color(0,200,0);
	graphShape.setFillColor(sf::Color(255,255,255));

	Graph graph = m_astar.GetGraph();
	Graph::EdgeVector edges = graph.GetEdges();

	for(int i=0; i<m_agents.size(); i++)
	{
		shape.setPosition(m_agents[i]->GetPosition() - sf::Vector2f(shape.getRadius(), shape.getRadius()));
		shape.setFillColor(sf::Color(200,0,0));
		rw.draw(shape);

		shape.setPosition(m_agents[i]->GetTarget() - sf::Vector2f(shape.getRadius(), shape.getRadius()));
		shape.setFillColor(sf::Color(0,200,0));
		rw.draw(shape);

		nodes = m_agents[i]->GetSubtargets();
		for(int j=0; j<nodes.size(); j++)
		{
			pathShape.setPosition(nodes[j]->GetPosition() - sf::Vector2f(pathShape.getRadius(), pathShape.getRadius()));
			pathShape.setFillColor(sf::Color(255,240,0));
			rw.draw(pathShape);
			if(index < nodes.size())
			{
				vertex2.position = nodes[j]->GetPosition() + sf::Vector2f(1.0f, 1.0f);
				line[0] = vertex2;
				vertex2.position = nodes[index]->GetPosition() + sf::Vector2f(1.0f, 1.0f);
				line[1] = vertex2;
				index++;
				rw.draw(line, 2, sf::Lines);
			}
		}
	}

	for(int i=0; i<edges.size(); i++)
	{
		vertex.position = edges[i]->First()->GetPosition() - sf::Vector2f(1.0f, 1.0f);
		line3[0] = vertex;
		vertex.position = edges[i]->Second()->GetPosition() - sf::Vector2f(1.0f, 1.0f);
		line3[1] = vertex;
		index++;
		rw.draw(line3, 2, sf::Lines);

		graphShape.setPosition(edges[i]->First()->GetPosition().x - graphShape.getRadius(), edges[i]->First()->GetPosition().y - graphShape.getRadius());
		rw.draw(graphShape);
		graphShape.setPosition(edges[i]->Second()->GetPosition().x - graphShape.getRadius(), edges[i]->Second()->GetPosition().y - graphShape.getRadius());
		rw.draw(graphShape);
	}

	for(int i=0; i<wv.size(); i++)
	{
		line2[0] = wv[i][0];
		line2[1] = wv[i][1];
		rw.draw(line2, 2, sf::Lines);
	}
}
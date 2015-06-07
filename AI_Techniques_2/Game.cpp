#include "Game.h"
#include "Actor.h"
#include "Level.h"
#include "Values.h"
#include "Player.h"
#include <iostream>
#include "GlobalClock.h"

using namespace std;

Game::Game() :
	m_state(&Game::Run),
	m_stack(),
	m_player(new Player(sf::Vector2f(1280/2.0f, 720/1.4f), "player.lua")),
	m_actor(new Actor),
	m_level(new Level("level.lua", m_player)),
	m_window(sf::VideoMode(1280, 720), "Magick"),
	m_paused(false),
	m_rectangle(sf::Vector2f(1280,720))
{
	m_rectangle.setFillColor(sf::Color(100,78,32,100));
}

Game::~Game()
{
	delete m_actor;
}

Game::Game(const Game& game) :
	m_state(game.m_state),
	m_stack(game.m_stack),
	m_player(game.m_player),
	m_actor(game.m_actor),
	m_level(game.m_level),
	m_paused(game.m_paused)
{
}

Game& Game::operator=(const Game& game)
{
	m_state				= game.m_state;
	m_stack				= game.m_stack;
	m_player			= game.m_player;
	m_actor				= game.m_actor;
	m_level				= game.m_level;
	m_paused			= game.m_paused;

	return *this;
}

void Game::Initialize()
{
	Values v;
	v.Load("values.ini");

	m_level->Initialize();
	m_actor->Initialize(m_window);
}

void Game::Main()
{
	sf::Event event;
	while(m_window.isOpen())
	{
		GlobalClock::Ref().Reset();
		while(m_window.pollEvent(event))
		{
			switch(event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;
			case sf::Event::KeyPressed:
				if(event.key.code == sf::Keyboard::Escape)
					m_paused = !m_paused;
			default:
				break;
			}
		}
		
		m_window.clear(sf::Color(128,128,128,255));
		Render();
		Inputs();
		Update();

		m_window.display();
	}
}

void Game::Update()
{
	sf::Vector2f target(float(sf::Mouse::getPosition(m_window).x),float(sf::Mouse::getPosition(m_window).y));
	m_actor->Update(m_window);
	m_level->Update();
	m_player->Update(target);
}

void Game::Render()
{
	m_level->Render(m_window);
	m_player->Render(m_window);
}

void Game::Inputs()
{
	if(m_paused)
		Dispatch(PAUSE);
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
		Dispatch(CONCENTRATE);
	else
		Dispatch(RUN);
}

void Game::Dispatch(Event e)
{
	(this->*m_state)(e);
}

void Game::Transit(State toState)
{
	Dispatch(EXIT);
	m_state = toState;
	Dispatch(ENTER);
}

void Game::Call(State toState)
{
	m_stack.push(m_state);
	Transit(toState);
}
void Game::Result()
{
	State toState = m_stack.top();
	m_stack.pop();
	Transit(toState);
}

void Game::Run(Event e)
{
	switch (e)
	{
	case ENTER:
		cout << "\nALERT: Game Entering [Run] state";
		break;
	case EXIT:
		cout << "\nALERT: Game Exiting [Run] state";
		break;
	case RUN:
		break;
	case PAUSE:
		Call(&Game::Pause);
		break;
	case CONCENTRATE:
		if(m_player->GetConcentration())
		Call(&Game::Concentrate);
		break;
	default:
		break;
	}

}
void Game::Pause(Event e)
{
	switch (e)
	{
	case ENTER:
		cout << "\nALERT: Game Entering [Pause] state";
		break;
	case EXIT:
		cout << "\nALERT: Game Exiting [Pause] state";
		break;
	case RUN:
		Result();
		break;
	case PAUSE:
		// PAUSE
		break;
	case CONCENTRATE:
		break;
	default:
		break;
	}
}
void Game::Concentrate(Event e)
{
	switch (e)
	{
	case ENTER:
		cout << "\nALERT: Game Entering [Concentrate] state";
		GlobalClock::Ref().SetMultiplier(0.1);	// Slow everything down
		m_actor->SetConcentrating(true);
		break;
	case EXIT:
		cout << "\nALERT: Game Exiting [Cencentrate] state";
		GlobalClock::Ref().SetMultiplier(1);	// Take everything back to normal
		m_actor->SetConcentrating(false);
		m_actor->Evaluate();
		m_player->Attack(m_actor->GetMatchedPattern());
		break;
	case RUN:
		Result();
		break;
	case PAUSE:
		Call(&Game::Pause);
		break;
	case CONCENTRATE:
		if(m_player->GetConcentration() <= 0)
			Result();

		m_window.draw(m_rectangle);
		m_actor->Render(m_window);
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
			m_actor->SetDrawing(true);
		else
			m_actor->SetDrawing(false);
		break;
	default:
		break;
	}
}
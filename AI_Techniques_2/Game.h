#ifndef GAME_H
#define GAME_H

#include <stack>
#include <SFML\Graphics.hpp>
#include <sstream>

class Actor;
class Level;
class Player;

class Game
{
public:
	enum Event{ENTER, EXIT, RUN, PAUSE, CONCENTRATE};
	typedef void (Game::*State)(Event e);

	Game();
	~Game();
	Game(const Game& game);
	Game& operator=(const Game& game);

	void Initialize();
	void Main();

private:
	typedef std::stack<State> Stack;

	void Update();
	void Render();
	void Inputs();

	void Run(Event e);
	void Pause(Event e);
	void Concentrate(Event e);
	void Dispatch(Event e);
	void Transit(State toState);
	void Call(State toState);
	void Result();

	Stack				m_stack;
	State				m_state;
	Player*				m_player;
	Actor*				m_actor;
	Level*				m_level;
	sf::RenderWindow	m_window;
	bool				m_paused;
	sf::RectangleShape	m_rectangle;
	std::stringstream	m_text;
};

int main()
{
	Game game;
	game.Initialize();
	game.Main();

	return 0;
}

#endif
#include <SFML/Graphics.hpp>
#include "Actor.h"
#include "Values.h"


int main()
{
	Values v;
	//v.Load("values.ini");
	Actor a;
	a.TrainAndTest();
	

	sf::RenderWindow window(sf::VideoMode(1000, 200), "NeuralNetwork");
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Blue);
		a.Render(window);
		window.display();
	}
	return 0;
}
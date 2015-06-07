#include <SFML/Graphics.hpp>
#include "AgentManager.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "A* Example");
	AgentManager am;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
		am.Update(window);
        window.display();
    }

    return 0;
}
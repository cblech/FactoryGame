#include "SFML\Graphics.hpp"
#include <thread>
#include "GameMap.h"
#include <iostream>
#include "debug.h"

/////////////////////////////////////////////////////////////


void run() {
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

	GameMap garage;


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color(0, 0, 0, 255));
		window.draw(garage);
		window.display();
	}

}


/////////////////////////////////////////////////////////////////////////
int main()
{

	//std::cout << debug() << "Test Debug" << std::endl;
	//std::cout << error() << "Test Error" << std::endl;
	std::thread t(run);

	t.join();

	return 0;
}
#include "SFML\Graphics.hpp"
#include <thread>
#include "GameMap.h"
#include <iostream>
#include "debug.h"
#include "Animation.h"
 

/////////////////////////////////////////////////////////////


void run() {
	//Creating the RenderWindow
	sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");

	//Creating the Map
	sf::RenderTexture mapRenderTexture;
	mapRenderTexture.create(1280, 720);
	sf::Sprite mapSprite;
	GameMap * activeMap = nullptr;

	//Creating garage map
	GameMap garage(1,&mapRenderTexture);
	std::cout << (garage.initByFile("garage.json") ? "Korrekt\n":"Falsch\n");
	activeMap = &garage;

	garage.carlos.solveSpaceDependencies();
	garage.doory.solveSpaceDependencies();


	sf::Clock deltaClock;
	double delta = 0;


	GameMap * openedMap = &garage;

	while (window.isOpen())
	{
		delta = deltaClock.getElapsedTime().asSeconds();
		deltaClock.restart();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed)
				openedMap->mouseClickEvent(event.mouseButton);

			if (event.type == sf::Event::MouseButtonReleased)
				openedMap->mouseReleaseEvent(event.mouseButton);
		}
		garage.checkMousePosition(sf::Mouse::getPosition(window));


		//Step forward all Animations
		auto it = Anim::ANIMATIONS.begin();
		while (it != Anim::ANIMATIONS.end()) {
			(*it)->step(delta);
			if ((*it)->isDone()) {
				it = Anim::ANIMATIONS.erase(it);
			}
			else
				it++;
		}

		//Rendering Map to mapRenderTexture
		mapRenderTexture.setView(activeMap->mapView);
		mapRenderTexture.clear(sf::Color(0, 0, 0, 255));
		mapRenderTexture.draw(garage);
		mapRenderTexture.display();
		mapSprite.setTexture(mapRenderTexture.getTexture());

		//Rendering Window
		window.clear(sf::Color(0, 0, 0, 255));
		window.draw(mapSprite);
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
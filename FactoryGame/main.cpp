#include "SFML\Graphics.hpp"
#include <thread>
#include "GameMap.h"
#include <iostream>
#include "debug.h"
#include "Animation.h"
#include "MapDatabase.h" 


/////////////////////////////////////////////////////////////


void run() {
	//Creating the RenderWindow
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!",sf::Style::Titlebar|sf::Style::Close);

	//Creating the Map
	sf::RenderTexture mapRenderTexture;
	mapRenderTexture.create(window.getSize().x,window.getSize().y);
	sf::Sprite mapSprite;


	//Creating maps
	MapDatabase mdb(&mapRenderTexture, float(window.getSize().x) / window.getSize().y);

	//GameMap garage(1,&mapRenderTexture,float(window.getSize().x)/window.getSize().y);
	//std::cout << (garage.initByFile("shipyard.json") ? "Korrekt\n":"Falsch\n");
	//activeMap = &garage;

	mdb.getMap(1)->carlos.solveSpaceDependencies();
	mdb.getMap(1)->doory.solveSpaceDependencies();
	GameMap * openedMap = mdb.getMap(2);

	openedMap->carlos.solveSpaceDependencies();
	openedMap->doory.solveSpaceDependencies();


	sf::Clock deltaClock;
	double delta = 0;


	while (window.isOpen())
	{
		delta = deltaClock.getElapsedTime().asSeconds();
		deltaClock.restart();


		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				openedMap->mouseClickEvent(event.mouseButton);
				break;
			case sf::Event::MouseButtonReleased:
				openedMap->mouseReleaseEvent(event.mouseButton);
				break;
			case sf::Event::MouseWheelMoved:
				openedMap->zoomCamera(event.mouseWheel.delta);
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::U)
					openedMap = mdb.getMap(1);
				if (event.key.code == sf::Keyboard::Z)
					openedMap = mdb.getMap(2);
					
			//case sf::Event::Resized:
			//	//TODO for every map
			//	//window.setView(sf::View({0.f,0.f}, { float(event.size.width), float(event.size.height) }));
			//	//mapRenderTexture.create(event.size.width, event.size.height);
			//	openedMap->setPixelRatio(float(event.size.width) / event.size.height);
			//	
			//	//openedMap->mapView.setViewport(sf::FloatRect(0.f, 0.f,2.f, 2.f));

			//	openedMap->zoomCamera(0);
				break;
			default:
				break;
			}
		}
		//Mouse Tick
		openedMap->checkMousePosition(sf::Mouse::getPosition(window));

		//Camera move tick
		if (window.hasFocus())
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				openedMap->moveCamera(Direction::up, delta);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				openedMap->moveCamera(Direction::left, delta);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				openedMap->moveCamera(Direction::down, delta);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				openedMap->moveCamera(Direction::right, delta);
		}

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
		mapRenderTexture.setView(openedMap->getMapView());
		mapRenderTexture.clear(sf::Color(0, 0, 0, 255));
		mapRenderTexture.draw(*openedMap);
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
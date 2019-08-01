#include "SFML\Graphics.hpp"
#include <thread>
#include "GameMap.h"
#include <iostream>
#include "debug.h"
#include "Animation.h"
#include "MapDatabase.h" 
#include "Options.h"
#include "Savegame.h"
#include <filesystem>
#include "GlobalDefines.h"

/////////////////////////////////////////////////////////////
std::filesystem::path userDataPath;

int main() {
	//setting the user data path
	{
		char *pValue;
		size_t len;
		_dupenv_s(&pValue, &len, "APPDATA");
		userDataPath = std::filesystem::path(pValue)/"FactoryGame";
	}

	//all savegames
	auto ss = Savegame::getAllSavegames();


	//Creating the options
	Options options;
	
	//creating the savegame
	//Savegame * svg = Savegame::newGame("AktTesty");
	Savegame * svg = new Savegame(ss[0]["path"].get < std::string>());


	//std::cout << userDataPath.root_path() << std::endl;

	std::cout << "exists() = " << std::filesystem::exists(userDataPath) << "\n"
		<< "root_name() = " << userDataPath.root_name() << "\n"
		<< "root_path() = " << userDataPath.root_path() << "\n"
		<< "relative_path() = " << userDataPath.relative_path() << "\n"
		<< "parent_path() = " << userDataPath.parent_path() << "\n"
		<< "filename() = " << userDataPath.filename() << "\n"
		<< "stem() = " << userDataPath.stem() << "\n"
		<< "extension() = " << userDataPath.extension() << "\n";


	for (auto vm : sf::VideoMode::getFullscreenModes())
	{
		std::cout << "Res: " << vm.width << "x" << vm.height << std::endl;
	}

	//Creating the RenderWindow
	auto r = options.getResolution();
	sf::RenderWindow window(sf::VideoMode(r.resolution.x, r.resolution.y), "SFML works!", r.isFullscreen ? sf::Style::Fullscreen : sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(options.getVSync());

	//Creating the Map
	sf::RenderTexture mapRenderTexture;
	mapRenderTexture.create(window.getSize().x,window.getSize().y);
	sf::Sprite mapSprite;
	
	//Creating map database
	MapDatabase mdb(&mapRenderTexture, float(window.getSize().x) / window.getSize().y);

	
	GameMap * openedMap = mdb.getMap(1, svg->getObjects());



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
					openedMap = mdb.getMap(1,svg->getObjects());
				if (event.key.code == sf::Keyboard::Z)
					openedMap = mdb.getMap(2, svg->getObjects());
					
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
			//Save game
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
				svg->gatherAndSave(mdb.getLoadedMaps());

			//move camera by keyboard
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

	delete svg;
	return 0;
}

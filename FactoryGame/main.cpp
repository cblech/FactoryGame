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
#include "GuiWindow.h"
#include "GuiRectangle.h"
#include "Global.h"
#include "ClickableGuiElement.h"
#include "GuiButton.h"
#include "SFML/Network.hpp"

/*
void OpenWebsite(char * cpURL)
{
	ShellExecute(NULL, "open", cpURL, NULL, NULL, SW_SHOWNORMAL);
}
*/


Global global;
/////////////////////////////////////////////////////////////

int main() {


	//setting the user data path

	//all savegames
	auto ss = Savegame::getAllSavegames();


	//Creating the options
	//Options options;

	//creating the savegame
	//Savegame * svg = Savegame::newGame("AktTesty");
	Savegame * svg = new Savegame(ss[0]["path"].get<std::string>());



	//std::cout << "exists() = " << std::filesystem::exists(userDataPath) << "\n"
	//	<< "root_name() = " << userDataPath.root_name() << "\n"
	//	<< "root_path() = " << userDataPath.root_path() << "\n"
	//	<< "relative_path() = " << userDataPath.relative_path() << "\n"
	//	<< "parent_path() = " << userDataPath.parent_path() << "\n"
	//	<< "filename() = " << userDataPath.filename() << "\n"
	//	<< "stem() = " << userDataPath.stem() << "\n"
	//	<< "extension() = " << userDataPath.extension() << "\n";


	for (auto vm : sf::VideoMode::getFullscreenModes())
	{
		std::cout << "Res: " << vm.width << "x" << vm.height << std::endl;
	}

	//Creating the RenderWindow
	auto r = global.options.getResolution();
	sf::RenderWindow window(sf::VideoMode(r.resolution.x, r.resolution.y), "SFML works!", r.isFullscreen ? sf::Style::Fullscreen : sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(global.options.getVSync());

	//Creating the Map
	sf::RenderTexture mapRenderTexture;
	mapRenderTexture.create(window.getSize().x, window.getSize().y);
	sf::Sprite mapSprite;

	//Creating map database
	MapDatabase mdb(&mapRenderTexture, float(window.getSize().x) / window.getSize().y);


	global.openedMap = mdb.getMap(1, svg->getObjects());

	//temp
	GuiWindow guiw(true);
	//GuiWindow guifull(true);
	auto cRight = std::make_shared<GuiContainer>();
	auto btn = std::make_shared<GuiButton>(sf::Vector2f{ 150.f,40.f });

	btn->setClickFunc([]() {std::cout << "Button Click Funcion" << std::endl; });

	guiw.container.addElement(std::make_shared<GuiRectangle>(sf::Vector2f{ 200.f,40.f }, sf::Color::Red));
	guiw.container.addElement(GUI_SPACE(5.f));
	guiw.container.addElement(cRight);

	cRight->addElement(std::make_shared<GuiRectangle>(sf::Vector2f{ 150.f,80.f }, sf::Color::Green));
	cRight->addElement(GUI_SPACE(5.f));
	cRight->addElement(btn);


	guiw.totalTransform.translate({ 200.f,200.f });
	//guiw.totalTransform.rotate(70.f);
	guiw.totalTransform.scale({ 1.3f,1.3f });
	guiw.container.setHorizontal();
	guiw.solveSize();

	//guifull.container.addElement(std::make_shared<GuiRectangle>(sf::Vector2f{ 100.f,50.f }, sf::Color::Cyan));
	//guifull.container.addElement(GUI_SPACE(20.f));
	//guifull.container.addElement(std::make_shared<GuiRectangle>(sf::Vector2f{ 100.f,50.f }, sf::Color::Cyan));
	//guifull.container.setVertical();
	//guifull.container.setPosition({ 150.f,150.f });
	
	//global.guiWindows.push_back(&guifull);
	global.guiWindows.push_back(&guiw);


	bool ClickedOnGui = false;

	sf::Clock deltaClock;
	double delta = 0;


	while (window.isOpen())
	{
#ifdef _DEBUG
		//KeyBreak
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			int i = 1;
#endif

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
			{
				
				//bool hit=false;//changes to true, when the mouse button hits a GuiWindow
				//for (auto w = global.guiWindows.rbegin();w != global.guiWindows.rend(); ++w) 
				//{
				//	auto dw= *w;
				//	if (dw->click(sf::Vector2f{ float(event.mouseButton.x),float(event.mouseButton.y) })) 
				//	{
				//		hit = true;
				//		break;
				//	}
				//}
				//
				//if (!hit)
				//	global.openedMap->onMouseRawStart(event.mouseButton);
				//else
				//	ClickedOnGui = true;
				//break;
				global.clickStack.mousePressed(event.mouseButton);
				break;
			}

			case sf::Event::MouseButtonReleased:
				/*if (ClickedOnGui)
				{
					ClickedOnGui = false;
				}
				else
				{
					global.openedMap->onMouseRawEnd(event.mouseButton);
				}*/

				global.clickStack.mouseReleased(event.mouseButton);
				break;
			case sf::Event::MouseWheelMoved:
				global.openedMap->zoomCamera(event.mouseWheel.delta);
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::U)
					global.openedMap = mdb.getMap(1, svg->getObjects());
				if (event.key.code == sf::Keyboard::Z)
					global.openedMap = mdb.getMap(2, svg->getObjects());

				if (event.key.code == sf::Keyboard::M)//save game
					svg->gatherAndSave(mdb.getLoadedMaps());

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
		//global.openedMap->onMouseTick(sf::Mouse::getPosition(window));
		global.clickStack.mouseTick(sf::Mouse::getPosition(window));

		//Camera move tick
		if (window.hasFocus())
		{
			//tmp joystick
			//openedMap->moveCamera({ sf::Joystick::getAxisPosition(0,sf::Joystick::Axis::X)*0.01f ,sf::Joystick::getAxisPosition(0,sf::Joystick::Axis::Y)*0.01f });


			//move camera by keyboard
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				global.openedMap->moveCamera(Direction::up, delta);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				global.openedMap->moveCamera(Direction::left, delta);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				global.openedMap->moveCamera(Direction::down, delta);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				global.openedMap->moveCamera(Direction::right, delta);
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
		mapRenderTexture.setView(global.openedMap->getMapView());
		mapRenderTexture.clear(sf::Color(0, 0, 0, 255));
		mapRenderTexture.draw(*global.openedMap);
		mapRenderTexture.display();
		mapSprite.setTexture(mapRenderTexture.getTexture());

		//Rendering Window
		window.clear(sf::Color(0, 0, 0, 255));
		window.draw(mapSprite);
		for (auto w : global.guiWindows)
		{
			window.draw(*w);
		}
		window.display();
	}

	delete svg;
	return 0;
}

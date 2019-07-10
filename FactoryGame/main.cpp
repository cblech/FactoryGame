#include "SFML\Graphics.hpp"
#include <thread>

/////////////////////////////////////////////////////////////
class runningClass
{
public:
	runningClass();

	void run();
};

runningClass::runningClass()
{

}

void runningClass::run() {
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

	sf::CircleShape shape(100.f);


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color(0, 0, 0, 255));
		window.draw(shape);
		window.display();
	}

}


/////////////////////////////////////////////////////////////////////////
int main()
{
	std::thread t(&runningClass::run, runningClass());

	t.join();

	return 0;
}
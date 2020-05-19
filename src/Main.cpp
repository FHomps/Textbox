#include "textbox.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "Main window");
	window.setFramerateLimit(60);
	sf::Event haps;

	TextboxGenerator tbg;
	tbg.loadFromFile("resources/testbase.png", 3, 1, 2, 4);
	sf::Sprite box;
	box.setTexture(tbg.getTexture(200,200));
	box.setPosition(100, 100);

	TextboxGenerator aa;
	aa.loadFromFile("resources/aceattorney.png");
	sf::Sprite aabox;
	aabox.setTexture(aa.getTexture(300, 100));
	aabox.setPosition(50, 50);

	while (window.isOpen())
	{
		while (window.pollEvent(haps))
		{
			if (haps.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color(20, 20, 30));
		window.draw(box);
		window.draw(aabox);
		window.display();
	}

	return 0;
}

#pragma once
#include <SFML/Graphics.hpp>

class Fonts{
public:

	sf::Font arial;

	Fonts() {
		arial.loadFromFile("assets/fonts/arialmt.ttf");
	}
};


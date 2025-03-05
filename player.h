#pragma once
#include <string>
#include <objects.h>
#include <terminal.h>

#pragma once
class Player{

	std::string default_name = "@player_name";
	std::string default_className = "@player_class_name";

public:
	std::string name = this->default_name;
	std::string className = this->default_className;
	int hp = 20;
	int dmg = 2;
	bool life = false;

	// Создание игрока
	PlayerObject object;

	// Инициализация игрока
	PlayerObject initialize(std::string name = "@player_name") {
		sysPrint("The player's essence has been created.");
		return object;
	}

	void update() {
		// Управление игроком
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) object.move(0, -1);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) object.move(0, 1);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) object.move(-1, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) object.move(1, 0);
	}
};


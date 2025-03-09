#pragma once
#include <string>
#include <objects.h>
#include <terminal.h>
#include <collision.h>

class Player{

	std::string default_name = "@player_name";
	std::string default_className = "@player_class_name";
	Collision collision;

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

	void update(int mapWidth, int mapHeight, bool log = false) {
		// Управление игроком

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			if (collision.border('W', object.size, object.position, mapWidth, mapHeight)) object.move(0, -1, log);
		} 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			if (collision.border('S', object.size, object.position, mapWidth, mapHeight)) object.move(0, 1, log);
		} 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			if (collision.border('A', object.size, object.position, mapWidth, mapHeight)) object.move(-1, 0, log);
		} 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			if (collision.border('D', object.size, object.position, mapWidth, mapHeight)) object.move(1, 0, log);
		} 
	}
};
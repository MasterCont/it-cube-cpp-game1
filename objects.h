#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <terminal.h>

struct MapObject{
	sf::RectangleShape shape;
	sf::Vector2f position;
	sf::Color color;
};

struct MapSize {
	int width = 200;
	int height = 200;
};

struct GameMap {
	std::string name;
	MapSize size;
	std::vector<MapObject> level;
};

struct PlayerObject {
	sf::RectangleShape shape;
	sf::Vector2f position;
	float speed = 5.0f;
	int size = 32;

	PlayerObject() {
		shape.setSize(sf::Vector2f(size, size)); // Размер игрока
		shape.setFillColor(sf::Color::Blue);
	}

	bool SetPosition(int spawnW, int spawnH) {
		position = sf::Vector2f(spawnW, spawnH); // Стартовая позиция
		shape.setPosition(position);
		return true;
	}

	void move(float dx, float dy, bool log = false) {
		position.x += dx * speed;
		position.y += dy * speed;
		if (log) {
			sysPrintWithoutEndl("Player pos X: ");
			sysPrint(position.x, false);


			sysPrintWithoutEndl("Player pos Y: ");
			sysPrint(position.y, false);
		}
		shape.setPosition(position);
	}
};
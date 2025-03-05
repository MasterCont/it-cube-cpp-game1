#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

struct MapObject{
	sf::Vector2f position;
	sf::Color color;
};

struct GameMap {
	std::string name;
	std::vector<MapObject> level;
};

struct PlayerObject {
	sf::RectangleShape shape;
	sf::Vector2f position;
	float speed = 5.0f;

	PlayerObject() {
		shape.setSize(sf::Vector2f(32, 32)); // Размер игрока
		shape.setFillColor(sf::Color::Blue);
		position = sf::Vector2f(400, 300); // Стартовая позиция
		shape.setPosition(position);
	}

	void move(float dx, float dy) {
		position.x += dx * speed;
		position.y += dy * speed;
		shape.setPosition(position);
	}
};
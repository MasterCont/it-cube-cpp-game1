#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <terminal.h>

struct MapObjectBasicShape{
	sf::RectangleShape shape;
	sf::Vector2f position;
	sf::Color color;
};

struct MapObjectBasicSprite{
	sf::Sprite sprite;
};

struct MapSize {
	int width = 200;
	int height = 200;
};

struct GameMap {

	struct ObjectList {
		std::vector<MapObjectBasicShape> shapes;
		std::vector<MapObjectBasicSprite> sprites;
	};

	std::string name;
	MapSize size;
	ObjectList level;
};

struct PlayerObject {
	sf::RectangleShape shape;
	sf::Vector2f position;
	float speed = 5.0f;
	int size = 32;

	PlayerObject() {
		shape.setSize(sf::Vector2f(size, size)); // ������ ������
		shape.setFillColor(sf::Color::Blue);
	}

	bool SetPosition(int spawnW, int spawnH) {
		position = sf::Vector2f(spawnW, spawnH); // ��������� �������
		shape.setPosition(position);
		return true;
	}

	void move(float dx, float dy, bool log = false) {
		position.x += dx * speed;
		position.y += dy * speed;
		if (log) {
			sysPrintWithoutEndl("Player pos X: ", true);
			sysPrint(position.x, false);

			sysPrintWithoutEndl("Player pos Y: ", true);
			sysPrint(position.y, false);
		}
		shape.setPosition(position);
	}
};

struct DebugPages {
	std::string header;
	std::vector<std::string> list;
};

// ����� �� ���������� ����� ��������� � ���� �� ����������� ������� �����
class ObjectManager {
public:

	// ������ � ������
	MapObjectBasicSprite createSprite(sf::Vector2f position, sf::Color color) {
		MapObjectBasicSprite newObject;
		newObject.sprite.setPosition(position);
		newObject.sprite.setColor(color);
		return newObject;
	}

	// ������ � ���������
	MapObjectBasicSprite createSprite(sf::Vector2f position, sf::Texture& texture) {
		MapObjectBasicSprite newObject;
		newObject.sprite.setPosition(position);
		newObject.sprite.setTexture(texture);
		return newObject;
	}


};
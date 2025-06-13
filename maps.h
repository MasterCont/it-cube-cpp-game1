#pragma once
#include <vector>
#include <objects.h>
#include <common.h>
#include <terminal.h>
#include <string>

class MapManager {
public:

	// ������ ������ ���� ����
	std::vector<GameMap> maps; 


	// ������� ����� �����
	static GameMap create(std::string name = "undefined_map", int width = 200, int height = 200) {

		GameMap map;

		// ����������� ��������� ����
		map.name = name;
		map.size.width = width;
		map.size.height = height;

		// ������������ ��������� ��������� �����
		MapObjectBasicShape border;
		border.shape.setSize(sf::Vector2f(width, height)); // ������ ������
		border.shape.setOutlineThickness(1);
		//sf::Image image;
		//image.loadFromFile("grass.png");
		//sf::Texture* texture = nullptr;
		//// Getting Error here!
		//if (!texture->loadFromImage(image))
		//	throw std::runtime_error("Could not load fighter jet.png");
		//border.shape.setTexture(texture);
		border.shape.setOutlineColor(sf::Color::Red);
		map.level.shapes.push_back(border);

		sysPrint("The map '" + name + "' has been created successfully!");
		return map;
	}

	// ��������� ��� �����
	void loadAllMaps() {
		this->maps.push_back(create("default", game.mapDefaultSize.width, game.mapDefaultSize.height));
		sysPrint("There were "+ std::to_string(maps.size()) + " game locations uploaded.");
	}

	// �������� ������ �������-������� �� �����
	void loadSprite(int mapNumber, MapObjectBasicSprite sprite) {
		maps[mapNumber].level.sprites.push_back(sprite);
	}

};
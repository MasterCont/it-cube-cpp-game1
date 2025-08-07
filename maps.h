#pragma once
#include <vector>
#include <objects.h>
#include <common.h>
#include <terminal.h>
#include <string>

class MapManager {
public:

	// Создаём список всех карт
	std::vector<GameMap> maps; 


	// Создать новую карту
	static GameMap create(std::string name = "undefined_map", int width = 200, int height = 200) {

		GameMap map;

		// Прописываем настройки карт
		map.name = name;
		map.size.width = width;
		map.size.height = height;

		// Отрисовываем доступную местность карты
		MapObjectBasicSprite location;
		location.sprite.setScale(width, height);
		// location.sprite.setSize(sf::Vector2f(width, height)); // Размер игрока
		// location.sprite.setOutlineThickness(1);
		//sf::Image image;
		//image.loadFromFile("grass.png");
		//sf::Texture* texture = nullptr;
		//// Getting Error here!
		//if (!texture->loadFromImage(image))
		//	throw std::runtime_error("Could not load fighter jet.png");
		//border.shape.setTexture(texture);
		// location.sprite.setOutlineColor(sf::Color::Red);
		map.level.sprites.push_back(location);

		sysPrint("The map '" + name + "' has been created successfully!");
		return map;
	}

	// Загрузить все карты
	void loadAllMaps() {
		this->maps.push_back(create("default", game.mapDefaultSize.width, game.mapDefaultSize.height));
		sysPrint("There were "+ std::to_string(maps.size()) + " game locations uploaded.");
	}

	// Загрузка нового объекта-спрайта на карту
	void loadSprite(int mapNumber, MapObjectBasicSprite sprite) {
		sprite.sprite.setColor(sf::Color::Green);
		maps[mapNumber].level.sprites.push_back(sprite);
	}

};
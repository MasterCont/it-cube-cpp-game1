#pragma once
#include <vector>
#include <objects.h>
#include <common.h>
#include <terminal.h>

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

		// Добавляем тестовые объекты на карту
		//for (int i = 0; i < 100; ++i) {
		//	MapObject obj;
		//	obj.position = sf::Vector2f(rand() % game.window.width, rand() % game.window.height);
		//	obj.color = sf::Color(rand() % 255, rand() % 255, rand() % 255); // Случайный цвет
		//	map.level.push_back(obj);
		//}

		// Отрисовываем доступную местность карты
		MapObject border;
		border.shape.setSize(sf::Vector2f(width, height)); // Размер игрока
		border.shape.setOutlineThickness(1);
		border.shape.setOutlineColor(sf::Color::Red);
		map.level.push_back(border);

		sysPrint("The map '" + name + "' has been uploaded successfully!");
		return map;
	}

	// Загрузить все карты
	void loadAllMaps() {
		this->maps.push_back(create("default", game.mapDefaultSize.width, game.mapDefaultSize.height));
	}


};
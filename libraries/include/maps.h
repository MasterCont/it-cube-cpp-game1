#pragma once
#include <vector>
#include <objects.h>
#include <common.h>
#include <terminal.h>

class MapManager {
public:

	// ������ ������ ���� ����
	std::vector<GameMap> maps; 


	// ������� ����� �����
	static GameMap create(std::string name = "undefined_map") {
		GameMap map;
		map.name = name;

		// ��������� �������� ������� �� �����
		for (int i = 0; i < 100; ++i) {
			MapObject obj;
			obj.position = sf::Vector2f(rand() % game.window.width, rand() % game.window.height);
			obj.color = sf::Color(rand() % 255, rand() % 255, rand() % 255); // ��������� ����
			map.level.push_back(obj);
		}

		sysPrint("The map '" + name + "' has been uploaded successfully!");
		return map;
	}

	// ��������� ��� �����
	void loadAllMaps() {
		this->maps.push_back(create("default"));
	}


};
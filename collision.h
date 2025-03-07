#pragma once
#include <SFML/Graphics.hpp>
#include <terminal.h>

class Collision{
public:

	bool border(char keyboard, int playerSize, sf::Vector2f position, int mapWidth, int mapHeight) {

		if (keyboard == 'W' && position.y > 0) return true;
		else if (keyboard == 'S' && position.y < mapHeight - playerSize) return true;
		else if (keyboard == 'A' && position.x > 0) return true;
		else if (keyboard == 'D' && position.x < mapWidth - playerSize) return true;

		// Если игрок не заходит за границы карты
		//if ((position.x > 0 && position.x < mapWidth) && (position.y > 0 && position.y < mapHeight) ) {
		//	return true; // То разрешаем передвижение
		//}

		else {
			return false; // Иначе отправляем запрет на передвижение
		}

	}

};


#pragma once
#include <SFML/Graphics.hpp>
#include <terminal.h>
#include <time.h>

class Clock{
public:

	sf::Clock clock;
	sf::Time previousTime = clock.getElapsedTime();
	sf::Time currentTime;
	std::time_t nowTime = time(0);
	float currentFPS = 0;

	float getFPS() {
		currentTime = clock.getElapsedTime();

		// Обновляем счётчик FPS через каждую секунду
		if (nowTime != time(0)) {
			currentFPS = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds()); // the asSeconds returns a float
			nowTime = time(0);
		}

		previousTime = currentTime;
		return currentFPS;
	}

};


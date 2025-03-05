#pragma once
#include <SFML/Graphics.hpp>
#include <terminal.h>

class Cam{

	sf::View view;
	sf::Vector2f targetCenter;
	float smoothSpeed = 0.1f;

public:

	// Создание камеры
	sf::View initialize(sf::RenderWindow& window) {
		view = sf::View(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
		view.setCenter(window.getSize().x / 2, window.getSize().y / 2);
		sysPrint("The player's camera is initialized.");
		return view;
	}

	// Обновление позиции камеры с плавным следованием
	void update(const sf::Vector2f& newCenter) {
		targetCenter = newCenter;
		sf::Vector2f currentCenter = view.getCenter();
		sf::Vector2f smoothedPosition = currentCenter + (targetCenter - currentCenter) * smoothSpeed;
		view.setCenter(smoothedPosition);
	}

	// Получение объекта камеры
	sf::View& getView() {
		return view;
	}

};


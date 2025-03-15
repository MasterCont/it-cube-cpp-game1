#pragma once
#include <common.h>
#include <terminal.h>
#include <objects.h>
#include <string>
#include <SFML/Graphics.hpp>
#include <fonts.h>
#include <player.h>

class Debug{
	Fonts fonts;
public:

	DebugPages pages[5];


	static void toggle(sf::RenderWindow& window) {
		game.debug.active = game.debug.active ? false : true;
		
		// Обновляем заголовок окна
		if (game.debug.active) window.setTitle(game.name + " | " + game.version + " | " + game.author);
		else window.setTitle(game.name);

		sysPrintWithoutEndl("The developer's debugging mode has been updated to ", true);
		sysPrint(game.debug.active, false);
	}

	void updatePage(int index, std::string header, std::vector<std::string> list) {
		pages[index].header = header;
		pages[index].list = list;
		//sysPrintWithoutEndl("Debugging page #", true);
		//sysPrintWithoutEndl(index);
		//sysPrintWithoutEndl(" has been overwritten. \n");
	}


	void update(Player player, int page) {

		std::vector<std::string> list;

		if (game.debug.active) {
			if (page == 0) {
				list.clear();
				list.push_back("Version: " + game.version);
				list.push_back("Window.Witdh: " + game.window.widthString);
				list.push_back("Window.Height: " + game.window.heightString);
				list.push_back("Map: " + std::to_string(game.map_number));

				updatePage(0, "DEBUG PAGE #0", list);
			}

			else if (page == 1) {
				list.clear();
				list.push_back("Player posX: " + std::to_string(player.object.position.x));
				list.push_back("Player posY: " + std::to_string(player.object.position.y));
				list.push_back("Player HP: " + std::to_string(player.hp));
				list.push_back("Player Life: " + std::to_string(player.life));

				updatePage(1, "DEBUG PAGE #1", list);
			}
		}

		// Очистка памяти при выключении отладки
		else if (list.size() > 0) list.clear();
	}

	sf::Text outputText(std::string value, int posX, int posY) {
		sf::Text text(value, fonts.arial);
		text.setCharacterSize(game.debug.fontSize);
		text.setStyle(sf::Text::Bold);
		text.setFillColor(sf::Color::Red);
		text.setPosition(sf::Vector2f(posX, posY));

		return text;
	}

	void render(sf::RenderWindow& window, int posX, int posY, int index = 0) {

		int intervalH = 0;

		sf::Text text = outputText(pages[index].header, posX, posY + intervalH);
		window.draw(text);
		intervalH += game.debug.fontSize * 1.5;

		for (int i = 0; i < pages[index].list.size(); i++) { // Выводим список с данными страницы отладки
			sf::Text text = outputText(pages[index].list[i], posX, posY + intervalH);
			window.draw(text);
			intervalH += game.debug.fontSize;
		}
		
	}
};


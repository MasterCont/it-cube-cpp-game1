#pragma once
#include <common.h>
#include <terminal.h>
#include <objects.h>
#include <string>
#include <SFML/Graphics.hpp>
#include <fonts.h>
#include <player.h>
#include <clock.h>
#include <maps.h>

class Debug{

	Fonts fonts;
	Clock clock;

public:

	DebugPages pages[game.debug.pages.max + 1]; // +1 нужен, чтобы не крашалась игра при потере памяти

	static void toggle(sf::RenderWindow& window) {
		game.debug.active = game.debug.active ? false : true;

		// Обновляем заголовок окна
		if (game.debug.active) window.setTitle(game.name + " | " + game.version + " | " + game.author);
		else window.setTitle(game.name);

		sysPrintWithoutEndl("The developer's debugging mode has been updated to ", true);
		sysPrint(game.debug.active, false);
	}

	void updatePage(int index, std::string header, std::vector<std::string> list) {
		pages[index].header = header.length() > 0 ? header : "DEBUG PAGE #" + std::to_string(index) + " (The page does not exist)";
		pages[index].list = list;
		//sysPrintWithoutEndl("Debugging page #", true);
		//sysPrintWithoutEndl(index);
		//sysPrintWithoutEndl(" has been overwritten. \n");
	}

	void update(GameMap map, Player player, int page) {

		if (game.debug.active) {

			// Создаём список отладки
			std::vector<std::string> list;

			if (page == 0) {
				list.push_back("Version: " + game.version);
				list.push_back("Window.Witdh: " + game.window.widthString);
				list.push_back("Window.Height: " + game.window.heightString);
				list.push_back("FPS: " + std::to_string(clock.getFPS()));
				list.push_back("Map: " + std::to_string(game.map_number));

				updatePage(0, "Main settings", list);
			}
			
			else if (page == 1) {
				list.push_back("Player posX: " + std::to_string(player.object.position.x));
				list.push_back("Player posY: " + std::to_string(player.object.position.y));
				list.push_back("Player HP: " + std::to_string(player.hp));
				list.push_back("Player Life: " + std::to_string(player.life));

				updatePage(1, "Player Information", list);
			}

			else if (page == 2) {
				
	
				// Отрисовка спрайтов-объектов
				for (int i = 0; i < map.level.sprites.size(); i++) {

					MapObjectBasicSprite object = map.level.sprites[i];
					list.push_back("Sptire #" + std::to_string(i) + ":");
					list.push_back("PosX: " + std::to_string(object.sprite.getPosition().x) + " | PosY: " + std::to_string(object.sprite.getPosition().y));
					list.push_back(" ");

				}

	/*			list.push_back("Player posX: " + std::to_string(player.object.position.x));
				list.push_back("Player posY: " + std::to_string(player.object.position.y));
				list.push_back("Player HP: " + std::to_string(player.hp));
				list.push_back("Player Life: " + std::to_string(player.life));*/

				updatePage(2, "List of all sprites", list);
			}

			else {
				updatePage(page, "", list);
			}

			// Очищаем список отладки
			list.clear();
		}
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

		sf::Text text = outputText(std::to_string(index) + ": " + pages[index].header, posX, posY + intervalH);
		window.draw(text);
		intervalH += game.debug.fontSize * 1.5;

		for (int i = 0; i < pages[index].list.size(); i++) { // Выводим список с данными страницы отладки
			sf::Text text = outputText(pages[index].list[i], posX, posY + intervalH);
			window.draw(text);
			intervalH += game.debug.fontSize;
		}
		
	}
};


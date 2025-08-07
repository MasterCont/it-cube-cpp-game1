#pragma once
#include <SFML/Graphics.hpp>

namespace core {


	
	class GameMenu {

		class SizeWindow {
		public:
			float x; // Координаты меню по X
			float y; // Координаты меню по Y
			int margin; // Расстояние между пунктами меню
		};

		class FontSettings {
		public:
			int size; // Размер шрифта
			sf::Font font; // Шрифт меню
		};

		class MainSettings {
		public:
			int allOfPoints; // Максимальное количество пнуктов меню
			int selected; // Номер текущего пункта меню
		};

		class DecorationSettings {
		public:
			sf::Color menu_text_color = sf::Color::White;    // Цвет пунктов меню
			sf::Color chose_text_color = sf::Color::Yellow;  // Цвет выбора пункта меню
			sf::Color border_color = sf::Color::Black;       // Цвет обводки текста пунктов меню
		};

		// Динамический массив текстовых объектов названий пунктов меню
		sf::Text* mainMenu;

		MainSettings mainSettings;
		SizeWindow sizeWindow;
		FontSettings fontSettings;
		DecorationSettings decorationSettings;


		// Настройка текста пунктов меню
		// Параметры: ссылка на текстовый объект, текст, координаты текста
		void setInitText(sf::Text& text, sf::String str, float xpos, float ypos);
		// Ссылка на графическое окно
		sf::RenderWindow& mywindow;

	public:
		// Конструктор 
		// Параметры: ссылка на графическое окно, координаты игрового меню по x и y
		// количество пунктов меню, массив названий пунктов меню, размер шрифта, шаг между пунктами меню
		GameMenu(sf::RenderWindow& window, float menux, float menuy,
			int index, sf::String name[], int sizeFont = 60, int step = 80);

		~GameMenu(){
			delete[] mainMenu;
		}

		void draw();        // Рисуем меню

		void MoveUp();     // Перемещение выбора меню вверх

		void MoveDown();   // Перемещение выбора меню вниз

		// Цвет элементов игрового меню
		void setColorTextMenu(sf::Color menColor, sf::Color ChoColor,
			sf::Color BordColor);

		void AlignMenu(int posx);   // Выравнивание положения меню


		int getSelectedMenuNumber(){ // Возвращает номер выбранного элемента меню{
			return mainSettings.selected;
		}

	};



}

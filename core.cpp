#include "core.h"

// метод настройки текстовых объектов пунктов игрового меню
void core::GameMenu::setInitText(sf::Text& text, sf::String str, float xpos, float ypos)
{
	text.setFont(fontSettings.font);                 // шрифт
	text.setFillColor(decorationSettings.menu_text_color); // цвет 
	text.setString(str);                // текст
	text.setCharacterSize(fontSettings.size);   // размер шрифта
	text.setPosition(xpos, ypos);       // координаты текстового объекта
	text.setOutlineThickness(3);        // толщина контура обводки текста
	text.setOutlineColor(decorationSettings.border_color); // цвет контура обводки текста
}

// Выравнивание пунктов меню по левому по правому по центру 
void core::GameMenu::AlignMenu(int posx) {
	for (int i = 0; i < mainSettings.allOfPoints; i++) {
		float nullx = 0;
		switch (posx) {
		case 0: // По правому краю
			nullx = mainMenu[i].getLocalBounds().width;
			break;
		case 1: // По левому краю
			nullx = 0;
			break;
		case 2: // По центру
			nullx = mainMenu[i].getLocalBounds().width / 2;
			break;
		}
		// Исправленная позиция:
		mainMenu[i].setPosition(mainMenu[i].getPosition().x - nullx, mainMenu[i].getPosition().y);
	}
}

// Конструктор
core::GameMenu::GameMenu(sf::RenderWindow& window, float menux, float menuy, int index, sf::String name[], int sizeFont, int step)
	: mywindow(window)
{
	this->sizeWindow.x = menux;
	this->sizeWindow.y = menuy;
	this->sizeWindow.margin = step; // Добавьте эту строку!
	this->fontSettings.size = sizeFont;

	// Загрузка шрифта
	if (!fontSettings.font.loadFromFile("assets/fonts/arialmt.ttf"))
		exit(32);

	mainSettings.allOfPoints = index;
	mainMenu = new sf::Text[mainSettings.allOfPoints];

	// Исправленное позиционирование:
	float currentY = menuy;  // Начинаем с позиции menuy
	for (int i = 0; i < mainSettings.allOfPoints; i++) {
		setInitText(mainMenu[i], name[i], sizeWindow.x, currentY);
		currentY += step;  // Увеличиваем позицию Y на шаг
	}

	mainSettings.selected = 0;
	mainMenu[mainSettings.selected].setFillColor(decorationSettings.chose_text_color);
}

// перемещение выбора меню вверх
void core::GameMenu::MoveUp(){
	mainSettings.selected--;
	// подсвечиваем выбранный пункт меню
	if (mainSettings.selected >= 0) {
		mainMenu[mainSettings.selected].setFillColor(decorationSettings.chose_text_color);
		mainMenu[mainSettings.selected + 1].setFillColor(decorationSettings.menu_text_color);
	}
	else
	{
		mainMenu[0].setFillColor(decorationSettings.menu_text_color);
		mainSettings.selected = mainSettings.allOfPoints - 1;
		mainMenu[mainSettings.selected].setFillColor(decorationSettings.chose_text_color);
	}
}

// перемещение выбора меню вниз
void core::GameMenu::MoveDown(){
	mainSettings.selected++;
	// подсвечиваем выбранный пункт меню
	if (mainSettings.selected < mainSettings.allOfPoints) {
		mainMenu[mainSettings.selected - 1].setFillColor(decorationSettings.menu_text_color);
		mainMenu[mainSettings.selected].setFillColor(decorationSettings.chose_text_color);
	}
	else
	{
		mainMenu[mainSettings.allOfPoints - 1].setFillColor(decorationSettings.menu_text_color);
		mainSettings.selected = 0;
		mainMenu[mainSettings.selected].setFillColor(decorationSettings.chose_text_color);
	}
}

// рисуем элементы меню в графическом окне
void core::GameMenu::draw(){
	// перебираем для отрисовки существующие текстовые объекты пунктов меню 	
	for (int i = 0; i < mainSettings.allOfPoints; i++) mywindow.draw(mainMenu[i]);
}

// назначение цвета элементам пунктов меню
void core::GameMenu::setColorTextMenu(sf::Color menColor, sf::Color ChoColor, sf::Color BordColor){
	decorationSettings.menu_text_color = menColor;   // цвет пунктов меню
	decorationSettings.chose_text_color = ChoColor; // цвет выбраного пункта меню
	decorationSettings.border_color = BordColor;    // цвет контура пунктов меню

	for (int i = 0; i < mainSettings.allOfPoints; i++) {
		mainMenu[i].setFillColor(decorationSettings.menu_text_color);
		mainMenu[i].setOutlineColor(decorationSettings.border_color);
	}

	mainMenu[mainSettings.selected].setFillColor(decorationSettings.chose_text_color);
}
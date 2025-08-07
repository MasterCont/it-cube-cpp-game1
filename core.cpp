#include "core.h"

// ����� ��������� ��������� �������� ������� �������� ����
void core::GameMenu::setInitText(sf::Text& text, sf::String str, float xpos, float ypos)
{
	text.setFont(fontSettings.font);                 // �����
	text.setFillColor(decorationSettings.menu_text_color); // ���� 
	text.setString(str);                // �����
	text.setCharacterSize(fontSettings.size);   // ������ ������
	text.setPosition(xpos, ypos);       // ���������� ���������� �������
	text.setOutlineThickness(3);        // ������� ������� ������� ������
	text.setOutlineColor(decorationSettings.border_color); // ���� ������� ������� ������
}

// ������������ ������� ���� �� ������ �� ������� �� ������ 
void core::GameMenu::AlignMenu(int posx) {
	for (int i = 0; i < mainSettings.allOfPoints; i++) {
		float nullx = 0;
		switch (posx) {
		case 0: // �� ������� ����
			nullx = mainMenu[i].getLocalBounds().width;
			break;
		case 1: // �� ������ ����
			nullx = 0;
			break;
		case 2: // �� ������
			nullx = mainMenu[i].getLocalBounds().width / 2;
			break;
		}
		// ������������ �������:
		mainMenu[i].setPosition(mainMenu[i].getPosition().x - nullx, mainMenu[i].getPosition().y);
	}
}

// �����������
core::GameMenu::GameMenu(sf::RenderWindow& window, float menux, float menuy, int index, sf::String name[], int sizeFont, int step)
	: mywindow(window)
{
	this->sizeWindow.x = menux;
	this->sizeWindow.y = menuy;
	this->sizeWindow.margin = step; // �������� ��� ������!
	this->fontSettings.size = sizeFont;

	// �������� ������
	if (!fontSettings.font.loadFromFile("assets/fonts/arialmt.ttf"))
		exit(32);

	mainSettings.allOfPoints = index;
	mainMenu = new sf::Text[mainSettings.allOfPoints];

	// ������������ ����������������:
	float currentY = menuy;  // �������� � ������� menuy
	for (int i = 0; i < mainSettings.allOfPoints; i++) {
		setInitText(mainMenu[i], name[i], sizeWindow.x, currentY);
		currentY += step;  // ����������� ������� Y �� ���
	}

	mainSettings.selected = 0;
	mainMenu[mainSettings.selected].setFillColor(decorationSettings.chose_text_color);
}

// ����������� ������ ���� �����
void core::GameMenu::MoveUp(){
	mainSettings.selected--;
	// ������������ ��������� ����� ����
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

// ����������� ������ ���� ����
void core::GameMenu::MoveDown(){
	mainSettings.selected++;
	// ������������ ��������� ����� ����
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

// ������ �������� ���� � ����������� ����
void core::GameMenu::draw(){
	// ���������� ��� ��������� ������������ ��������� ������� ������� ���� 	
	for (int i = 0; i < mainSettings.allOfPoints; i++) mywindow.draw(mainMenu[i]);
}

// ���������� ����� ��������� ������� ����
void core::GameMenu::setColorTextMenu(sf::Color menColor, sf::Color ChoColor, sf::Color BordColor){
	decorationSettings.menu_text_color = menColor;   // ���� ������� ����
	decorationSettings.chose_text_color = ChoColor; // ���� ��������� ������ ����
	decorationSettings.border_color = BordColor;    // ���� ������� ������� ����

	for (int i = 0; i < mainSettings.allOfPoints; i++) {
		mainMenu[i].setFillColor(decorationSettings.menu_text_color);
		mainMenu[i].setOutlineColor(decorationSettings.border_color);
	}

	mainMenu[mainSettings.selected].setFillColor(decorationSettings.chose_text_color);
}
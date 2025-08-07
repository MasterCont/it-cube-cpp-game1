#pragma once
#include <SFML/Graphics.hpp>

namespace core {


	
	class GameMenu {

		class SizeWindow {
		public:
			float x; // ���������� ���� �� X
			float y; // ���������� ���� �� Y
			int margin; // ���������� ����� �������� ����
		};

		class FontSettings {
		public:
			int size; // ������ ������
			sf::Font font; // ����� ����
		};

		class MainSettings {
		public:
			int allOfPoints; // ������������ ���������� ������� ����
			int selected; // ����� �������� ������ ����
		};

		class DecorationSettings {
		public:
			sf::Color menu_text_color = sf::Color::White;    // ���� ������� ����
			sf::Color chose_text_color = sf::Color::Yellow;  // ���� ������ ������ ����
			sf::Color border_color = sf::Color::Black;       // ���� ������� ������ ������� ����
		};

		// ������������ ������ ��������� �������� �������� ������� ����
		sf::Text* mainMenu;

		MainSettings mainSettings;
		SizeWindow sizeWindow;
		FontSettings fontSettings;
		DecorationSettings decorationSettings;


		// ��������� ������ ������� ����
		// ���������: ������ �� ��������� ������, �����, ���������� ������
		void setInitText(sf::Text& text, sf::String str, float xpos, float ypos);
		// ������ �� ����������� ����
		sf::RenderWindow& mywindow;

	public:
		// ����������� 
		// ���������: ������ �� ����������� ����, ���������� �������� ���� �� x � y
		// ���������� ������� ����, ������ �������� ������� ����, ������ ������, ��� ����� �������� ����
		GameMenu(sf::RenderWindow& window, float menux, float menuy,
			int index, sf::String name[], int sizeFont = 60, int step = 80);

		~GameMenu(){
			delete[] mainMenu;
		}

		void draw();        // ������ ����

		void MoveUp();     // ����������� ������ ���� �����

		void MoveDown();   // ����������� ������ ���� ����

		// ���� ��������� �������� ����
		void setColorTextMenu(sf::Color menColor, sf::Color ChoColor,
			sf::Color BordColor);

		void AlignMenu(int posx);   // ������������ ��������� ����


		int getSelectedMenuNumber(){ // ���������� ����� ���������� �������� ����{
			return mainSettings.selected;
		}

	};



}

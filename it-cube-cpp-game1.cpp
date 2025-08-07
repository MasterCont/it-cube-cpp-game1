#include <iostream>
#include <common.h>
#include <terminal.h>
#include <SFML/Graphics.hpp>
#include <maps.h>
#include <player.h>
#include <cam.h>
#include <debug.h>
#include <fonts.h>
#include <objects.h>
#include <core.h>

// функция настройки текста
void InitText(sf::Text& mtext, float xpos, float ypos, sf::String str, int size_font = 60,
    sf::Color menu_text_color = sf::Color::White, int bord = 0, sf::Color border_color = sf::Color::Black) {

    mtext.setString(str);
    mtext.setCharacterSize(size_font);
    mtext.setPosition(xpos, ypos);
    mtext.setFillColor(menu_text_color);
    mtext.setOutlineThickness(bord);
    mtext.setOutlineColor(border_color);
}

// Функция настройки игры
void Options(sf::RenderWindow& Options){

    sf::RectangleShape background_opt(sf::Vector2f(1920, 1080));
    sf::Texture texture_opt;
    if (!texture_opt.loadFromFile("assets/images/menu/options.jpg")) exit(2);

    background_opt.setTexture(&texture_opt);
    while (Options.isOpen())
    {
        sf::Event event_opt;
        while (Options.pollEvent(event_opt))
        {
            if (event_opt.type == sf::Event::Closed) Options.close();
            if (event_opt.type == sf::Event::KeyPressed)
            {
                if (event_opt.key.code == sf::Keyboard::Escape) return; // Выход в меню
            }
        }
        Options.clear();
        Options.draw(background_opt);
        Options.display();
    }

}

// Функция перехода к игре
void GameStart(sf::RenderWindow& window) {
    // Установка переменных
    game.debug.pages.page = 0;

    // Оповещение о загрузке
    sysPrint("SinglePlayer is running.");

    // Загрузка карт
    MapManager mapManager;
    mapManager.loadAllMaps();

    // Создание игрока
    Player player;
    int spawnWidth = (mapManager.maps[game.map_number].size.width / 2) - (player.object.size / 2);
    int spawnHeight = (mapManager.maps[game.map_number].size.height / 2) - (player.object.size / 2);
    player.object.SetPosition(spawnWidth, spawnHeight); // Спавним игрока в центер карты
    player.initialize();

    // Создание камеры
    Cam cam;
    cam.initialize(window);

    // Создание отладки
    Debug debug;

    // Тест создания спрайта
    ObjectManager objManager;
    MapObjectBasicSprite sprite = objManager.createSprite(sf::Vector2f(20, 20), sf::Color(255, 255, 255, 128));
    mapManager.loadSprite(0, sprite);

    window.setVerticalSyncEnabled(true);

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {

            // События
            if (event.type == sf::Event::Closed) window.close(); // Если игра закрыта
            if (event.type == sf::Event::LostFocus) game.window.focus = false; // Если игру свернули/передвинули на второй план
            if (event.type == sf::Event::GainedFocus) game.window.focus = true; // Если игру развернули/сфокусировали


            // Считываем нажания клавиш
            if (event.type == sf::Event::KeyPressed && game.window.focus) {
                if (event.key.code == sf::Keyboard::Escape) return; // Выход в меню
                if (!game.debug.release && event.key.code == sf::Keyboard::I) Debug::toggle(window); // Вызов отладки
                if (event.key.code == sf::Keyboard::Num0) window.close(); // Закрытие приожения
                if (game.debug.active) {
                    if (event.key.code == sf::Keyboard::L) game.debug.pages.max > game.debug.pages.page ? ++game.debug.pages.page : game.debug.pages.page = 0;
                    else if (event.key.code == sf::Keyboard::K) game.debug.pages.page > 0 ? --game.debug.pages.page : game.debug.pages.page = game.debug.pages.max;
                    if (game.debug.pages.looging && event.key.code == sf::Keyboard::L || event.key.code == sf::Keyboard::K) sysPrint("The debug page is open #" + std::to_string(game.debug.pages.page));
                }
            }


        }

        if (game.window.focus) { // Когда игра не свёрнута/передвинута на второй план

            // Обновление позиции игрока
            player.update(mapManager.maps[0].size.width, mapManager.maps[0].size.height);

            // Обновление камеры
            sf::Vector2f playerPosForCam = sf::Vector2f(player.object.shape.getPosition().x + player.object.size / 2, player.object.shape.getPosition().y + player.object.size / 2);
            cam.update(playerPosForCam);
            window.setView(cam.getView());


            // Отрисовка объектов на карте
            window.clear(sf::Color(30, 30, 30));

            // Объекты карты
            // Отрисовка простых объектов
            for (const auto& obj : mapManager.maps[game.map_number].level.shapes) {
                sf::RectangleShape shape = mapManager.maps[game.map_number].level.shapes[0].shape;
                shape.setPosition(obj.position);
                shape.setFillColor(obj.color);
                window.draw(shape);
            }

            // Отрисовка спрайтов-объектов
            for (int i = 0; i < mapManager.maps[game.map_number].level.sprites.size(); i++) {
                sf::Sprite sprite = mapManager.maps[game.map_number].level.sprites[i].sprite;
                sprite.setScale(20, 20);
                window.draw(sprite);
            }


            // Отрисовка отладки
            if (game.debug.active) debug.update(mapManager.maps[game.map_number], player, game.debug.pages.page);

            // Игрок
            window.draw(player.object.shape);

            // Обновление позиции отрисовки отладки
            int posX = cam.getView().getCenter().x - game.window.width / 2;
            int posY = cam.getView().getCenter().y - game.window.height / 2;
            if (game.debug.active) debug.render(window, posX, posY, game.debug.pages.page);

        }

        // Вывод на экран
        window.display();
    }

}

int main(){

    // Оповещение о загрузке
    sysPrint("The application is running.");

    // Создаём главное окно
    sf::RenderWindow window(sf::VideoMode(game.window.width, game.window.height), game.name, sf::Style::Default);
    window.setFramerateLimit(60);

    // Устанавливаем фон меню
    sf::RectangleShape background(sf::Vector2f(window.getSize().x, window.getSize().y));
    sf::Texture texture_window;
    if (!texture_window.loadFromFile("assets/images/menu/default.jpg")) return 1;
    background.setTexture(&texture_window);

    // Заголовок игры
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/arialmt.ttf")) return 2;
    sf::Text title;
    InitText(title, window.getSize().x / 6, 50, L"IT-CUBE-GAME", 100, sf::Color(237, 147, 0), 3, sf::Color::Black);
    title.setFont(font);

    // Пункты меню
    sf::String name_menu[]{ L"Старт", L"Настройки", L"Выход" };

    // Инициализация меню
    sysPrint("The game menu starts.");
    sysPrint(window.getSize().x);
    core::GameMenu mymenu(window, window.getSize().x / 2, 150, 3, name_menu, 80, 100);
    mymenu.setColorTextMenu(sf::Color(237, 147, 0), sf::Color::Red, sf::Color::Black);
    mymenu.AlignMenu(2); // Выравнивание по центру

    // Главный цикл меню
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Обработка навигации по меню
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    mymenu.MoveUp();
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    mymenu.MoveDown();
                }
                else if (event.key.code == sf::Keyboard::Enter) {
                    // Обработка выбора пункта меню
                    switch (mymenu.getSelectedMenuNumber()) {
                    case 0: // Старт игры
                        GameStart(window);
                        window.setView(window.getDefaultView()); // Сброс камеры
                        break;
                    case 1: // Настройки
                        Options(window);
                        window.setView(window.getDefaultView());
                        break;
                    case 2: // Выход
                        window.close();
                        break;
                    }
                }
                else if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
        }

        // Отрисовка меню
        window.clear();
        window.draw(background);
        window.draw(title);
        mymenu.draw();
        window.display();
    }


    return 0;

}

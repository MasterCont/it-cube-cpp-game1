#include <iostream>
#include <common.h>
#include <terminal.h>
#include <SFML/Graphics.hpp>
#include <maps.h>
#include <player.h>
#include <cam.h>
#include <debug.h>
#include <fonts.h>

int main(){

    // Установка переменных
    game.debug.pages.max = 1;
    game.debug.pages.page = 0;

    // Оповещение о загрузке
    sysPrint("The application is running.");

    // Declare and load a font
    sf::Font font;
    font.loadFromFile("assets/fonts/arialmt.ttf");

    // Загрузка карт
    MapManager mapManager;
    mapManager.loadAllMaps();

    // Создание игрока
    Player player;
    int spawnWidth = (mapManager.maps[game.map_number].size.width / 2) - (player.object.size / 2);
    int spawnHeight = (mapManager.maps[game.map_number].size.height / 2) - (player.object.size / 2);
    player.object.SetPosition(spawnWidth, spawnHeight); // Спавним игрока в центер карты
    player.initialize();
  

    // Создаём окно игры с размерами из настроек
    sf::RenderWindow window(sf::VideoMode(game.window.width, game.window.height), game.name, sf::Style::Default);

    // Создание камеры
    Cam cam;
    cam.initialize(window);


    window.setVerticalSyncEnabled(true);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();



            // Считываем нажания клавиш
            if (event.type == sf::Event::KeyPressed) {

                if (!Terminal::release) { // Если программа запущена в режиме debug
                    if (event.key.code == sf::Keyboard::I) Debug::toggle(window); // Вызов отладки
                }

                if (event.key.code == sf::Keyboard::Num0) window.close(); // Закрытие приожения
                if (game.debug.active) {
                    if (event.key.code == sf::Keyboard::L) game.debug.pages.max > game.debug.pages.page ? ++game.debug.pages.page : game.debug.pages.page = 0;
                    else if (event.key.code == sf::Keyboard::K) game.debug.pages.page > 0 ? --game.debug.pages.page : game.debug.pages.page = game.debug.pages.max;
                }
            }


        }



        // Обновление позиции игрока
        player.update(mapManager.maps[0].size.width, mapManager.maps[0].size.height);

        // Обновление камеры
        cam.update(player.object.shape.getPosition());
        window.setView(cam.getView());


        // Отрисовка объектов на карте
        window.clear(sf::Color(30, 30, 30));

        // Объекты карты
        for (const auto& obj : mapManager.maps[game.map_number].level) {
            sf::RectangleShape shape = mapManager.maps[game.map_number].level[0].shape;
            shape.setPosition(obj.position);
            shape.setFillColor(obj.color);
            window.draw(shape);
        }

        // Отрисовка отладки
        Debug debug;
        debug.update(player, game.debug.pages.page);

        // Игрок
        window.draw(player.object.shape);

        int posX = cam.getView().getCenter().x - game.window.width / 2;
        int posY = cam.getView().getCenter().y - game.window.height / 2;
        if (game.debug.active) debug.render(window, posX, posY, game.debug.pages.page);


        window.display();
    }
    return 0;
}

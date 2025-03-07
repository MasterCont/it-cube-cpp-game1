#include <iostream>
#include <common.h>
#include <terminal.h>
#include <SFML/Graphics.hpp>
#include <maps.h>
#include <player.h>
#include <cam.h>

int main(){
    
    // Оповещение о загрузке
    sysPrint("The application is running.");

    // Загрузка карт
    MapManager mapManager;
    mapManager.loadAllMaps();

    // Создание игрока
    Player player;
    int spawnWidth = (mapManager.maps[0].size.width / 2) - (player.object.size / 2);
    int spawnHeight = (mapManager.maps[0].size.height / 2) - (player.object.size / 2);
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
        }

        // Обновление позиции игрока
        player.update(mapManager.maps[0].size.width, mapManager.maps[0].size.height, true);

        // Обновление камеры
        cam.update(player.object.shape.getPosition());
        window.setView(cam.getView());


        // Отрисовка объектов на карте
        window.clear(sf::Color(30, 30, 30));

        // Объекты карты
        for (const auto& obj : mapManager.maps[0].level) {
            sf::RectangleShape shape = mapManager.maps[0].level[0].shape;
            shape.setPosition(obj.position);
            shape.setFillColor(obj.color);
            window.draw(shape);
        }

        // Игрок
        window.draw(player.object.shape);
        window.display();
    }
    return 0;
}

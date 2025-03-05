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
        player.update();

        // Обновление камеры
        cam.update(player.object.shape.getPosition());
        window.setView(cam.getView());


        // Отрисовка объектов на карте
        window.clear(sf::Color(30, 30, 30));

        // Объекты карты
        for (const auto& obj : mapManager.maps[0].level) {
            sf::CircleShape shape(8);
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

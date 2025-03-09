#pragma once
#include <chrono>
#include <ctime>
#include <iostream>

class Terminal{
public:
#if defined(DEBUG) || defined(_DEBUG) 
    static const bool release = 0;
#else
    static const bool release = 1;
#endif
};
    

// Метод для вывода информации в консоль
template<typename Any>
void sysPrint(Any value, bool time = true) {

    if (!Terminal::release) { // Если debug режим
        if (time) {
            // Получаем текущее время
            auto now = std::chrono::system_clock::now();
            std::time_t now_time = std::chrono::system_clock::to_time_t(now);

            // Используем localtime_s вместо localtime
            std::tm local_time;
            localtime_s(&local_time, &now_time);

            // Форматируем дату и время
            char date_buffer[11], time_buffer[9];
            std::strftime(date_buffer, sizeof(date_buffer), "%d.%m.%Y", &local_time);
            std::strftime(time_buffer, sizeof(time_buffer), "%H:%M:%S", &local_time);

            // Выводим в консоль
            std::cout << "[" << date_buffer << "] [" << time_buffer << "] [System] " << value << std::endl;
        }

        // Выводим в консоль
        else std::cout << value << std::endl;
    }
}

template<typename Any>
void sysPrintWithoutEndl(Any value, bool time = false) {

    if (!Terminal::release) { // Если debug режим
        if (time) {
            // Получаем текущее время
            auto now = std::chrono::system_clock::now();
            std::time_t now_time = std::chrono::system_clock::to_time_t(now);

            // Используем localtime_s вместо localtime
            std::tm local_time;
            localtime_s(&local_time, &now_time);

            // Форматируем дату и время
            char date_buffer[11], time_buffer[9];
            std::strftime(date_buffer, sizeof(date_buffer), "%d.%m.%Y", &local_time);
            std::strftime(time_buffer, sizeof(time_buffer), "%H:%M:%S", &local_time);

            // Выводим в консоль
            std::cout << "[" << date_buffer << "] [" << time_buffer << "] [System] " << value;
        }

        else std::cout << value;
    }
    
}
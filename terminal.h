#pragma once
#include <string>
#include <chrono>
#include <ctime>
#include <iostream>

class terminal
{
};

// ����� ��� ������ ���������� � �������
template<typename Any>
void sysPrint(Any value, bool time = true) {

    // �������� ������� �����
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);

    // ���������� localtime_s ������ localtime
    std::tm local_time;
    localtime_s(&local_time, &now_time);

    // ����������� ���� � �����
    char date_buffer[11], time_buffer[9];
    std::strftime(date_buffer, sizeof(date_buffer), "%d.%m.%Y", &local_time);
    std::strftime(time_buffer, sizeof(time_buffer), "%H:%M:%S", &local_time);

    // ������� � �������
    if (time) std::cout << "[" << date_buffer << "] [" << time_buffer << "] [System] " << value << std::endl;
    else std::cout << value << std::endl;
}

template<typename Any>
void sysPrintWithoutEndl(Any value) {

    // �������� ������� �����
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);

    // ���������� localtime_s ������ localtime
    std::tm local_time;
    localtime_s(&local_time, &now_time);

    // ����������� ���� � �����
    char date_buffer[11], time_buffer[9];
    std::strftime(date_buffer, sizeof(date_buffer), "%d.%m.%Y", &local_time);
    std::strftime(time_buffer, sizeof(time_buffer), "%H:%M:%S", &local_time);

    // ������� � �������
    std::cout << "[" << date_buffer << "] [" << time_buffer << "] [System] " << value;
}
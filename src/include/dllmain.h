#ifndef MYLIBRARY_H
#define MYLIBRARY_H

#ifdef __cplusplus

#include <iostream>
#include <fstream>
#include <cstdlib> 
#include <cstring>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>
#include <ctime>
#include <queue>

class Journal
{
private:
    std::string PathFile = "./Journals/";
    std::string FileName = "";
    std::string PriorityLevel = "Low";
public:
    Journal(std::string filename, std::string priority);
    // Записывает сообщение в журнал с важностью и временем 
    // [priority] [dd.mm.yyyy | hh.mm.ss] - msg
    //void Write(std::string priority, std::string time, std::string message);
    void Write(std::string FileName, std::string priority, std::string time, std::string message);
    // Проверяет корректность формата важности для сообщений
    bool SetPriority(std::string priority);
    // Возвращает локальное время в отформатированном виде
    static std::string GetTime();
    // Возвращает true если приоритет выше или равен
    bool Check_Priority(std::string priority);
    // Возвращает приоритет в отформатированном виде
    std::string GetPriority();
    // Устанавливает имя файла
    bool SetFileName(std::string filename);
    // Возвращает текущий журнал для редактирования
    std::string GetFileName();
    // Возвращает путь до папки с журналами
    std::string GetPathToFile();
};
#endif

#endif // MYLIBRARY_H

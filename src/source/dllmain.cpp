#include "../include/dllmain.h"



Journal::Journal(std::string filename, std::string priority)
{
    if (filename.length() > 255)
        throw std::invalid_argument("Имя файла с расширением не может превышать 255 символов!");
    if (filename.empty() || filename == ".txt")
        throw std::invalid_argument("Имя файла не может быть пустым!");
    if (!SetPriority(priority))
        throw std::invalid_argument("Ошибка в формате важности! Допустимые значения: {High, Medium, Low}.");
    this->FileName = filename;
}

std::mutex dll_mx;
// Записывает сообщение в журнал с важностью и временем 
// [priority] [dd.mm.yyyy | hh.mm.ss] - msg
void Journal::Write(std::string FileName, std::string priority, std::string time, std::string message)
{
    if (Check_Priority(priority))
        return;

    {
        std::lock_guard<std::mutex> lock(dll_mx);

        std::ofstream file(FileName, std::ios::app);

        if (file.is_open())
        {
            file << priority << ' ' << time << " - " << message << std::endl;
            file.close();
        }
        else
        {
            std::cerr << "Ошибка: Не удалось открыть файл. Имя файла:" << FileName << "\b" << message << std::endl;
        }
    }
}

// Возвращает время в отформатированном виде
std::string Journal::GetTime()
{
    auto future = std::chrono::system_clock::now();
    time_t t_future = std::chrono::system_clock::to_time_t(future);
    struct tm* ptm_future = std::localtime(&t_future);
    char future_str[23];
    strftime(future_str, sizeof(future_str), "[%d.%m.%Y-%H.%M.%S", ptm_future);
    strcat(future_str, "]");
    return future_str;
}

// Проверяет корректность формата важности для сообщений
bool Journal::SetPriority(std::string priority)
{
    if (priority == "High")
    {
        this->PriorityLevel = "High";
        return true;
    }
    else if (priority == "Medium")
    {
        this->PriorityLevel = "Medium";
        return true;
    }
    else if (priority == "Low")
    {
        this->PriorityLevel = "Low";
        return true;
    }
    else
        return false;
    return false;
}

// Возвращает true если приоритет выше или равен
bool Journal::Check_Priority(std::string priority)
{
    if (priority == "High")
    {
        return false;
    }
    else if (priority == "Medium")
    {
        if (this->PriorityLevel == "High")
            return false;
    }
    else if (priority == "Low")
    {
        if (this->PriorityLevel == "Medium" || this->PriorityLevel == "High")
            return false;
    }
    else
        return true;
    return false;
}

// Возвращает приоритет в отформатированном виде
std::string Journal::GetPriority()
{
    return ('[' + this->PriorityLevel + ']');
}

bool Journal::SetFileName(std::string filename)
{
    if (filename.size() > 255)
    {
        return false;
    }
    else if (filename.empty() || filename == ".txt")
    {

        return false;
    }
    else
    {
        this->FileName = filename;
        return true;
    }
    return false;
}

std::string Journal::GetFileName()
{
    return this->FileName;
}

std::string Journal::GetPathToFile()
{
    return this->PathFile;
}

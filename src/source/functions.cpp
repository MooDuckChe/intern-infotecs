#include "../include/functions.h"

#define File_Exstension ".txt"
// Выводит все файлы типа .txt в директории
std::vector<std::string> Func::OutExistFiles(const std::string& directory)
{
    try
    {
        std::vector<std::string> files;
        for (const auto& entry : std::filesystem::directory_iterator(directory))
        {
            if (entry.is_regular_file() && entry.path().extension() == File_Exstension)
            {
                files.push_back(entry.path().filename().string());
            }
        }
        std::sort(files.begin(), files.end());
        
        return files;
    }
    catch (const std::filesystem::filesystem_error& e)
    {
        std::system("mkdir Journals");
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }
    return {};
}

// Коректно обрабатывает ввод пользователя числа, исключая ошибки от неправильного ввода
int Func::Returnint()
{
    do
    {
        if (int input; std::cin >> input)
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return input;
        }
        
        else
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очиста буфера ввода так как cin сохраняет в себе символ '\n' и из-за этого не даёт вводить заново
            std::cerr << "Ошибка. Неправильный ввод!\n";
        }
    } while (true);
}

// Выводит меню если файл с указанным именем уже существует
bool Func::Filename_Exist(std::string path_to_filename, bool exist)
{
    do
    {
        std::system("clear");
        if (exist) std::cout << "\nФайл с таким именем уже существует!\n";
        std::cout << "1) Перезаписать файл\n";
        std::cout << "2) Добавить данные в конец файла\n";
        std::cout << "3) Создать с другим именем\n";
        std::cout << "Введите номер(1-3): ";
        switch (Func::Returnint())
        {
        case 1:
        {
            std::ofstream file(path_to_filename, std::ios::trunc);
            file.close();
            if (file.fail())
            {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                std::cerr << "Ошибка. Не удалось открыть файл!\n";
                return false;
            }
            
            else
            {
                std::cout << "Успешно перезаписан\n";
                return true;
            }
        }
        case 2:
        {
            return true;
        }
        case 3:
        {
            return false;
        }
        default:
        {
            continue;
        }
        }
    } while (true);
    return false;
}

// Выводит меню выбора журнала для редактирования
std::string Func::ChooseJournal()
{

    do
    {
        std::system("clear");
        std::cout << "\n[0] Создать новый файл\n";
        std::cout << "[1] Показать существующие журналы\n";
        switch (Func::Returnint())
        {
        case 0:
        {
            do
            {
                std::cout << "Введите имя журнала: ";
                std::string filename = "";
                std::getline(std::cin, filename);
                
                if (filename == "")
                {
                    continue;
                }
                
                std::string filename_path = "./Journals/" + filename + ".txt";
                filename += ".txt";

                if (filename.length() <= 255)
                {
                    std::ofstream file(filename_path, std::ios::in);
                    if (file)
                    {
                        if (Filename_Exist(filename_path))
                        {
                            return filename;
                        }
                        
                        else
                        {
                            continue;
                        }
                    }
                    else
                    {
                        std::ofstream file(filename_path, std::ios::out);
                        file.close();
                        if (file.fail())
                        {
                            std::cerr << "Ошбика! Не удалось создать файл с таким именем.\n";
                            std::this_thread::sleep_for(std::chrono::milliseconds(1500));
                            continue;
                        }
                        std::cout << "Файл успешно создан!\n";
                        return filename;
                    }
                }
                else
                {
                    std::cerr << "Название файла не должно превышать 251 символ!\n";
                }
            } while (true);
            
            break;
        }
        
        case 1:
        {
            std::system("clear");
            std::cout << "[0] Выход.\n" << std::endl;
            
            std::vector<std::string> filess = OutExistFiles("./Journals");
            if (filess.empty())
            {
                std::cout << "Созданных ранее журналов нет!\n";
                break;
            }
            for (int i = 0; i < (filess.size() > 20 ? 20 : filess.size()); i++)
            {
                std::cout << "[" << i + 1 << "] " << filess[i] << std::endl;;
            }
            int userInput = Func::Returnint() - 1;
            
            
            if (userInput <= -1)
            {
                break;
            }
            
            if (Filename_Exist(("./Journals/" + filess[userInput]),false))
            {
                return filess[userInput];
            }
            else 
            {
                continue;
            }
            
            return filess[userInput];
            
            break;
        }
        default:
        {
            return "";
        }
        }
    } while (true);
    
    return "fail";
}

// Спрашивает у пользователя важность сообщений и возвращает
std::string Func::GetPriority(bool allow_empty)
{
    do
    {
        std::system("clear");
        std::string text;
        std::cout << "Введите уровень важности сообщения (High/Medium/Low): ";
        std::getline(std::cin, text);
        if (text.empty() && allow_empty)
        {
            return "";
        }
        else if (text.empty())
        {
            continue;
        }
        
        switch (text[0])
        {
        case 72:
        case 104:
        {
            return "High";
        }
        case 77:
        case 109:
        {
            return "Medium";
        }
        case 76:
        case 108:
        {
            return "Low";
        }
        default:
        {
            std::cerr << "Уровень важности может быть только High/Medium/Low\n";
            continue;
        }
        }
    } while (true);   
}

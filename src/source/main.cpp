#include "../include/include.h"

Journal journal(Func::ChooseJournal(), Func::GetPriority(false));

std::queue<std::vector<std::string>> write_task, sorted_write_task;
std::condition_variable ring, write_ring;
std::mutex mtx, mtt, mts, mx, write_mx;

bool stop = false;
int UsedLine = 0;
int Line = 0;

// Функция для получения вектора из очереди
std::vector<std::string> Get_Vec()
{
    {
        std::lock_guard<std::mutex> lock(mts);
        if (!write_task.empty())
        {
            std::vector<std::string> data = write_task.front();
            write_task.pop();
            
            return data;
        }
        return {};
    }
}
void TerribleSort()
{
    std::unique_lock<std::mutex> ulk(mtx);
    while (true)
    {
        ring.wait(ulk, [] { 
            return !write_task.empty() || stop;
        });
        
        if (stop && write_task.empty())
        {
            break;
        }
        std::vector<std::string> data;
        {
            std::lock_guard<std::mutex> lock(mx);
            
            bool flag = false;
            data = Get_Vec();
            
            if (data.empty())
            {
                continue;
            }
            
            for (int i = 0; i < write_task.size()+1; i++)
            {
                if (UsedLine == std::stoi(data[4]))
                {
                    sorted_write_task.push({ data[0], data[1], data[2], data[3] });
                    write_ring.notify_all();
                    flag = true;
                    break;
                }
            }
            if (!flag)
            {
                write_task.push(data);
            }
            else
            {
                UsedLine++;
            }
        }
    }
}

void threadWriteToFile()
{
    std::unique_lock<std::mutex> write_lock(write_mx);
    
    while (true)
    {
        write_ring.wait(write_lock, [] () {
            return !sorted_write_task.empty() || stop;
        });
        
        if (stop && sorted_write_task.empty())
        {
            break;
        }
        std::cout << "write" << std::endl;
        std::vector<std::string> data = sorted_write_task.front();
        journal.Write(data[0], data[1], data[2], data[3]);
        sorted_write_task.pop();
    }
}

int main()
{
    std::thread TerbleSort(TerribleSort);
    std::thread writerThread(threadWriteToFile);
    do
    {
        std::system("clear");
        std::cout << "Файл: [ " << journal.GetFileName() << " ] | Уровень сообщений: " << journal.GetPriority() << "\n\n"; 
        std::cout << "1) Выбрать журнал." << std::endl;
        std::cout << "2) Установить уровень важности." << std::endl;
        std::cout << "3) Внести запись в журнал.\n" << std::endl;
        std::cout << "0) Выход.\n" << std::endl;
        std::cout << "Выберите пункт(1-3): ";

        switch (Func::Returnint())
        {
            // Выбрать журнал
        case 1:
        {
            std::cout << "\n\nТекущий журнал: " << journal.GetFileName() << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1500));
            
            if (journal.SetFileName(Func::ChooseJournal()))
            {
                std::cout << "Журнал успешно обновлён!\n";
            }
            else
            {
                std::cerr << "Ошибка! Не удалось изменить журнал.";
            }
            
            std::this_thread::sleep_for(std::chrono::seconds(2));
            
            break;
        }
        // Установить уровень важности.
        case 2:
        {
            std::system("clear");
            std::cout << "\n\nТекущий уровень важности: " << journal.GetPriority() << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
            std::string priority = Func::GetPriority(true);
            
            if (priority.empty())
            {
                std::cout << "Уровень не изменён!\n";
            }
            
            else if (journal.SetPriority(priority))
            {
                std::cout << "Важность сообщений обновлена!\n";
            }
            
            else
            {
                std::cerr << "Ошибка! Важность сообщений не удалось обновить.\n";
            }
            
            std::this_thread::sleep_for(std::chrono::seconds(2));
            
            break;
        }
        // Внести запись в журнал.
        case 3:
        {
            do
            {
                std::string pathToFile = journal.GetPathToFile() + journal.GetFileName();
                std::string priority = "[" + Func::GetPriority(true) + "]";
                std::cout << "[ Для выхода нажмите Enter ] Введите сообщение: ";
                std::string input;
                std::getline(std::cin, input);
                if (input == "")
                {
                    break;
                }
                std::cout << "112\n";
                
                std::string time = Journal::GetTime();
                {
                    std::lock_guard<std::mutex> lock(mtt);
                    write_task.push({ pathToFile, priority, time, input, std::to_string(Line) });
                    Line += 1;
                }
                ring.notify_all();
            } while (true);
            continue;
      }
      case 0:
      {
          stop = true;
          ring.notify_all();
          TerbleSort.join();
          write_ring.notify_all();
          writerThread.join();
            
          std::cout << "Close Completed\n";
          std::this_thread::sleep_for(std::chrono::seconds(2));
          return 0;
      }
      default:
      {
          continue;
      }
      }
    } while (true);
    
    return 0;
}

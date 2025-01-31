#pragma once
#include "include.h"

class Func
{
private:
    int SelectedMainMenu = 1;
public:

    // Âûâîäèò âñå ôàéëû òèïà .txt â äèðåêòîðèè
    static std::vector<std::string> OutExistFiles(const std::string& directory);

    // Êîðåêòíî îáðàáàòûâàåò ââîä ïîëüçîâàòåëÿ ÷èñëà, èñêëþ÷àÿ îøèáêè îò íåïðàâèëüíîãî ââîäà
    static int Returnint();

    // Âûâîäèò ìåíþ åñëè ôàéë ñ óêàçàííûì èìåíåì óæå ñóùåñòâóåò
    static bool Filename_Exist(std::string filename);

    // Âûâîäèò ìåíþ âûáîðà æóðíàëà äëÿ ðåäàêòèðîâàíèÿ
    static std::string ChooseJournal();

    // Ñïðàøèâàåò ó ïîëüçîâàòåëÿ âàæíîñòü ñîîáùåíèé è âîçâðàùàåò
    static std::string GetPriority(bool allow_empty);
};


/*
void Func::InitDll()
{
    do
    {
        std::cout << "Ââåäèòå èìÿ æóðíàëà: ";
        std::string filename = "";
        std::getline(std::cin, filename);
        if (filename == "")
            continue;

        filename += ".txt";
        if (filename.length() <= 255)
        {
            std::ofstream file(filename, std::ios::in);
            if (file)
            {
                std::cout << "Ôàéë ñ òàêèì èìåíåì óæå ñóùåñòâóåò!\n";
                std::cout << "1) Ïåðåçàïèñàòü ôàéë\n";
                std::cout << "2) Äîáàâèòü äàííûå â êîíåö ôàéëà\n";
                std::cout << "3) Ñîçäàòü ñ äðóãèì èìåíåì\n";
                int userInput;
                std::cout << "Ââåäèòå íîìåð(1-3): ";
                if (!(std::cin >> userInput))
                {
                    std::cin.clear();
                }
                //std::getline(std::cin, userInput);
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                switch (userInput)
                {

                case 1:
                {
                    this->FileName = filename;
                    std::ofstream file(this->FileName, std::ios::trunc);
                    file.close();
                    break;
                }
                case 2:
                {
                    this->FileName = filename;
                    std::ofstream file(this->FileName, std::ios::app);
                    if (file.is_open())
                    {
                        file << GetPriority() << ' ' << GetTime() << " - " << "text" << std::endl;
                        file.close();
                    }
                    else
                    {
                        std::cerr << "Îøèáêà: Íå óäàëîñü îòêðûòü ôàéë. Èìÿ ôàéëà:" << this->FileName << std::endl;
                    }
                    break;
                }
                case 3:
                {
                    continue;
                }
                }
            }
            else
            {
                file.open(filename);
                if (file.is_open())
                {
                    this->FileName = filename;
                    std::cout << "Óñïåøíî!\n";
                    file.close();
                    break;
                }
                else {
                    std::cout << "Íå óäàëîñü îòêðûòü ôàéë!\n";
                }
            }
        }
        else
            std::cerr << "Íàçâàíèå ôàéëà íå äîëæíî ïðåâûøàòü 251 ñèìâîë!\n";
    } while (true);
}
*/

/*
do
{
    int switch_on;
    std::cin >> switch_on;

    switch (switch_on)
    {
    case 1:
    {
        // smth
    }
    case 2:
    {
        // smth
    }
    case 3:
    {
        // smth
        break; // need x2
    }
    default:
        break;
    }
} while (true);
*/

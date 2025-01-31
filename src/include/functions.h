#pragma once
#include "include.h"

class Func
{
public:

    // Âûâîäèò âñå ôàéëû òèïà .txt â äèðåêòîðèè
    static std::vector<std::string> OutExistFiles(const std::string& directory);

    // Êîðåêòíî îáðàáàòûâàåò ââîä ïîëüçîâàòåëÿ ÷èñëà, èñêëþ÷àÿ îøèáêè îò íåïðàâèëüíîãî ââîäà
    static int Returnint();

    // Âûâîäèò ìåíþ åñëè ôàéë ñ óêàçàííûì èìåíåì óæå ñóùåñòâóåò
    static bool Filename_Exist(std::string filename, bool exist = true);

    // Âûâîäèò ìåíþ âûáîðà æóðíàëà äëÿ ðåäàêòèðîâàíèÿ
    static std::string ChooseJournal();

    // Ñïðàøèâàåò ó ïîëüçîâàòåëÿ âàæíîñòü ñîîáùåíèé è âîçâðàùàåò
    static std::string GetPriority(bool allow_empty);
};

#ifndef TEAM_H
#define TEAM_H
#include "Hero.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Team
{
    private:
        string name;
        vector<Hero*> heroes;
        int energy;

    public:
        Team(const string& teamName, int energy);
        void addHero(Hero* hero);
        void setEnergy(int a);
        int getEnergy();
        bool useEnergy(int amount);
        bool isAliveTeam() const;
        int AliveCount();
        Hero* getHero(int index);
        void showTeam();
        void updateAllCounters();
        void updateAllBuffs();
        void updateAllHotEffects();
        void updateAllShileds();
};
#endif
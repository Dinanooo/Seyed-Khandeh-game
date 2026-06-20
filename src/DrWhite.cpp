#include "Drwhite.h"
#include <cstdlib>
#include <ctime>

const int DoctorWhite::ASPIRIN_ENERGY = 3;
const int DoctorWhite::DOPING_ENERGY = 4;
const int DoctorWhite::SPECIAL_ENERGY = 4;
const int DoctorWhite::REVIVE_UP = 200;

DoctorWhite::DoctorWhite() : Hero("Dr.White" , 550, 4)
{
    ragePhrase = "put him on the table... he'll survive if he is lucky!";
}

DoctorWhite::~DoctorWhite()
{
}

int DoctorWhite::getAbility1Energy() const
{
    return 3;
}

int DoctorWhite::getAbility2Energy() const
{
    return 4;
}

int DoctorWhite::getSpeacialAbilityEnergy() const
{
    return 4;
}

string DoctorWhite::getAbility1Name()
{
    return "Aspirin";
}

string DoctorWhite::getAbility2Name()
{
    return "Doping";
}

string DoctorWhite::getSpecialAbilityName()
{
    return "Surgical operation";
}

void DoctorWhite::useAbility1(class Team& myteam, class Team& enemyteam)
{
    if(myteam.getEnergy() < ASPIRIN_ENERGY)
    {
        cout << "not enough energy for aspirin!" << endl;
        return;
    }
    vector<Hero*> aliveAllies;
    for(int i=0 ; i<3 ; i++)
    {
        Hero* hero = myteam.getHero(i);
        if(hero != nullptr && hero != this && hero->isAlive())
        {
            aliveAllies.push_back(hero);
        }
    }
    if(aliveAllies.empty())
    {
        cout << "no alive ally to heal!" << endl;
        return;
    }
    srand(time(0));
    int randomAlly = rand() % aliveAllies.size();
    Hero* targetAlly = aliveAllies[randomAlly];

    myteam.useEnergy(ASPIRIN_ENERGY);
    targetAlly->Heal(40);
    cout << "Dr.white healed " << targetAlly->getName() << " 40 HP." << endl;
    
    vector<Hero*> aliveEnemies;
    for(int i=0 ; i<3 ; i++)
    {
        Hero* enemy = enemyteam.getHero(i);
        if(enemy != nullptr && enemy->isAlive())
        {
            aliveEnemies.push_back(enemy);
        }
    }
    if(aliveEnemies.empty())
    {
        cout << "no alive enemy to attack!" << endl;
        return;
    }
    srand(time(0));
    int randomEnemy = rand() % aliveEnemies.size();
    Hero* targetEnemy = aliveEnemies[randomEnemy];
    targetEnemy->takeDamage(40);
    cout << "Dr.white attacked " << targetEnemy->getName() << " 40 HP!" << endl;
}

void DoctorWhite::useAbility2(class Team& myteam, class Team& enemyteam)
{
    if(myteam.getEnergy() < DOPING_ENERGY)
    {
        cout << "not enough energy for doping!" << endl;
        return;
    }
    vector<Hero*> aliveAllies;
    for(int i=0 ; i<3 ; i++)
    {
        Hero* hero = myteam.getHero(i);
        if(hero != nullptr && hero != this && hero->isAlive())
        {
            aliveAllies.push_back(hero);
        }
    }
    srand(time(0));
    int randomAlly = rand() % aliveAllies.size();
    Hero* targetAlly = aliveAllies[randomAlly];

    myteam.useEnergy(DOPING_ENERGY);
    targetAlly->AddDamageBuff(20, 2);
    cout << "Dr.White used doping on " << targetAlly->getName() << endl;
}

void DoctorWhite::useSpecialAbility(class Team& myteam, class Team& enemyteam)
{
    if(counter > 0)
    {
        cout << "you can't use special ability!" << endl;
        return;
    }
    else if(myteam.getEnergy() < SPECIAL_ENERGY)
    {
        cout << "not enough energy for special ability!" << endl;
        return;
    }
    vector<Hero*> deadAllies;
    for(int i=0 ; i<3 ; i++)
    {
        Hero* hero = myteam.getHero(i);
        if(hero != nullptr && hero != this && !hero->isAlive())
        {
            deadAllies.push_back(hero);
        }
    }
    srand(time(0));
    int randomAlly = rand() % deadAllies.size();
    Hero* deadHero = deadAllies[randomAlly];

    myteam.useEnergy(SPECIAL_ENERGY);
    performRage();
    deadHero->Revive(REVIVE_UP);
    cout << deadHero->getName() << " has been revived all negative effects are removed!" << endl;
    counter = CountSpecialAbi;
}

void DoctorWhite::PrintInfo() const
{
    cout << endl;
    cout << "Hero: Dr.White(Healer)" << endl;
    cout << "HP: " << HP << "/" << MaxHealth << (isAlive() ? "[Alive]" : "[Dead]") << endl;
    cout << "Special ability cooldown: " << counter << "/" << CountSpecialAbi << endl;
    cout << endl;
}
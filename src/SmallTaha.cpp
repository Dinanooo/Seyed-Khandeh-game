#include "SmallTaha.h"
#include <ctime>
#include <cstdlib>
#include <climits>

const int SmallTaha::RAZOR_ENERGY = 2;
const int SmallTaha::SERUM_ENERGY = 4;
const int SmallTaha::SPECIAL_ENERGY = 4;
const int SmallTaha::SPECIAL_HEAL_AMOUNT = 200;

SmallTaha::SmallTaha() : Hero("Small Taha", 500, 3)
{
    ragePhrase = "Everyone stay in your place! this area is polluted.";
}
SmallTaha::~SmallTaha()
{
}

int SmallTaha::getAbility1Energy() const
{
    return 2;
}

int SmallTaha::getAbility2Energy() const
{
    return 4;
}

int SmallTaha::getSpeacialAbilityEnergy() const
{
    return 4;
}

string SmallTaha::getAbility1Name()
{
    return "Razor";
}

string SmallTaha::getAbility2Name()
{
    return "Blood serum";
}

string SmallTaha::getSpecialAbilityName()
{
    return "Full quarantine";
}

Hero* SmallTaha::findLowestHpAlly(Team& myteam) const
{
    Hero* lowestHpHero = nullptr;
    int lowestHP = INT_MAX;
    for(int i=0 ; i<3 ; i++)
    {
        Hero* hero = myteam.getHero(i);
        if(hero != nullptr && hero != this && hero->isAlive())
        {
            int currentHP = hero->getHP();
            if(currentHP < lowestHP)
            {
                lowestHP = currentHP;
                lowestHpHero = hero;
            }
        }
    }
    return lowestHpHero;
}

void SmallTaha::useAbility1(class Team& myteam, class Team& enemyteam)
{
    if(myteam.getEnergy() < RAZOR_ENERGY)
    {
        cout << "not enough energy for razor blade!" << endl;
        return;
    }
    Hero* targetAlly = findLowestHpAlly(myteam);
    if(targetAlly == nullptr)
    {
        cout << "no alive ally to heal" << endl;
    }
    myteam.useEnergy(RAZOR_ENERGY);
    targetAlly->Heal(20);
    cout << "Small Taha healed " << targetAlly->getName() << " 20 HP!" << endl;

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

    targetEnemy->takeDamage(30);
    cout << "Small Taha attacked " << targetEnemy->getName() << " 30 HP!" << endl;
}

void SmallTaha::useAbility2(class Team& myteam, class Team& enemyteam)
{
    if(myteam.getEnergy() < SERUM_ENERGY)
    {
        cout << "not enough energy for blood serum!" << endl;
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

    myteam.useEnergy(SERUM_ENERGY);
    targetAlly->addHealOverTime(40, 2);
    cout << "Small Taha used blood serum on " << targetAlly->getName() << endl;
}

void SmallTaha::useSpecialAbility(class Team& myteam, class Team& enemyteam)
{
    if(counter < 0)
    {
        cout << "you can't use special ability!" << endl;
        return;
    }
    if(myteam.getEnergy() < SPECIAL_ENERGY)
    {
        cout << "not enough energy for special ability!" << endl;
        return;
    }
    Hero* targetAlly = findLowestHpAlly(myteam);
    if(targetAlly == nullptr)
    {
        cout << "no alive ally to heal!" << endl;
        return;
    }
    myteam.useEnergy(SPECIAL_ENERGY);
    performRage();
    targetAlly->Heal(SPECIAL_HEAL_AMOUNT);
    cout << targetAlly->getName() << " has been healed for " << SPECIAL_HEAL_AMOUNT << "HP by quarantine" << endl;

    counter = CountSpecialAbi;
}

void SmallTaha::PrintInfo() const
{
    cout << endl;
    cout << "Hero: Small Taha(healer)" << endl;
    cout << "HP: " << HP << "/" << MaxHealth << (isAlive() ? "[Alive]" : "[Dead]") << endl;
    cout << "Special ability cooldown: " << counter << "/" << CountSpecialAbi << endl;
    cout << endl;
}

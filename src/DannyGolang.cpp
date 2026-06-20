#include "DannyGolang.h"
#include <ctime>
#include <cstdlib>
#include <climits>

const int DannyGolang::LOCK_ENERGY = 2;
const int DannyGolang::ELEPHANT_ENERGY = 4;
const int DannyGolang::SPECIAL_ENERGY = 4;
const int DannyGolang::SHIELD_AMOUNT = 250;

DannyGolang::DannyGolang() : Hero("Danny Golang", 600, 4), lastLockTarget(nullptr), lockDamageRatio(1)
{
    ragePhrase = "nobody crosses this line";
}
DannyGolang::~DannyGolang()
{
}

int DannyGolang::getAbility1Energy() const
{
    return 2;
}

int DannyGolang::getAbility2Energy() const
{
    return 4;
}

int DannyGolang::getSpeacialAbilityEnergy() const
{
    return 4;
}

string DannyGolang::getAbility1Name()
{
    return "Lock";
}

string DannyGolang::getAbility2Name()
{
    return "Elephant gun";
}

string DannyGolang::getSpecialAbilityName()
{
    return "family's shelter";
}

Hero* DannyGolang::findHighestHPenemy(Team& enemyteam)
{
    Hero* highestHPhero = nullptr;
    int highestHP = -1;
    for(int i=0 ; i<3 ; i++)
    {
        Hero* enemy = enemyteam.getHero(i);
        if(enemy != nullptr && enemy->isAlive())
        {
            int currentHP = enemy->getHP();
            if(currentHP > highestHP)
            {
                highestHP = currentHP;
                highestHPhero = enemy;
            }
        }
    }
    return highestHPhero;
}

Hero* DannyGolang::findLowestHPally(Team& myteam) 
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

void DannyGolang::ResetLockstate()
{
    lastLockTarget = nullptr;
    lockDamageRatio = 1;
}

void DannyGolang::useAbility1(class Team& myteam, class Team& enemyteam)
{
    if(myteam.getEnergy() < LOCK_ENERGY)
    {
        cout << "not enough energy for lock!" << endl;
        return;
    }
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
    Hero* targetEnemy = nullptr;
    if(lastLockTarget != nullptr && lastLockTarget->isAlive())
    {
        targetEnemy = lastLockTarget;
        cout << "lock repeated on the same target!" << endl;
    }
    else
    {
        srand(time(0));
        int randomEnemy = rand() % aliveEnemies.size();
        Hero* targetEnemy = aliveEnemies[randomEnemy];

        lockDamageRatio = 1;
        cout << "lock on new target " << targetEnemy->getName() << endl;
    }
    myteam.useEnergy(LOCK_ENERGY);
    double damage = (20)*(lockDamageRatio);
    targetEnemy->takeDamage(damage);
    cout << "Danny Golang attacked " << targetEnemy->getName() << " for " << damage << "HP!" << endl;

    lastLockTarget = targetEnemy;
    lockDamageRatio *= 1.6;
}

void DannyGolang::useAbility2(class Team& myteam, class Team& enemyteam)
{
    if(myteam.getEnergy() < ELEPHANT_ENERGY)
    {
        cout << "not enough energy for elephant gun!" << endl;
        return;
    }
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

    Hero* highestHPenemy = findHighestHPenemy(enemyteam);
    if(highestHPenemy == nullptr)
    {
        cout << "no enemy with highest HP found!" << endl;
        return;
    }
    myteam.useEnergy(ELEPHANT_ENERGY);
    targetEnemy->takeDamage(ELEPHANT_ENERGY);
    cout << "Danny Golang attacked random enemy " << targetEnemy->getName() << " for 50 HP!" << endl;

    if(targetEnemy != highestHPenemy)
    {
        highestHPenemy->takeDamage(ELEPHANT_ENERGY);
        cout << "Danny Golang attacked highest HP enemy " << highestHPenemy->getName() << " for 50 HP!" << endl;
    }
    else
    {
        highestHPenemy->takeDamage(ELEPHANT_ENERGY);
        cout << highestHPenemy->getName() << " was attacked again!" << endl;
    }
}

void DannyGolang::useSpecialAbility(class Team& myteam, class Team& enemyteam)
{
    if(counter < 0)
    {
        cout << "you can't use special ability!" << endl;
        return;
    }
    Hero* targetAlly = findLowestHPally(myteam);
    if(targetAlly == nullptr)
    {
        cout << "no alive ally to shield." << endl;
        return;
    }
    myteam.useEnergy(SPECIAL_ENERGY);
    performRage();
    targetAlly->addShield(250, 2);
    cout << targetAlly->getName() << " has been shield with 250 HP for 2 turns" << endl;

    counter = CountSpecialAbi;
}

void DannyGolang::PrintInfo() const
{
    cout << endl;
    cout << "Hero: Danny Golang(defender)" << endl;
    cout << "HP" << HP << "/" << MaxHealth << (isAlive() ? "[Alive]" : "[Dead]") << endl;
    cout << "Special ability cooldown: " << counter << "/" << CountSpecialAbi << endl;
    cout << endl;
}

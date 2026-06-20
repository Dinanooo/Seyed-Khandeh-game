#include "BigTaha.h"
#include <ctime>
#include <climits>

const int BigTaha::BARRAGE_ENERGY = 3;
const int BigTaha::XRAY_ENERGY = 4;
const int BigTaha::SPECIAL_ENERGY = 3;

BigTaha::BigTaha() : Hero("Big Taha", 500, 4), isHidden(false), hiddenTurnsLeft(0), markedEnemy(nullptr), isMArkActive(false)
{
    ragePhrase = "this one was for my little brother... now it's your turn...";
}
BigTaha::~BigTaha()
{
}

int BigTaha::getAbility1Energy() const
{
    return 3;
}

int BigTaha::getAbility2Energy() const
{
    return 4;
}

int BigTaha::getSpeacialAbilityEnergy() const
{
    return 3;
}

string BigTaha::getAbility1Name()
{
    return "Barrage";
}

string BigTaha::getAbility2Name()
{
    return "X-ray";
}

string BigTaha::getSpecialAbilityName()
{
    return "Brother's revenge";
}

void BigTaha::resetHiddenState()
{
    isHidden = false;
    hiddenTurnsLeft = 0;
}

void BigTaha::useAbility1(class Team& myteam, class Team& enemyteam)
{
    if(myteam.getEnergy() < BARRAGE_ENERGY)
    { 
        cout << "not enough energy for barrage!" << endl;
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
    myteam.useEnergy(BARRAGE_ENERGY);

    for(Hero* enemy : aliveEnemies)
    {
        enemy->takeDamage(30);
        cout << "Big Taha hit " << enemy->getName() << " for 30 HP!" << endl;
        if(!enemy->isAlive())
        {
            cout << enemy->getName() << " has been daed!" << endl;
        }
    }
}

void BigTaha::useAbility2(class Team& myteam, class Team& enemyteam)
{
    if(myteam.getEnergy() < XRAY_ENERGY)
    {
        cout << "not enough energy for X-ray!" << endl;
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

    myteam.useEnergy(XRAY_ENERGY);
    targetEnemy->takeDamage(90);
    cout << "Big Taha used X-ray on " << targetEnemy->getName() << " for 90 HP!" << endl;

    if(!targetEnemy->isAlive())
    {
        cout << targetEnemy->getName() << " has been dead!" << endl;
    }
    isHidden = true;
    hiddenTurnsLeft = 1;
    cout << "Big Taha is now hidden for 1 turn!" << endl;
}


void BigTaha::useSpecialAbility(class Team& myteam, class Team& enemyteam)
{
    if(counter > 0)
    {
        cout << "you can't use special ability." << endl;
        return;
    }
    if(myteam.getEnergy() < SPECIAL_ENERGY)
    {
        cout << "not enough energy for special ability!" << endl;
        return;
    }
    if(isMArkActive)
    {
        cout << "a mark is already active!" << endl;
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
        cout << "no alive enemy to mark!" << endl;
        return;
    }
    srand(time(0));
    int randomEnemy = rand() % aliveEnemies.size();
    markedEnemy = aliveEnemies[randomEnemy];

    isMArkActive = true;
    myteam.useEnergy(SPECIAL_ENERGY);
    performRage();
    cout << markedEnemy->getName() << " has been marked!" << endl;
    cout << "he will take damage next turn." << endl;
    counter = CountSpecialAbi;
}

void BigTaha::applyMarkDamage()
{
    if(!isMArkActive || markedEnemy == nullptr)
    {
        return;
    }
    long int finalDamage;
    if(markedEnemy->getHP() <= 360)
    {
        finalDamage = 360;
        cout << markedEnemy->getName() << "'s HP was less than 360 so he died!" << endl;
    }
    else
    {
        finalDamage = 200;
        cout << markedEnemy->getName() << "'s was more than 360 so he took 200 damage!" << endl;
    }
    markedEnemy->takeDamage(finalDamage);
    cout << markedEnemy->getName() << " takes " << finalDamage << " damage!" << endl;

    if(!markedEnemy->isAlive())
    {
        cout << markedEnemy->getName() << " has been dead!" << endl;
    }
    isMArkActive = false;
    markedEnemy = nullptr;
}


void BigTaha::updateHiddenStatus()
{
    if(isHidden)
    {
        hiddenTurnsLeft--;
        if(hiddenTurnsLeft <= 0)
        {
            isHidden = false;
            cout << "Big Taha is no longer hidden!" << endl;
        }
    }
}

void BigTaha::PrintInfo() const
{
    cout << endl;
    cout << "Hero: Big Taha(attacker) " << endl;
    cout << "HP: " << HP << "/" << MaxHealth << (isAlive() ? "[Alive]" : "[Dead]") << endl;
    cout << "Special ability cooldown: " << counter << "/" << CountSpecialAbi << endl;
    cout << "status: " << (isHidden ? "Hidden" : "visible") << endl;
    cout << endl;
}

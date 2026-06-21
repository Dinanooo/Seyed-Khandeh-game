#include "AminSafety.h"
#include <ctime>
#include <cstdlib>
#include <vector>

const int AminSafety::LAST_BULLET_ENERGY = 3;
const int AminSafety::SELF_HIT_ENERGY = 3;
const int AminSafety::SPECIAL_ENERGY = 4;

AminSafety::AminSafety() : Hero("AminSafety", 500, 3)
{
    ragePhrase = "one...two...three...boom...who's left? doesn't matter";
}
AminSafety::~AminSafety()
{
}

int AminSafety::getAbility1Energy() const
{
    return 3;
}

int AminSafety::getAbility2Energy() const
{
    return 3;
}

int AminSafety::getSpeacialAbilityEnergy() const
{
    return 4;
}

string AminSafety::getAbility1Name()
{
    return "Last bullet";
}

string AminSafety::getAbility2Name()
{
    return "Self hit";
}

string AminSafety::getSpecialAbilityName()
{
    return "Shout of insecurity";
}

void AminSafety::useAbility1(class Team& myteam, class Team& enemyteam)
{
    if(myteam.getEnergy() < LAST_BULLET_ENERGY)
    {
        cout << "not enough energy for last bullet!" << endl;
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
        cout << "no alive enemy to attack." << endl;
        return;
    }
    srand(time(0));
    int randomEnemy = rand() % aliveEnemies.size();
    Hero* targetEnemy = aliveEnemies[randomEnemy];

    myteam.useEnergy(LAST_BULLET_ENERGY);
    int damage = 55;
    if(targetEnemy->getHP() <= damage)
    {
        damage = damage * 2;
    }
    targetEnemy->takeDamage(damage);
    cout << "Amin Safety attacked " << targetEnemy->getName() << " for " << damage << "HP!" << endl;
}

void AminSafety::useAbility2(class Team& myteam, class Team& enemyteam)
{
    if(myteam.getEnergy() < SELF_HIT_ENERGY)
    {
        cout << "not enough energy for self hit" << endl;
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
        cout << "no alive ally to hit" << endl;
        return;
    }
    srand(time(0));
    int randomAlly = rand() % aliveAllies.size();
    Hero* targetAlly = aliveAllies[randomAlly];
    
    myteam.useEnergy(SELF_HIT_ENERGY);
    targetAlly->takeDamage(25);
    cout << "Amin Safety took 25 HP from " << targetAlly->getName() << endl;

    if(!targetAlly->isAlive())
    {
        cout << targetAlly->getName() << " has been killed by his own ally Amin Safety!" << endl;
    }
    Heal(75);
    cout << "Amin Safety healed himself for 75 HP!" << endl;
}

void AminSafety::useSpecialAbility(class Team& myteam, class Team& enemyteam)
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
        cout << "no alive ally to hit!" << endl;
        return;
    }

    srand(time(0));
    int randomEnemy = rand() % aliveEnemies.size();
    Hero* targetEnemy = aliveEnemies[randomEnemy];

    vector<Hero*> selectedAllies;
    if(aliveAllies.size() == 1)
    {
        selectedAllies.push_back(aliveAllies[0]);
        selectedAllies.push_back(aliveAllies[0]);
        cout << "only one ally is alive and will be hit twice!" << endl;
    }
    else
    {
        int firstRandom = rand() % aliveAllies.size();
        Hero* firstAlly = aliveAllies[firstRandom];
        selectedAllies.push_back(firstAlly);

        int secondRandom = rand() % aliveAllies.size();
        Hero* secondAlly = aliveAllies[secondRandom];
        selectedAllies.push_back(secondAlly);
        
        if(firstAlly == secondAlly)
        {
            cout << "both hits on the same ally" << endl;
        }
    }
    myteam.useEnergy(SPECIAL_ENERGY);
    performRage();
    targetEnemy->takeDamage(250);
    cout << "Amin Safety attacked enemy " << targetEnemy->getName() << " for 250 HP!" << endl;

    for(Hero* ally : selectedAllies)
    {
        if(ally->isAlive())
        {
            ally->takeDamage(30);
            cout << "Amin Safety hit ally " << ally->getName() << " for 30 HP!" << endl;
            if(!ally->isAlive())
            {
                cout << ally->getName() << " has been killed by Amin Safety!" << endl;
            }
        }
    }
    counter = CountSpecialAbi;
}

void AminSafety::PrintInfo() const
{
    cout << endl;
    cout << "Hero: Amin Safety(attacker)" << endl;
    cout << "HP: " << HP << "/" << MaxHealth << (isAlive() ? "[Alive]" : "[Dead]") << endl;
    cout << "Special ability cooldown: " << counter << "/" << CountSpecialAbi << endl;
    cout << endl;
}

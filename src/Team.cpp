#include "Team.h"

Team::Team(const string& teamName, int energy)
: name(teamName), energy(energy)
{
}

void Team::addHero(Hero* hero)
{
    if(heroes.size() < 3)
    {
        heroes.push_back(hero);
    }
}

void Team::setEnergy(int a)
{
    energy = a;
}

int Team::getEnergy()
{
    return energy;
}

bool Team::useEnergy(int amount)
{
    if(energy >= amount)
    {
        energy -= amount;
        return true;
    }
    return false;
}

bool Team::isAliveTeam() const
{
    for(Hero* hero : heroes)
    {
        if(hero->isAlive())
        {
            return true;
        }
    }
    return false;
}

int Team::AliveCount()
{
    int count = 0;
    for(Hero* hero : heroes)
    {
        if(hero->isAlive())
        {
            count++;
        }
    }
    return count;
}

Hero* Team::getHero(int index)
{
    if(index >= 0 && index < heroes.size())
    {
        return heroes[index];
    }
    return nullptr;
}

void Team::showTeam()
{
    cout << "Team: " << name << " Energy: " << energy << endl;
    int i=1;
    for(const auto* hero : heroes)
    {
        cout << i << "_ " << hero->getName() 
        << " HP: " << hero->getHP() 
        << "| " << hero->getMaxHP()
        << (hero->isAlive() ? "[Alive]" : "[Dead]") << endl;
        i++;
    }
}

void Team::updateAllCounters()
{
    for(Hero* hero : heroes)
    {
        hero->updateCounter();
    }
}
void Team::updateAllBuffs()
{
    for(Hero* hero : heroes)
    {
        hero->UpdateBuffs();
    }
}
void Team::updateAllHotEffects()
{
    for(Hero* hero : heroes)
    {
        hero->updateHotEffects();
    }
}

void Team::updateAllShileds()
{
    for(Hero* hero : heroes)
    {
        hero->updateShields();
    }
}
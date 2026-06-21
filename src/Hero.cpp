#include "Hero.h"

Hero::Hero(string name, int hp, int countAbi) 
: Name(name), HP(hp), CountSpecialAbi(countAbi)
{
    MaxHealth = hp;
    counter = 0;
}

Hero::~Hero()
{
}

int Hero::getHP() const
{
    return this->HP;
}

int Hero::getMaxHP() const
{
    return this->MaxHealth;
}

void Hero::setName(string& name)
{
    Name = name;
}

string Hero::getName() const
{
    return Name;
}

int Hero::getSpecialCoolDown() const
{
    return counter;
}

int Hero::getCountSpecialAbi() const
{
    return CountSpecialAbi;
}

void Hero::takeDamage(int amount)
{
    HP -= amount;
    if(HP < 0)
    {
        HP = 0;
    }
}

void Hero::Heal(int amount)
{
    HP += amount;
    if(HP > MaxHealth)
    {
        HP = MaxHealth;
    }
}

bool Hero::isAlive() const
{
    if(HP > 0)
    {
        return true;
    }
    return false;
}

void Hero::updateCounter()
{
    if(counter > 0)
    {
        counter--;
    }
}

void Hero::performRage()
{
    cout << Name << ": " << ragePhrase << endl;
}

void Hero::Revive(int amount)
{
    if(HP > 0)
    {
        return;
    }
    HP = amount;
    if(HP > MaxHealth)
    {
        HP = MaxHealth;
    }
    cout << Name << " has been revived with " << HP << "HP!" << endl;
}

void Hero::AddDamageBuff(int percent, int turns)
{
    DamageBuff buff;
    buff.percent = percent;
    buff.turnsLeft = turns;
    damagebuffs.push_back(buff);
}

int Hero::getDamageBuffPercent() const
{
    int total = 0;
    for(const auto& buff : damagebuffs)
    {
        total += buff.percent;
    }
    return total;
}

void Hero::UpdateBuffs()
{
    for(auto it = damagebuffs.begin(); it != damagebuffs.end();)
    {
        it->turnsLeft--;
        if(it->turnsLeft <= 0)
        {
            it = damagebuffs.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Hero::addHealOverTime(int amount, int turns)
{
    HealOverTime hot;
    hot.amount = amount;
    hot.Turnsleft = turns;
    hotEffects.push_back(hot);
    cout << Name << " will receive " << amount << "HP from healing each turn for " << turns << " turns!" << endl;
}

void Hero::updateHotEffects()
{
    for(auto it = hotEffects.begin(); it != hotEffects.end();)
    {
        Heal(it->amount);
        cout << Name << " healed for " << it->amount << "HP from heal over time!" << endl;
        it->Turnsleft--;
        if(it->Turnsleft <= 0)
        {
            it = hotEffects.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Hero::addShield(int amount, int turns)
{
    Shield newShield;
    newShield.amount = amount;
    newShield.turnsLeft = turns;
    shields.push_back(newShield);
}

void Hero::updateShields()
{
    for(auto it = shields.begin(); it != shields.end();)
    {
        it->turnsLeft--;
        if(it->turnsLeft <= 0)
        {
            it = shields.erase(it);
        }
        else
        {
            ++it;
        }
    }
}
int Hero::getShieldAmount() const
{
    int total = 0;
    for(const auto& shield : shields)
    {
        total += shield.amount;
    }
    return total;
}
void Hero::takeDamageWithShield(int amount)
{
    int remainDamage = amount;
    for(auto it = shields.begin(); it != shields.end(); remainDamage > 0)
    {
        if(it->amount >= remainDamage)
        {
            it->amount -= remainDamage;
            remainDamage = 0;
            if(it->amount == 0)
            {
                it = shields.erase(it);
            }
            else
            {
                ++it;
            }
        }
        else
        {
            remainDamage -= it->amount;
            cout << Name << "'s shield absorbed " << it->amount << " damage and deleted!" << endl;
            it = shields.erase(it);
        }
    }
    if(remainDamage > 0)
    {
        takeDamage(remainDamage);
    }
}
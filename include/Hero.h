#ifndef HERO_H
#define HERO_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct DamageBuff
{
    int percent;
    int turnsLeft;
};

struct HealOverTime
{
    int amount;
    int Turnsleft;
};

struct Shield
{
    int amount;
    int turnsLeft;
};

class Hero
{
    protected:
        string Name;
        string ragePhrase;
        int HP;
        int MaxHealth;
        int CountSpecialAbi;
        int counter;
        vector<DamageBuff> damagebuffs;
        vector<HealOverTime> hotEffects;
        vector<Shield> shields;

    public:
        Hero(string name, int hp, int countAbi);
        virtual ~Hero();
        void setName(string& name);
        string getName() const;
        int getSpecialCoolDown() const;
        int getCountSpecialAbi() const;
        virtual void useAbility1(class Team& myteam, class Team& enemyteam) = 0;
        virtual void useAbility2(class Team& myteam, class Team& enemyteam) = 0;
        virtual void useSpecialAbility(class Team& myteam, class Team& enemyteam) = 0;
        virtual string getAbility1Name() = 0;
        virtual string getAbility2Name() = 0;
        virtual string getSpecialAbilityName() = 0;
        virtual int getAbility1Energy() const = 0;
        virtual int getAbility2Energy() const = 0;
        virtual int getSpeacialAbilityEnergy() const = 0;
        int getHP() const;
        int getMaxHP() const;
        void takeDamage(int amount);
        void Heal(int amount);
        bool isAlive() const;
        void updateCounter();
        void performRage();
        void Revive(int amount);
        void AddDamageBuff(int percent, int turns);
        int getDamageBuffPercent() const;
        void UpdateBuffs();
        void addHealOverTime(int amount, int turns);
        void updateHotEffects();
        void addShield(int amount, int turns);
        void updateShields();
        int getShieldAmount() const;
        void takeDamageWithShield(int amount);
        virtual void PrintInfo() const = 0;
};
#endif
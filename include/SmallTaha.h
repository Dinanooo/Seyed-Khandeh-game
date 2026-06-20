#ifndef SMALLTAHA_H
#define SMALLTAHA_H
#include <iostream> 
#include <string>
#include "Team.h"
#include "Hero.h"
using namespace std;

class SmallTaha : public Hero
{
    private:
        Hero* findLowestHpAlly(Team& myteam) const;
        static const int RAZOR_ENERGY;
        static const int SERUM_ENERGY;
        static const int SPECIAL_ENERGY;
        static const int SPECIAL_HEAL_AMOUNT;

    public:
        SmallTaha();
        ~SmallTaha();
        virtual void useAbility1(class Team& myteam, class Team& enemyteam) override;
        virtual void useAbility2(class Team& myteam, class Team& enemyteam) override;
        virtual void useSpecialAbility(class Team& myteam, class Team& enemyteam) override;
        virtual string getAbility1Name() override;
        virtual string getAbility2Name() override;
        virtual string getSpecialAbilityName() override;
        virtual int getAbility1Energy() const override;
        virtual int getAbility2Energy() const override;
        virtual int getSpeacialAbilityEnergy() const override;
        virtual void PrintInfo() const override;
};
#endif
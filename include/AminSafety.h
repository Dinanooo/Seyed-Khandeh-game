#ifndef AMINSAFETY_H
#define AMINSAFETY_H
#include <iostream>
#include <string>
#include "Team.h"
#include "Hero.h"
using namespace std;

class AminSafety : public Hero
{
    private:
        static const int LAST_BULLET_ENERGY;
        static const int SELF_HIT_ENERGY;
        static const int SPECIAL_ENERGY;

    public:
        AminSafety();
        ~AminSafety();
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
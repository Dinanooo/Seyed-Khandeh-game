#ifndef DOCTORWHITE_H
#define DOCTORWHITE_H
#include <iostream>
#include <string>
#include "Hero.h"
#include "Team.h"
using namespace std;

class DoctorWhite : public Hero
{
    private:
        static const int ASPIRIN_ENERGY;
        static const int DOPING_ENERGY;
        static const int SPECIAL_ENERGY;
        static const int REVIVE_UP;

    public:
        DoctorWhite();
        ~DoctorWhite();
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
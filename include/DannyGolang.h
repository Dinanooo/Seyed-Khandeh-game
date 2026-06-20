#ifndef DANNYGOLANG_H
#define DANNYGOLANG_H
#include <iostream>
#include <string>
#include "Hero.h"
#include "Team.h"
using namespace std;

class DannyGolang : public Hero
{
    private:
        Hero* lastLockTarget;
        int lockDamageRatio;
        Hero* findHighestHPenemy(Team& enemyteam);
        Hero* findLowestHPally(Team& myteam);
        void ResetLockstate();
        static const int LOCK_ENERGY;
        static const int ELEPHANT_ENERGY;
        static const int SPECIAL_ENERGY;
        static const int SHIELD_AMOUNT;

    public:
        DannyGolang();
        ~DannyGolang();
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
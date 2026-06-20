#ifndef BIGTAHA_H
#define BIFTAHA_H
#include "Hero.h"
#include "Team.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class BigTaha : public Hero
{
    private:
        bool isHidden;
        int hiddenTurnsLeft;
        Hero* markedEnemy;
        bool isMArkActive;
        void resetHiddenState();
        void resetMarkState();
        static const int BARRAGE_ENERGY;
        static const int XRAY_ENERGY;
        static const int SPECIAL_ENERGY;

    public:
        BigTaha();
        ~BigTaha();
        void applyMarkDamage();
        void updateHiddenStatus();
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
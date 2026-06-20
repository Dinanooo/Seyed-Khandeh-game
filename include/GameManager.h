#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "Team.h"
#include "Hero.h"
#include "Drwhite.h"
#include "SmallTaha.h"
#include "DannyGolang.h"
#include "AminSafety.h"
#include "BigTaha.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class GameManager 
{
    protected:
        Team* team1;
        Team* team2;
        vector<Hero*> allHeroesTeam1;
        vector<Hero*> allHeroesTeam2;
        int currentRound;
        int maxRound;
        bool gameIsOver;
        string winner;
        vector<int> team1Energy;
        vector<int> team2Energy;
        int team1EnergyIndex;
        int team2EnergyIndex;
        bool isTeam1Turn;
        bool isTurnActive;
        vector<Hero*> team1Heroes;
        vector<Hero*> team2Heroes;

        void InitializeAllHeroesTeam1();
        void InitializeAllHeroesTeam2();
        void SelectHeroesForTeams();
        void displayHeroSelection(int teamNum);
        void displayHeroInfo(Hero* hero);
        void displayGameStatus();
        void displayRoundStatus();
        void displayTurnsStatus(Team* currentTeam);
        void displayEndGameStatus();
        void handleTurn(Team* currentTeam, Team* enemyTeam);
        void handleAbilitySelection(Team* currentTeam, Team* enemyTeam, Hero* hero);
        void applyEndOfTurnEffects(Team* team);
        void checkGameOver();
        void DetermineWinner();
        int getEnergyForRound(int teamNum);
        void nextRound();
        void resetForNewRound();

    public:
        GameManager();
        ~GameManager();
        void StartGame();
        void RunGame();
        void EndGame();
};
#endif
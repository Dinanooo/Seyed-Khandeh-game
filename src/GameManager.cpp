#include "GameManager.h"
#include <climits>
#include <ctime>
#include <algorithm>

GameManager::GameManager()
: currentRound(1), maxRound(15), gameIsOver(false), winner(""),
isTurnActive(false), team1EnergyIndex(0), team2EnergyIndex(0)
{
    srand(time(0));
    team1Energy = {5, 8, 9, 10};
    team2Energy = {8, 9, 10};
    team1 = nullptr;
    team2 = nullptr;
    InitializeAllHeroesTeam1();
    InitializeAllHeroesTeam2();
}
        
GameManager::~GameManager()
{
    delete team1;
    delete team2;
    for(auto hero : allHeroesTeam1)
    {
        delete hero;
    }
    for(auto hero : allHeroesTeam2)
    {
        delete hero;
    }
    allHeroesTeam1.clear();
    allHeroesTeam2.clear();
}

void GameManager::InitializeAllHeroesTeam1()
{
    allHeroesTeam1.push_back(new DoctorWhite());
    allHeroesTeam1.push_back(new SmallTaha());
    allHeroesTeam1.push_back(new DannyGolang());
    allHeroesTeam1.push_back(new AminSafety());
    allHeroesTeam1.push_back(new BigTaha());
}

void GameManager::InitializeAllHeroesTeam2()
{
    allHeroesTeam2.push_back(new DoctorWhite());
    allHeroesTeam2.push_back(new SmallTaha());
    allHeroesTeam2.push_back(new DannyGolang());
    allHeroesTeam2.push_back(new AminSafety());
    allHeroesTeam2.push_back(new BigTaha());
}

void GameManager::SelectHeroesForTeams()
{
    cout << endl;
    cout << "<<<...Hero Selection...>>>" << endl;
    cout << endl;
    cout << "Team 1 : Please select your favorite heroes! (just 3 heroes) " << endl;
    for(int i=0 ; i<3 ; i++)
    {
        displayHeroSelection(1);
        cout << "Select Hero " << i+1 << " (enter number) " << endl;
        int choice;
        cin >> choice;
        if(choice >= 1 && choice <= 5)
        {
            Hero* selectedHero = allHeroesTeam1[choice-1];
            bool alreadySelected = false;
            for(Hero* hero : team1Heroes)
            {
                if(hero->getName() == selectedHero->getName())
                {
                    alreadySelected = true;
                    break;
                }
            }
            if(!alreadySelected)
            {
                team1Heroes.push_back(selectedHero);
                cout << "Selected: " << selectedHero->getName() << endl;
            }
            else
            {
                cout << "Hero already selected! choose another one." << endl;
                i--;
            }
        }
        else
        {
            cout << "invalid choice! try again." << endl;
            i--;
        }
    }
    cout << "Team 2 : Please select your favorite heroes! (just 3 heroes) " << endl;
    
    for(int i=0 ; i<3 ; i++)
    {
        displayHeroSelection(2);
        cout << "Select Hero " << i+1 << " (enter number) " << endl;
        int choice;
        cin >> choice;
        if(choice >= 1 && choice <= 5)
        {
            Hero* selectedHero = allHeroesTeam2[choice-1];
            bool alreadySelected = false;
            for(Hero* hero : team2Heroes)
            {
                if(hero->getName() == selectedHero->getName())
                {
                    alreadySelected = true;
                    break;
                }
            }
            if(!alreadySelected)
            {
                team2Heroes.push_back(selectedHero);
                cout << "Selected: " << selectedHero->getName() << endl;
            }
            else
            {
                cout << "Hero already selected! choose another one." << endl;
                i--;
            }
        }
        else
        {
            cout << "invalid choice! try again." << endl;
            i--;
        }
    }
}


void GameManager::displayHeroSelection(int teamNum)
{
    cout << endl;
    cout << "List of available heroes to select: " << endl;
    int index = 1;
    vector<Hero*> heroesList = (teamNum == 1) ? allHeroesTeam1 : allHeroesTeam2;
    for(Hero* hero : heroesList)
    {
        bool alreadySelected = false;
        if(teamNum == 1)
        {
            for(Hero* h : team1Heroes)
            {
                if(h->getName() == hero->getName())
                {
                    alreadySelected = true;
                    break;
                }
            }
        }
        else
        {
            for(Hero* h : team2Heroes)
            {
                if(h->getName() == hero->getName())
                {
                    alreadySelected = true;
                    break;
                }
            }
        }
        if(!alreadySelected)
        {
            cout << index << ". " << hero->getName() 
            << "(HP: " << hero->getMaxHP() << ")" << endl;
        }
        index++;
    }
}


void GameManager::displayHeroInfo(Hero* hero)
{
    cout << "Name: " << hero->getName() << endl;
    cout << "HP: " << hero->getHP() << "/" << hero->getMaxHP() << endl;
}

void GameManager::displayGameStatus()
{
    cout << endl;
    cout << "Game status: " << endl;
    cout << "Round: " << currentRound << "/" << maxRound << endl;
    cout << "----------------------------------------" << endl;
    cout << "Team 1: " << endl;
    if(team1)
    {
        team1->showTeam();
    }
    cout << "Team 2: " << endl;
    if(team2)
    {
        team2->showTeam();
    }
    cout << endl;
}

void GameManager::displayRoundStatus()
{
    cout << "----------------------------------------" << endl;
    cout << "Round: " << currentRound << endl;
    cout << "----------------------------------------" << endl;
    int T1energy = getEnergyForRound(1);
    int T2energy = getEnergyForRound(2);
    cout << "Team 1 energy: " << T1energy << endl;
    cout << "Team 2 energy: " << T2energy << endl;
    cout << "----------------------------------------" << endl;
}

void GameManager::displayTurnsStatus(Team* currentTeam)
{
    string teamName = (currentTeam == team1) ? "Team 1" : "Team 2";
    cout << endl;
    cout << teamName << "'s turn....." << endl;
    cout << "available heroes: " << endl;
    for(int i=0 ; i<3 ; i++)
    {
        Hero* hero = currentTeam->getHero(i);
        if(hero)
        {
            cout << i+1 << ". " << hero->getName() 
            << " - HP: " << hero->getHP() << "/" << hero->getMaxHP()
            << " [" << (hero->isAlive() ? "Alive" : "Dead") << "]" << endl;
            if(hero->isAlive())
            {
                cout << " (Special ability: " << hero->getSpecialCoolDown() << "/" 
                << hero->getCountSpecialAbi() << ")" << endl;
                cout << endl;
            }
        }
    }
    cout << endl;
}


void GameManager::handleTurn(Team* currentTeam, Team* enemyTeam)
{
    isTurnActive = true;
    while(isTurnActive)
    {
        displayTurnsStatus(currentTeam);
        if(currentTeam->getEnergy() <= 0)
        {
            cout << "No energy left! turn ended." << endl;
            isTurnActive = false;
            break;
        }
        cout << "Select hero(1-3) or 0 to end turn: " << endl;
        int choice;
        cin >> choice;
        if(choice == 0)
        {
            cout << "you ended your turn!" << endl;
            isTurnActive = false;
            break;
        }
        if(choice < 1 || choice > 3)
        {
            cout << "invalid choice! try again." << endl;
            continue;
        }
        Hero* selectedHero = currentTeam->getHero(choice - 1);
        if(!selectedHero || !selectedHero->isAlive())
        {
            cout << "hero is dead or doesn't exist! choose another one." << endl;
            continue;
        }
        handleAbilitySelection(currentTeam, enemyTeam, selectedHero);

        if(currentTeam->getEnergy() <= 0)
        {
            cout << "No energy left! turn ended." << endl;
            isTurnActive = false;
            break;
        }
        checkGameOver();
        if(gameIsOver)
        {
            isTurnActive = false;
            break;
        }
    }
}


void GameManager::handleAbilitySelection(Team* currentTeam, Team* enemyTeam, Hero* hero)
{
    cout << endl;
    cout << hero->getName() << "'s abilities: " << endl;
    cout << "1. Ability 1: " << hero->getAbility1Name() << endl;
    cout << "Energy: " << hero->getAbility1Energy() << endl;
    cout << "2. Ability 2: " << hero->getAbility2Name() << endl;
    cout << "Energy: " << hero->getAbility2Energy() << endl;
    cout << "3. SpecialEnergy: " << hero->getSpecialAbilityName() << endl;
    cout << "Energy: " << hero->getSpeacialAbilityEnergy() << endl;
    if(hero->getSpecialCoolDown() == 0)
    {
        cout << "you can use Special energy! it's ready" << endl;
    }
    else
    {
        cout << "you can't use Special energy." << endl;
        cout << "[cool down: " << hero->getSpecialCoolDown() << " turns]" << endl;
    }
    cout << "0. Cancel" << endl;

    cout << "Select ability: " << endl;
    int choice;
    cin >> choice;
    if(choice == 0)
    {
        return;
    }
    if(choice < 1 || choice > 3)
    {
        cout << "Invalid choice!" << endl;
        return;
    }
    switch(choice)
    {
        case 1:
            hero->useAbility1(*currentTeam, *enemyTeam);
            break;

        case 2:
            hero->useAbility2(*currentTeam, *enemyTeam);
            break;

        case 3:
            hero->useSpecialAbility(*currentTeam, *enemyTeam);
            break;

        default:
            cout << "invalid ability!" << endl;
            break;
    }
}

void GameManager::applyEndOfTurnEffects(Team* team)
{
    team->updateAllCounters();
    team->updateAllBuffs();
    team->updateAllHotEffects();
    team->updateAllShileds();
}

void GameManager::checkGameOver()
{
    if(!team1->isAliveTeam() || !team2->isAliveTeam())
    {
        gameIsOver = true;
        DetermineWinner();
    }
    else if(currentRound > maxRound)
    {
        gameIsOver = true;
        DetermineWinner();
    }
}

void GameManager::DetermineWinner()
{
    int T1alive = team1->AliveCount();
    int T2alive = team2->AliveCount();
    if(T1alive == 0 && T2alive == 0)
    {
        winner = "Draw!";
    }
    else if(T1alive == 0)
    {
        winner = "Team 2";
    }
    else if(T2alive == 0)
    {
        winner = "Team 1";
    }
    else if(currentRound > maxRound)
    {
        if(T1alive > T2alive)
        {
            winner = "Team 1";
        }
        else if(T2alive > T1alive)
        {
            winner = "Team 2";
        }
        else 
        {
            winner = "Draw!";
        }
    }
}


int GameManager::getEnergyForRound(int teamNum)
{
    if(teamNum == 1)
    {
        if(team1EnergyIndex < team1Energy.size())
        {
            return team1Energy[team1EnergyIndex];
        }
        else
        {
            return 10;
        }
    }
    else if(teamNum == 2)
    {
        if(team2EnergyIndex < team2Energy.size())
        {
            return team2Energy[team2EnergyIndex];
        }
        else
        {
            return 10;
        }
    }
}


void GameManager::nextRound()
{
    currentRound++;
    if(team1EnergyIndex < team1Energy.size())
    {
        team1EnergyIndex++;
    }
    if(team2EnergyIndex < team2Energy.size())
    {
        team2EnergyIndex++;
    }
}

void GameManager::resetForNewRound()
{
    int T1energy = getEnergyForRound(1);
    int T2energy = getEnergyForRound(2);
    team1->setEnergy(T1energy);
    team2->setEnergy(T2energy);
}


void GameManager::StartGame()
{
    cout << "----------------------------------------" << endl;
    cout << "---WELCOME TO SEYED HKANDEH GAMEPLAY!---" << endl;
    cout << "----------------------------------------" << endl;
    SelectHeroesForTeams();
    team1 = new Team("Team 1", 0);
    team2 = new Team("Team 2", 0);
    for(Hero* hero : team1Heroes)
    {
        team1->addHero(hero);
    }
    for(Hero* hero : team2Heroes)
    {
        team2->addHero(hero);
    }
    isTeam1Turn = rand() % 2;
    cout << (isTeam1Turn ? "Team 1" : "Team 2") << " starts the game!" << endl;
    RunGame();
}


void GameManager::RunGame()
{
    while(!gameIsOver && currentRound <= maxRound)
    {
        displayRoundStatus();
        resetForNewRound();
        if(isTeam1Turn)
        {
            cout << endl;
            cout << "---Team 1's Turn---" << endl;
            handleTurn(team1, team2);
            if(!gameIsOver)
            {
                cout << "---Team 2's Turn---" << endl;
                handleTurn(team2, team1);
            }
        }
        else if(!isTeam1Turn)
        {
            cout << "---Team 2's Turn---" << endl;
            handleTurn(team2, team1);
            if(!gameIsOver)
            {
                cout << "---Team 1's Turn---" << endl;
                handleTurn(team1, team2);
            }
        }
        if(!gameIsOver)
        {
            applyEndOfTurnEffects(team1);
            applyEndOfTurnEffects(team2);
        }
        if(!gameIsOver)
        {
            nextRound();
        }
        displayGameStatus();
    }
    EndGame();
}


void GameManager::EndGame()
{
    cout << "----------------------------------------" << endl;
    cout << "--------------Game Over-----------------" << endl;
    cout << "----------------------------------------" << endl;
    if(winner.empty())
    {
        DetermineWinner();
    }
    cout << "Winner: " << winner << "!" << endl;
    cout << "Total rounds: " << currentRound << endl;
    cout << "Final status: " << endl;
    displayGameStatus();

    cout << "----------------------------------------" << endl;
    cout << "---------Thanks for playing!------------" << endl;
}

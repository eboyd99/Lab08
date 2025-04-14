#include <iostream>
#include <string>
#include "windows.h"
#include <ctime>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

void HUD();
void Combat();
void CombatHUD();
void Moving();
void CreateMonster();
void LevelUp();

int monsterHp = 0, monsterXp = 0, monsterLevel = 0;

string monsterName[] = {"Goblin", "Dwarf", "Ogre", "Witch", "Demon", "Wizard"};
int currentMonsterNames = 5;
string currentMonster = " ";

string sex = " ", race = " ", name = " ";
string playerRace[] = {"elf", "dwarf", "firelord", "goblin", "human"};
int level, xp, health, totalHealth, maxHealth, nextLevel, heal;

void CharacterCreation() {

    level = 1;
    xp = 0;
    nextLevel = 75;

    cout << "Enter Character Name: ";
    cin >> name;
    
    cout << "Elf\nDwarf\nFireLord\nGoblin\nHuman\n";
    cout << "Enter Character Race: \n\n";
    cin >> race;

    for_each(race.begin(), race.end(), [](char & c) {
        c - tolower(c);
    });

    for (int i = 0; i < sizeof(playerRace); i++){
        if(race == "elf"){
            health = 80;
            break;
        }
        if (race == "dwarf"){
            health = 120;
            break;
        }
        if (race == "firelord"){
            health = 150;
            break;
        }
        if (race == "goblin"){
            health = 70;
            break;
        }
        if (race == "human"){
            health = 100;
            break;
        }
        else{
            health = 100;
            break;
        }
    }

    cout << "Enter Character Sex: ";
    cin >> sex;

    cout << "Creating Character";
    Sleep(400);
    for (int i = 0; i < 3; i++){
        cout << ".";
        Sleep(400);
    }

    race[0] = toupper(race[0]);
    name[0] = toupper(name[0]);
    sex[0] = toupper(sex[0]);

    totalHealth = health;
    maxHealth = totalHealth;
}

int main(){

    srand(time(0));
    
    CharacterCreation();
    
    system("cls");
    
    HUD();


    return 0;

}

void CombatHUD() {
    Sleep(500);
    system("cls");
    cout << "Name: " << name << "       |       Monster Name: " << currentMonster << "\nHealth: " << totalHealth << "       |       Monster Health: "
         << monsterHp << "\nLevel: " << level << "      |       Monster Level: " << monsterLevel << endl;
}

void Combat() {
    CombatHUD();
    int playerAttack;
    int playerDamage = (10 * level) / 2;
    int monsterAttack = (6 * monsterLevel) / 2;

    if (totalHealth >= 1 && monsterHp >= 1){
        cout << endl;
        cout << "1. Attack\n";
        cout << "2. Block\n";
        cout << "3. Run\n\n";
        cin >> playerAttack;

        if (playerAttack == 1){
            cout << "Attacking ... you did " << playerDamage << " to the " << currentMonster << endl;
            monsterHp -= playerDamage;
            if (monsterHp <= 0){
                monsterHp = 0;
            }
            Sleep(1000);
            CombatHUD();
            if(monsterHp >= 1){
                cout << "\nThe monster is attacking...\n";
                totalHealth -= monsterAttack;
                cout << "You suffered " << monsterAttack << " damage. Health is " << totalHealth << endl;
            }
            Sleep(1000);
            Combat();
        }
        else if(playerAttack == 2){
            cout << "Blocking\n";
            int i = rand() % 100 + 1;
            if (i >= 50){
                cout << "You blocked the incoming attack\n";
                heal = level * 10 / 2;
                cout << "You have been healed for " << heal << endl;
                totalHealth += heal;
                if (totalHealth > maxHealth){
                    totalHealth = maxHealth;
                }
                Sleep(1000);
                Combat();
            }
            else{
                cout << "You failed to block the savage attack\n";
                totalHealth -= monsterAttack;
                cout << "You were stabbed in the back for " << monsterAttack << " . Current hp: " << totalHealth << endl;
                Sleep(1000);
                Combat();
            }
        }
        else if (playerAttack == 3){
            cout << "You try to run\n";
            int x = rand() % 100 + 1;
            if (x >= 50) {
                cout << "You run away\n";
                HUD();
            }
            else {
                cout << "You failed to run away\n";
                cout << "Monster attacks you!\n";
                totalHealth -= monsterAttack + 10;
                cout << "You suffered " << monsterAttack + 10 << ". Your current health is " << totalHealth << endl;
                Sleep(1000);
                Combat();
            }
        }
        else{
            cout << "Invalid Choice" << endl;
            Sleep(500);
            Combat();
        }

    }
    if (totalHealth <= 1){
        totalHealth = 0;
            system("cls");
            cout << "You died!\nYou were level: " << level << "\nYou got killed by " << currentMonster << endl;
            Sleep(2000);
            exit(0);
    }
    if (monsterHp <= 1){
        LevelUp();
        cout << "\nYou defeated " << currentMonster << " you are rewarded with " << monsterXp << " xp!";
        Sleep(2000);
        system("cls");
        HUD();
    }
}

void HUD() {
    Sleep(500);
    cout << "Name: " << name << "       Health: " << totalHealth << "\nRace: " << race
         << "       Sex: " << sex << "\nLevel: " << level << "\nxp: " << xp << "\nxp to level: " << nextLevel << endl;

    Moving();
}

void Moving() {

    int choice;

    cout << endl << endl;
    cout << "1. Move Forward\n";
    cout << "2. Relax\n";
    cout << "3. Move Backwards\n";
    cout << endl << endl;

    cin >> choice;

    if (choice == 1){
        int temp = rand() % 100 + 1;
        cout << "You begin moving forward...\n";
        if (temp >= 50){
            CreateMonster();
            string tempName = monsterName[rand() % currentMonsterNames];
            cout << "A " << tempName << "! Prepare to fight!\n";
            currentMonster = tempName;
            Sleep(1000);
            Combat();
        }
        cout << "You find nothing of interest\n";
        Sleep(1000);
        HUD();
    }
    else if (choice == 2){
        cout << "You want to set up camp for the evening\n";
        if (totalHealth < maxHealth){
            totalHealth += 10 * level;
            if (totalHealth > maxHealth){
                totalHealth = maxHealth;
            }
        }
        cout << "You healed by resting. Health is now: " << totalHealth << endl;
        Sleep(100);
        HUD();
    }
    else if (choice == 3){
        int temp = rand() % 100 + 1;
        cout << "You begin moving backwards...\n";
        if (temp >= 50){
            CreateMonster();
            string tempName = monsterName[rand() % currentMonsterNames];
            cout << "A " << tempName << "! Prepare to fight!\n";
            currentMonster = tempName;
            Sleep(1000);
            Combat();
        }
        cout << "You find nothing of interest\n";
        Sleep(1000);
        HUD();
    }
    else{
        cout << "Invalid Choice" << endl;
        Sleep(500);
        Moving();
    }
}

void LevelUp() {
    xp = xp + monsterXp;

    while (xp >= nextLevel){
        level++; // did not implement a level cap
        nextLevel += (floor(level + 50 * pow(2, level / 7)));
        maxHealth = floor(maxHealth + 13 * pow(2, level / 8));
        totalHealth = maxHealth; // when the  user levels up, they fully heal
        cout << "You've leveled up! You are now level " << level << "!" << endl;
        cout << "Your total health increased by 20 points! Total max health is " << maxHealth << endl;
        Sleep(2000);
    }
    HUD();
}

void CreateMonster(){
    monsterHp = 30;
    monsterLevel = (rand() % 3) + level;
    monsterHp = (rand() % 30) * monsterLevel;
    monsterXp = monsterHp + (monsterLevel * 2); 
    
    if (monsterHp == 0){
        CreateMonster();
    }
    if (monsterLevel == 0){
        CreateMonster();
    }

}
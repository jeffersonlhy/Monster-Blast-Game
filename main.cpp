#include <iostream>
#include <chrono>
#include <ctime>
#include <time.h>
#include <fstream>
#include "colour.h"
#include "display.h"
#include "setup.h"
#include "field.h"
#include "battle.h"
#include "story.h"
using namespace std;


bool playerstart = true;

int main()
{
  Field field;  //initialize the class variable
  BattleStatus battle;
  char gar;
  
  system("clear");
  zerodaybanner();
  intro();
  cout << endl;
  cout << red_chosen << "READY TO FIGHT? (Y)/(N)" << reset << endl;
  string inputtemp;
  cin >> inputtemp;
  char choice=inputtemp[0];
  while (!(choice == 'Y' || choice == 'N')|| !(inputtemp.length()==1)) //prompt userinput
  {
    cout << "WRONG INPUT. WANT TO EXIT (E)?" << endl;
    cin >> inputtemp;
    if (inputtemp.length()==1)
    {
      choice = inputtemp[0];
      if (choice == 'E')
      {
        playerstart = false;
        break;
      }
    }
    else
      choice = inputtemp[0];
  }
  if (choice == 'Y')
  {
    cout << "START or OPEN SAVED FILE? (S)/(O)" << endl;
    string temp1;
    cin >> temp1;
    char choice1;
    choice1=temp1[0];
    while (!(choice1 == 'S' || choice1 == 'O'|| choice1 == 's' || choice1 == 'o') || !(temp1.length()==1))
    {
      cout << "WRONG INPUT. WANT TO EXIT(E)" << endl;
      cin >> temp1;
      if (temp1.length()==1)
      {
        choice1=temp1[0];
        if (choice1 == 'e' || choice1 == 'E')
        {
          playerstart = false;
          break;
        }
      }
      else
        choice1=temp1[0];
    }
    if (choice1 == 'S'||choice1 == 's')
    {
      field.iniField();
      battle.ini_player();    //player info created
      battle.spawn_monster(); //monster info created
    }

    else if (choice1 == 'O' || choice1 == 'o') 
    {
      string name;
      cout << "INPUT NAME OF YOUR SAVE (WITHOUT .txt)" << endl;
      cin >> name;
      name.append(".txt");
      ifstream savefile;
      savefile.open(name);
      while (!savefile.is_open())
      {
        cout << "FILE NOT FOUND\nENTER AGAIN OR INPUT E to EXIT\n";
        cin >> name;
        if (name == "E")
        {
          playerstart == false;
          break;
        }
        name.append(".txt");
        savefile.open(name);
      }
      if (savefile.is_open())
      {
        for (int i = 0; i < 16; ++i)
        {
          string temp;
          if (i == 0)
          {
            getline(savefile, temp);
            battle.load_MonsterMaxHP(temp);
          }
          if (i == 1)
          {
            getline(savefile, temp);
            battle.load_MonsterHP(temp);
          }
          if (i == 2)
          {
            getline(savefile, temp);
            battle.load_MonsterAttack(temp);
          }
          if (i == 3)
          {
            getline(savefile, temp);
            battle.load_MonsterType(temp);
          }
          if (i == 4)
          {
            getline(savefile, temp);
            battle.load_level(temp);
          }
          if (i == 5)
          {
            getline(savefile, temp);
            battle.load_round(temp);
          }
          if (i == 6)
          {
            getline(savefile, temp);
            battle.load_PlayerMaxHP(temp);
          }
          if (i == 7)
          {
            getline(savefile, temp);
            battle.load_PlayerHP(temp);
          }
          if (i == 8)
          {
            getline(savefile, temp);
            battle.load_PlayerAttack(temp);
          }
          if (i == 9)
          {
            getline(savefile, temp);
            battle.load_PlayerHeal(temp);
          }
          if (i == 10)
          {
            getline(savefile, temp);
            battle.load_revive(temp);
          }
          if (i == 11)
          {
            getline(savefile, temp);
            battle.load_PlayerSkillsCode(temp);
          }
          if (i == 12)
          {
            getline(savefile, temp);
            battle.load_PlayerSkills1Cd(temp);
          }
          if (i == 13)
          {
            getline(savefile, temp);
            battle.load_PlayerSkills2Cd(temp);
          }
          if (i == 14)
          {
            getline(savefile, temp);
            battle.load_PlayerSkills3Cd(temp);
          }
          if (i == 15)
          {
            getline(savefile, temp);
            cout << "temp = " << temp << endl;
            field.load_field(temp);
          }
        }
        savefile.close();
      }
    }
  }
  else //if the user input "N"
  {
    playerstart = false;
    cout << "NERVIOUS? HAHAHA...." << endl;
  }

  //game starts
  while (playerstart && gamestatus == RUNNING)
  {
    system("clear");
    //this whole set of print gives the main interface of our game
    battle.display_level();
    battle.display_round();
    battle.display_att(battle.monster);
    battle.display_monster();
    battle.display_att(battle.player);
    battle.use_skills();
    field.printfield();
    field.printinstruction();

    while (!field.checkstart()) //the user have to press "Enter" to procced to the swapping part by breaking this loop
    {
      field.getMove(); // update x & y in field
      system("clear");
      battle.display_level();
      battle.display_round();
      battle.display_att(battle.monster);
      battle.display_monster();
      battle.display_att(battle.player);
      battle.skills_bar();
      field.printfield();
      field.printinstruction();
    }

    //SWAP begins
    if (field.checkstart())
    {
      clock_t t1 = time(NULL); //initial clock
      while (true)
      {
        clock_t t2 = time(NULL); //the instantaneous clock for making the timer
        if (difftime(t2, t1) >= 7)
        {
          cout << "--TIMES UP--" << endl;
          field.start_false();
          break;
        }
        field.getMove();
        field.swap();
        system("clear");
        battle.display_level();
        battle.display_round();
        battle.display_att(battle.monster);
        battle.display_monster();
        battle.display_att(battle.player);
        battle.skills_bar();
        field.printfield();
        cout << "TIME LEFT = " << 7 - difftime(t2, t1) << endl;
      }
    }

    field.tile_searching(); //damage_byuser updated

    if (field.field_need_emn()) //for searching and eliminating the additional combo resulted as the random regeneration 
    {
      field.field_elimination(); 
      sleep(2);
      system("clear");
      battle.display_level();
      battle.display_round();
      battle.display_att(battle.monster);
      battle.display_monster();
      battle.display_att(battle.player);
      battle.skills_bar();
      field.printHLfield();
      field.printshortcombo();

      sleep(1.5);
      field.fieldfalling();
      field.field_regen();
      system("clear");
      battle.display_level();
      battle.display_round();
      battle.display_att(battle.monster);
      battle.display_monster();
      battle.display_att(battle.player);
      battle.skills_bar();
      field.printHLfield(); //non highlighted one
      field.printshortcombo();
      sleep(2);

      field.combobuff_divider();
      field.tile_searching();
      while (field.field_need_emn()) //until the field has no more matched tiles to be eliminated
      {
        field.field_elimination();
        system("clear");
        battle.display_level();
        battle.display_round();
        battle.display_att(battle.monster);
        battle.display_monster();
        battle.display_att(battle.player);
        battle.skills_bar();
        field.printHLfield(); //highlighed
        field.printshortcombo();
        sleep(1.5);

        field.fieldfalling();
        field.field_regen();
        system("clear");
        battle.display_level();
        battle.display_round();
        battle.display_att(battle.monster);
        battle.display_monster();
        battle.display_att(battle.player);
        battle.skills_bar();
        field.printHLfield(); //non highlighed
        field.printshortcombo();
        field.combobuff_divider();
        field.tile_searching();
        if (field.field_need_emn())
          sleep(2);
      }
    }

    battle.battle(field); //gamestatus will be changged accordingly
    //field.combobuff_reset();
    field.damagebyuser_reset();

    tcflush(STDIN_FILENO, TCIFLUSH);
    if (gamestatus==RUNNING){
      cout << "INPUT 1 to Continue ...\n";
      cout << "INPUT 2 to View the Combo History\n";
      cout << "INPUT 3 to Save and Exit ...\n";
      sleep(1.5);
      string temp;
      cin >> temp;
      char a = temp[0];
      while (!(a == '1' || a == '2' || a == '3') || !(temp.length()==1))
      {
        cout << "WRONG INPUT! WANT TO EXIT WITHOUT SAVING? (E)" << endl;
        cin >> temp;
        if (temp.length()==1)
        {
          a=temp[0];
          if (a == 'E' || a == 'e')
          {
            playerstart = false;
            break;
          }
        }
        else
          a=temp[0];
      }
      if (a == '1')
      {
        cout << "GOOD LUCK" << endl;
        sleep(1);
      }
      else if (a == '3')
      {
        cout << "INPUT NAME OF THIS SAVE (WITHOUT .txt) (Same input filename will lead to overwriting.)" << endl;
        string filename;
        cin >> filename;
        battle.store_MonsterPlayerinfo(filename);
        field.store_field(filename);
        cout << "SUCCESSFULLY STORED" << endl;
        break;
      }
      else if (a == '2'){
        field.printcombobuff();
        tcflush(STDIN_FILENO, TCIFLUSH);
        cout << endl;
        cout << "INPUT 1 to Continue ...\n";
        cout << "INPUT 3 to Save and Exit ...\n";
        sleep(0.5);
        string temp2;
        cin >> temp2;
        char c=temp2[0];
        while (!(c == '1' || c == '3') || !(temp2.length()==1))
        {
          cout << "WRONG INPUT! WANT TO EXIT WITHOUT SAVING? (E)" << endl;
          cin >> temp2;
          if (temp2.length()==1)
          {
            c=temp2[0];
            if (c == 'E' || c == 'e')
            {
              playerstart = false;
              break;
            }
          }
          else
            c=temp2[0];
        }
        if (c == '1')
        {
          cout << "GOOD LUCK" << endl;
          sleep(1);
        }
        else if (c == '3')
        {
          cout << "INPUT YOUR FILE NAME (WITHOUT .txt) (Same input filename will lead to overwriting.)" << endl;
          string filename;
          cin >> filename;
          battle.store_MonsterPlayerinfo(filename);
          field.store_field(filename);
          cout << "SUCCESSFULLY STORED" << endl;
          break;
        }
      }
    }
    field.combobuff_reset();
  }

  if (gamestatus == VICTORY)
  {
    cout << "YOU WIN" << endl;
    ending();
  }

  if (gamestatus == DEFEATED)
  {
    cout << "YOU LOSE" << endl;
  }

  cout << "==GAME ENDED==" << endl;
}

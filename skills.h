#pragma once
#include <string>
#include <iostream>
using namespace std;

struct skill{
  char code;
  string name;
  string description;
  string effect;
  int cd;
  int max_cd;

  void cd_reset(){
    cd = max_cd;
  }
  void skill_colour() const//Input type of skill
  {
  if(effect == "Buff")
    cout << green;
  if(effect == "Nerf")
    cout << yellow;
  if(effect == "Heal")
    cout << blue;
  if(effect == "Damage")
    cout << red;
  if(effect == "Other")
    cout << def;
  }
};

skill skill_1 ={'0',"Stun","[Stun the monster and reduce 50% of monster's damage]","Nerf",5,8};

skill skill_2 = {'1',"Roar","[Attack with rage and double Player's attack]","Buff",6,12};

skill skill_3 = {'2',"Heal","[Heal instantly and restore 30% of Player's max hp]","Heal",3,6};

skill skill_4 = {'3',"Execute","[Execute with a lethal hit and deal damage equal to 30% of monster lost hp]","Damage",8,15};

skill skill_5 = {'4',"Endure","[Endure all damages and become invulnerable by reducing 20% of Player's attack]","Nerf",6,12};

skill skill_6 = {'5',"Punish","[Punish and deal 5000 damage on the monster]","Damage",4,8};

skill skill_7 = {'6',"Pride","[Do nothing]","Other",0,0};

skill skill_8 = {'7',"Pray","[Pray for help and random among 3 effects]\n[1.Mighty blow: Deal 25000 damage]\n[2. God's blessing: Increase Player's attack by 400% and recover 70% of Player's max hp]\n[3. Unheard: Nothing happens]\n[Promised: Revive after death for once]","Other",20,20};

skill skill_9 = {'8',"Counter","[Counter and deal damage equal to 10 times of Player's lost hp]","Damage",8,15};

skill skill_10 = {'9',"Rage","[Battle in rage and increase Player's attack by 250% but 30% more vulnerable to damage]","Buff",9,18};

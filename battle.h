#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <array>
#include <cmath>
#include <iomanip>
#include <sstream>
#include "field.h"
#include "colour.h"
#include "skills.h"

using namespace std;

#define HEART "\xE2\x99\xA5"

enum gamestatus
{
  VICTORY,
  DEFEATED,
  RUNNING
};

gamestatus gamestatus = RUNNING;

const string types[4] = {"HP", "WOOD", "ELECTRIC", "FIRE"};
const string skill_effects[5] = {"Buff","Nerf","Heal","Damage","Other"};
const string Monsters[10] = {"Ant","Bee","Spider","Bat","Snake","Scorpion","Shark","Crocodile","Dragon","Demon"};
const vector< skill > skill_set = {skill_1,skill_2,skill_3,skill_4,skill_5,skill_6,skill_7,skill_8,skill_9,skill_10};
const int max_levels = 10;
int current_level = 1;
int current_round = 1;
double mde = 1;//monster damage effect
double pde = 1;//player damage effect
int skill_dam = 0;//Skill damage
int skill_heal = 0;//Skill heal
int revive = 0; 

struct object//Storing the attributes of monsters/player
{ int max_hp;
  int hp;
  int attack;
  int heal;
  string type;
  vector< skill > Skills;
};

class BattleStatus
{
public:
  object player;
  object monster;
  double mde,pde;
  int type_convert(string);
  void ini_attributes();
  void skill_description(char &);
  bool choose_skill(int);
  void ini_skills();
  void ini_player();
  void display_att(object);
  void spawn_monster();
  double type_multiplier(string, string);
  double subtotal_damage(vector<int>, int);
  double count_combo(Field &);
  double total_damage(Field &, string, int);
  void display_damage(double, string);
  void skill_effect(int);
  void use_skills();
  void battle(Field &);
  void load_MonsterMaxHP(string);
  void load_MonsterHP(string);
  void load_MonsterAttack(string);
  void load_MonsterType(string);
  void load_level(string);
  void load_round(string);
  void load_PlayerMaxHP(string);
  void load_PlayerHP(string);
  void load_PlayerAttack(string);
  void load_PlayerHeal(string);
  void load_revive(string);
  void load_PlayerSkillsCode(string);
  void load_PlayerSkills1Cd(string);
  void load_PlayerSkills2Cd(string);
  void load_PlayerSkills3Cd(string);
  void store_MonsterPlayerinfo(string);
  void display_level();
  void display_round();
  void display_monster();
  void skills_bar();
};

int BattleStatus::type_convert(string type)//Input the type
{ //Convert the type name to a number
  for (int i = 0; i < 5; ++i)
  {
    if (types[i] == type)
    {
      return i;
    }
  }
}
//Output the corresponding index in types[]

//Initiating player
void BattleStatus::ini_attributes()
{//Allocate attribute points
  system("clear");
  int hp,att,heal;
  char action = '.';
  while(action != 'C'){
    int pts = 10;
    cout << "Player Basic Attributes:" << endl;
    cout << "HP:1000   ATTACK:40   HEAL:20" << endl << endl;
    cout << "You have 10 attribute points to allocate" << endl;
    cout << "Enter the number of points you wish to allocate to each attribute" << endl;

    //Allocate hp attribute
    cout << left << setw(16) << "HP(+100/pt)" << " :";
    cin >> hp;
    while(hp>pts){//If allocates more than max
      cout << "[You couldn't allocate " << hp << " attribute points]" << endl;
      cout << left << setw(16) << "HP(+100/pt)" << " :";
      cin >> hp;
    }
    pts-=hp;

    //Allocate attack attribute
    cout << left << setw(16) << "ATTACK(+10/pt)" << " :";
    cin >> att;
    while(att>pts){
      cout << "You couldn't allocate " << att << " attribute points" << endl;
      cout << left << setw(16) << "ATTACK(+10/pt) " << ":";
      cin >> att;
    }
    pts-=att;

    //Allocate heal attribute
    cout << left << setw(16) << "HEAL(+8/pt)" << " :";
    cin >> heal;
    while(heal>pts){
      cout << "You couldn't allocate " << heal << " attribute points" << endl;
      cout << left << setw(16) << "HEAL(+8/pt) " << ":";
      cin >> heal;
    }
    pts-=heal;

  
    if(pts>0){//If remains attribute points
      cout << "You have " << pts << " attribute points left" << endl;     
    }

    player.max_hp = 1000+hp*80;
    player.hp = player.max_hp;
    player.attack = 50+att*10;
    player.heal = 20+heal*8;
    system("clear");
    cout << "Your Current Attributes:" << endl;
    cout << "HP: " << player.hp << "    ATTACK: " << player.attack << "    HEAL: " <<player.heal << endl << endl;
    cout << "Enter C to continue or R to redo the allocation"<<endl;
    cin >> action;
    while(action != 'R'){
      if(action=='C'){
        break;
      }
      else{
        cout << "Enter either C or R" << endl;
      }
      cin >> action;
    }
  }
  system("clear");
}

void BattleStatus::skill_description(char &action)//Input the instruction entered by the player
{//Display skills description
  while(action!='X'){
    cout << "Which skill to do you want to know about?\n(Enter X if you want to exit description)" << endl;
    cin >> action;
    int i = action - '0';
    if(action != 'X'){
      for(int k=0; k<skill_set.size();k++){
        if(i==k){
          skill_set[i].skill_colour();
          cout << skill_set[i].name << " MAX CD: " << skill_set[i].max_cd<<endl;
          cout << def << skill_set[i].description << endl;
          cout <<endl;
          break;
        }
        if(k==(skill_set.size()-1) && i!=k){
          cout << "There is no skill " << i <<endl;
          cout << endl;
          break;
        }
      }
    }
  }
}

bool BattleStatus::choose_skill(int s)
{//Choose availible skills
  char skill;
  cin >> skill;  
  for(int i=0;i<skill_set.size();i++){
    if(s>0){
     for(int j=0; j<s; j++){
       if(skill==player.Skills[j].code){
        cout << "You have this skill already" << endl;
        return true;
       }
     }
    }
    if(skill == skill_set[i].code){
      player.Skills.push_back(skill_set[i]);
      return false;
    }
    if(i == (skill_set.size()-1) && skill != skill_set[-1].code){
      cout << "There is no skill " << skill << endl;
      cout << endl;
      return true;
    }
  }
}
//Output if a choice is made

void BattleStatus::ini_skills()
{// Initiate Player's skills choices
  system("clear");
  char Skill;
  char action = '.';
  cout << "Choose 3 skills from below" << endl;
  for(int i=0;i<skill_set.size();i++){
    skill_set[i].skill_colour();
    cout << skill_set[i].name << "(" << skill_set[i].code << ")  ";
  }
  cout << def << endl << endl;
  while(action != 'X'){
    cout << "Enter D for skills description or P to proceed " << endl;
    cin >> action;
    if(action=='D'){//Read description
      skill_description(action);
    }
    if(action=='P'){
      action = 'X';
    }
  }
  while(action!='C'){//Confirm the 3 choices
    cout << "Choose by entering the corresponding skills code" << endl;
    bool choosing = true;
    while(choosing){
      cout << "Skill A: ";
      choosing = choose_skill(0);
    }
    choosing = true;
    while(choosing){
      cout << "Skill B: ";
      choosing = choose_skill(1);
    }
    choosing = true;
    while(choosing){
      cout << "Skill C: ";
      choosing = choose_skill(2);
    }

    cout << def << "You have chosen :"<<endl;
    for(int i=0;i<player.Skills.size();i++){
      player.Skills[i].skill_colour();
      cout << player.Skills[i].name << "(" << player.Skills[i].code << ")  ";
    }
    cout << def << endl;
    cout << "Enter C to confirm or R to rechoose" << endl;
    cin >> action;
    while((action != 'R')){
      if(action == 'C'){
        break;
      }
      else{
        cout << "Enter either C or R" << endl;
        cin >> action;
      }
    }
    if(action == 'R'){
      player.Skills.clear();
    }
  }
}

void BattleStatus::ini_player()
{ //Initiate player
  ini_attributes();
  ini_skills();
}

void BattleStatus::display_att(object obj)//Input the attributes of player or monster
{//Display attribute of object
  //Display TYPE
  int t = type_convert(obj.type);
  int n = current_level-1;
  switch (t)
  {       //Determine type
  case 1: //WOOD
    cout << green << "WOOD " << Monsters[n] << endl;
    break;
  case 2: //ELECTRIC
    cout << yellow << "ELECTRIC " << Monsters[n] << endl;
    break;
  case 3: //FIRE
    cout << red << "FIRE " << Monsters[n] << endl;
    break;
  default:
    cout << lightblue << "PLAYER" << endl;
  }
  //Display attack
  if(obj.type != ""){
    cout << def << "Attack:" << obj.attack << endl;
  }
  //Display HP
  if (obj.hp <= 0){
    cout << def;
    cout << "HP: 0"
         << "/" << obj.max_hp << endl;
  }
  else
  {
    int hp_percentage = ((obj.hp * 100) / obj.max_hp);
    cout << def<< "HP: ";
    cout << obj.hp << "/" << obj.max_hp << endl;
    string hp_bar = "";
    if (hp_percentage < 10 && hp_percentage >= 0)
    { //HP less than 10%
      hp_bar = HEART;
    }
    else
    {
      for (int i = 0; i < (hp_percentage / 10); i++)
      { //Determine no. of hp bars
        hp_bar += HEART;
      }
    }
    cout << def;
    if ((hp_percentage / 10) > 4)
    { //Healthly
      cout << def << hp_bar << endl;
    }
    else if ((hp_percentage / 10) > 2)
    { //Injured
      cout << lightred << hp_bar << endl;
    }
    else
    { //Dangerous
      cout << red << hp_bar << endl;
    }
  }
  cout << def;
  cout << endl;
}

//Spawning a monster
void BattleStatus::spawn_monster()
{ //Spawning a random monster with random attributes strengthened along levels
  srand(time(NULL));
  monster.hp = (rand()%500)*pow(1.38,(current_level-1))*5 + 6000*pow(1.13,(current_level-1));
  monster.max_hp = monster.hp;
  double attr = (500*pow(1.38,(current_level-1))*5 + 6000*pow(1.13,(current_level-1)))/monster.max_hp;
  monster.attack = ((rand()%40)*current_level*attr)+100*current_level/2;
  monster.type = types[(rand() % 3 + 1)];
}

//Calculating the damages
double BattleStatus::type_multiplier(string monster_type, string damage_type)//Input monster type and type of the damage
{ //Determine the type relationship and the corresponding multiplier to damage
  int monster_type_value = type_convert(monster_type);
  int damage_type_value = type_convert(damage_type);
  int counter = monster_type_value - damage_type_value;
  switch (counter)
  {
  case (0): //Same type
    return 1;
  case (1): //Countering
    return 1.5;
  case (-2): //Countering
    return 1.5;
  case (2): //Being countered
    return 0.85;
  case (-1): //Being countered
    return 0.85;
  default:
    return 0;
  }
}
//Output type multiplier

double BattleStatus::subtotal_damage(vector<int> damage, int attack)//Input result of swapped tiles of a type and player's attack
{ //Calculate the subtotal of damage dealt/hp recovered by an individual type
  int subtotal = 0;
  int number_attacks = damage.size();
  for (int i = 0; i < number_attacks; ++i)
  {
    switch (damage[i])
    {
    case 3:
      subtotal += attack;
    case 4:
      subtotal += attack * 1.15;
    case 5:
      subtotal += attack * 1.3;
    case 6:
      subtotal += attack * 1.7;
    default:
      subtotal = subtotal;
    }
  }
  return subtotal;
}
//Output the subtotal damage of a type

double BattleStatus::count_combo(Field &field)//Input result of swaped tiles
{ //Calculate the combo multiplier
  int combo = field.damage_byuser.wood.size() + field.damage_byuser.electric.size() + field.damage_byuser.fire.size() + field.damage_byuser.hp.size();
  return combo;
}
//Output number of combos

double BattleStatus::total_damage(Field &field, string monster_type, int attack)//Input result of swapped tiles, the monster type and player's attack
{ //Calculate the total damage of all types
  int total = 0;
  total += subtotal_damage(field.damage_byuser.wood, attack) * type_multiplier(monster_type, "WOOD");
  total += subtotal_damage(field.damage_byuser.electric, attack) * type_multiplier(monster_type, "ELECTRIC");
  total += subtotal_damage(field.damage_byuser.fire, attack) * type_multiplier(monster_type, "FIRE");
  double combo = count_combo(field);
  combo = pow(1.15, combo);
  total *= combo;
  return total;
}
//Output total damage dealt

//Battle
void BattleStatus::display_damage(double damage, string type)//Input subtotal damage and the type
{//Display the damage dealt
  int t = type_convert(type);
  cout << def;
  cout << fixed << setprecision(0);
  switch (t)
  {       //Determine type
  case 0: //HP
    cout << lightblue << "+" << damage << "  ";
    cout << def;
    break;
  case 1: //WOOD
    cout << green << "-" << damage << "  ";
    cout << def;
    break;
  case 2: //ELECTRIC
    cout << yellow << "-" << damage << "  ";
    cout << def;
    break;
  case 3: //FIRE
    cout << red << "-" << damage << "  ";
    cout << def;
    break;
  default:
    cout << "" << endl;
  }
}

void BattleStatus::skill_effect(int code)//Input the skill code
{//Effects by each skills
  switch(code){
    case 0:
      cout << "You stunned the monster and it now attacks weaker!" << endl;
      mde *= 0.5;
      break;
    case 1:
      cout << "You roared and gained double strength!" << endl;
      pde *= 2;
      break;
    case 2:
      cout << "You healed yourself " << 0.3*player.max_hp << " !" << endl;
      skill_heal += 0.3*player.max_hp;
      break;
    case 3:
      cout << "You excecuted the monster by " << (monster.max_hp-monster.hp)*0.3 << " !" << endl;
      skill_dam += ((monster.max_hp-monster.hp)*0.3);
      break;
    case 4:
      cout << "You are now invulnerable!" << endl;
      pde *= 0.8;
      break;
    case 5:
      cout << "You punished the monster by 5000 damage !" << endl;
      skill_dam += 5000;
      break;
    case 6:
      cout << "You stood in front of the monster proudly!" << endl;
      break;
    case 7:
      srand(time(NULL));
      int prayer = rand()%3+1;
      switch(rand()%4+1){
        case 1:
          cout << "Your prayer is answered ! A critical hit was dealt !!!" << endl;
          skill_dam += 25000;
          break;
        case 2:
          cout << "Your prayer is heard ! You are now fully enhanced !!" << endl;
          pde *= 4;
          skill_heal += 0.7*player.max_hp;
          break;
        case 3:
          cout << "Your prayer is not heard ..." << endl;
          break;
        case 4:
          cout << "Your prayer is remembered ~" << endl;
          revive = 1;
          break;
        break;
      case 8:
        cout << "You counter attacked and dealt " << (player.max_hp-player.hp)*10 << " damage!" << endl;
        monster.hp-=(player.max_hp-player.hp)*10;
        break;
      case 9:
        cout << "You are now in rage!"<<endl;
        pde *= 2.5;
        mde *= 1.3;
        break;
      }
      break;
  }

}

void BattleStatus::use_skills()
{//Choosing skills to be used
  mde = 1;//Reset monster damage effect
  pde = 1;//Reset player damage effect
  skill_dam = 0;//Reset skill damage
  skill_heal = 0;//Reset skill heal

  for(int i=0;i<3;i++){//Display availible skills
    player.Skills[i].skill_colour();
    cout << "[" << player.Skills[i].name << "("<<player.Skills[i].code << ") CD: ";
    if(player.Skills[i].cd <=0){
      cout << "READY" << "]  ";
    }
    else{
      cout<< player.Skills[i].cd << "]  ";
    }
  }
  cout << def << endl;

  char action = '.';   
  while(action != 'N'){
    cout << "Do you wanna use your skills?(Y/N)" << endl;
    cout << "(Press D for skill description)" << endl;
    cin >> action;
    if(action == 'N'){
      break;
    }
    else if(action =='D'){//Display skill description
      skill_description(action);
    }
    else if(action == 'Y'){//Player wants to use skill
      while(action !='X'){
        cout << "Which skill? (Please enter the code to use or X to exit)" << endl;
        cin >> action;
        if(action =='X'){
          break;
        }
        else{
          for(int i=0;i<3;i++){
            if(action == player.Skills[i].code){//Check if the skill is availible
              if(player.Skills[i].cd>0){//Check if skill requires cd
                cout << player.Skills[i].name << "("<<player.Skills[i].code << ") requires " << player.Skills[i].cd << " more rounds to cool down" << endl;
              }
              else{//Skill is ready
                int x = player.Skills[i].code -'0';
                cout << "You used " << player.Skills[i].name << endl;
                skill_effect(x);
                player.Skills[i].cd_reset();
              }
              break;
            }
            else{//Player doesn't have the skill
              if(i==(player.Skills.size()-1) && action!=player.Skills[player.Skills.size()-1].code){
                cout << "You don't have skill "<< action << endl;
              }
            }
          }
        }
        cout << "Do you want to use another skill?(Y/N)" << endl;
        cin >> action;
        while((action != 'Y')){//Ensure enter correctly
          if(action == 'N'){
            break;
          }
          else{
            cout << "Enter either Y or N" << endl;
            cin >> action;
          }
        }
        if(action == 'N'){//Exit use_skill loop
          break;
        }
      }
      break;
    }
    else{//Entered wrong instruction
      cout << "Please enter either Y(Yes), N(No) or D(Description)" << endl;
    }
  }
}

void BattleStatus::battle(Field &field)//Input the field
{ //Process the battle and proceed
  system("clear");
  for(int i=0;i<3;i++){
    player.Skills[i].cd--;
  }
  cout<<"DAMAGE DEALT"<<endl;
  int combo = count_combo(field);
  double combo_multiplier = pow(1.15, count_combo(field));
  display_damage(subtotal_damage(field.damage_byuser.wood, player.attack) * type_multiplier(monster.type, "WOOD"), "WOOD");
  display_damage(subtotal_damage(field.damage_byuser.electric, player.attack) * type_multiplier(monster.type, "ELECTRIC"), "ELECTRIC");
  display_damage(subtotal_damage(field.damage_byuser.fire, player.attack) * type_multiplier(monster.type, "FIRE"), "FIRE");
  display_damage((subtotal_damage(field.damage_byuser.hp, player.heal) * combo_multiplier), "HP");
  cout << endl;
  cout << combo << "COMBO  x";
  cout << setprecision(3) << combo_multiplier << endl;
  cout << "Skills Effect:" << endl;
  cout << "Attack x" << pde;
  cout << "  Extra Damage " << skill_dam;
  cout << "  Extra Heal " << skill_heal <<endl;
  cout << fixed << setprecision(0) << "TOTAL DAMAGE " << total_damage(field, monster.type, player.attack)*pde + skill_dam << endl;
  cout << endl;

  monster.hp -= total_damage(field, monster.type, player.attack)*pde + skill_dam;//Calculate the remaining hp of the monster
  player.hp += (subtotal_damage(field.damage_byuser.hp, player.heal) * combo_multiplier) + skill_heal; //Calculate hp recovered of player
  player.hp = min(player.hp, player.max_hp);
  display_att(monster);

  if (monster.hp <= 0)
  { //If current monster defeated
    if (current_level == max_levels)
    { //If all levels are completed
      Victory();
      gamestatus = VICTORY;
    }
    else
    { //Proceeds to the next Level
      Next_LV();
      current_level++;
      current_round=1;
      cout << "LEVEL " << current_level << "/10" << endl
           << endl;
      spawn_monster();
      field.printfield();
      display_att(monster);
      gamestatus = RUNNING;
    }
  }
  else
  { //Current monster still alive
    srand(time(NULL));
    int rage = 10*(1.25-monster.hp/(monster.max_hp*4))*pow(1.1,current_level)*pow(1.1,current_round);
    monster.attack += rage;
    player.hp -= monster.attack;

    cout << "DAMAGE TAKEN " << monster.attack << endl;
    cout << endl;
    display_att(player);
    field.printfield();
    if (player.hp <= 0)
    { //Player lost
      if(revive>0){
        revive--;
        cout << "Still remember your prayer?" <<endl;
        cout << "You are revived, continue to save the world!!" << endl;
        player.hp=player.max_hp;
        current_round++;
        gamestatus = RUNNING; 
      }
      else{
        Game_Over();
        gamestatus = DEFEATED;
      }
    }
    else
    { //Proceed to the next round
      current_round++;
      gamestatus = RUNNING;
    }
  }
}


//Save and load
void BattleStatus::load_MonsterMaxHP(string saved)//Input the corresponding line in save file
{//load at 0 line
  stringstream a(saved);
  int b = 0;
  a >> b;
  monster.max_hp = b;
}

void BattleStatus::load_MonsterHP(string saved)//Input the corresponding line in save file
{//load at 1 line
  stringstream a(saved);
  int b = 0;
  a >> b;
  monster.hp = b;
}

void BattleStatus::load_MonsterAttack(string saved)//Input the corresponding line in save file
{//2
  stringstream a(saved);
  int b = 0;
  a >> b;
  monster.attack = b;
}

void BattleStatus::load_MonsterType(string saved)//Input the corresponding line in save file
{//3
  monster.type = saved;
}

void BattleStatus::load_level(string saved)//Input the corresponding line in save file
{
  stringstream a(saved);
  int b = 0;
  a >> b;
  current_level = b;
}

void BattleStatus::load_round(string saved)//Input the corresponding line in save file
{
  stringstream a(saved);
  int b = 0;
  a >> b;
  current_round = b;
}

void BattleStatus::load_PlayerMaxHP(string saved)//Input the corresponding line in save file
{
  stringstream a(saved);
  int b = 0;
  a >> b;
  player.max_hp = b;
}

void BattleStatus::load_PlayerHP(string saved)//Input the corresponding line in save file
{//4
  stringstream a(saved);
  int b = 0;
  a >> b;
  player.hp = b;
}

void BattleStatus::load_PlayerAttack(string saved)//Input the corresponding line in save file
{//4
  stringstream a(saved);
  int b = 0;
  a >> b;
  player.attack = b;
}

void BattleStatus::load_PlayerHeal(string saved)//Input the corresponding line in save file
{//4
  stringstream a(saved);
  int b = 0;
  a >> b;
  player.heal = b;
}

void BattleStatus::load_revive(string saved)
{//4
  stringstream a(saved);
  int b = 0;
  a >> b;
  revive = b;
}

void BattleStatus::load_PlayerSkillsCode(string saved)//Input the corresponding line in save file
{//4
  for(int i=0;i<3;i++){
    char x = saved[i];
    for(int j=0;j<skill_set.size();j++){
      if(x == skill_set[j].code){
        player.Skills.push_back(skill_set[j]);
        break;
      }
    }
  }
}

void BattleStatus::load_PlayerSkills1Cd(string saved)//Input the corresponding line in save file
{
  stringstream a(saved);
  int b = 0;
  a >> b;
  player.Skills[0].cd = b ;
}

void BattleStatus::load_PlayerSkills2Cd(string saved)//Input the corresponding line in save file
{
  stringstream a(saved);
  int b = 0;
  a >> b;
  player.Skills[1].cd = b ;
}

void BattleStatus::load_PlayerSkills3Cd(string saved)//Input the corresponding line in save file
{
  stringstream a(saved);
  int b = 0;
  a >> b;
  player.Skills[2].cd = b ;
}

void BattleStatus::store_MonsterPlayerinfo(string name)//Input the name of save
{
  name.append(".txt");
  ofstream savefile;
  savefile.open(name);
  savefile << monster.max_hp << endl;//0
  savefile << monster.hp << endl;//1
  savefile << monster.attack << endl;//2
  savefile << monster.type << endl;//3
  savefile << current_level << endl;//4
  savefile << current_round << endl;//5
  savefile << player.max_hp << endl;//6
  savefile << player.hp << endl;//7
  savefile << player.attack << endl;//8
  savefile << player.heal << endl;//9
  savefile << revive << endl;//10
  for(int i=0; i<3;i++){
    savefile << player.Skills[i].code;//11
  }
  savefile << endl;
  for(int i=0; i<3;i++){
    savefile << player.Skills[i].cd<<endl; //12,13,14
  }
  savefile.close();
}


//Display
void BattleStatus::display_level()
{
  cout << "CURRENT LEVEL: " << current_level << " /10" << endl;
}

void BattleStatus::display_round()
{
  cout << "Round " << current_round << endl;
}

void BattleStatus::display_monster() //No input
{ switch(current_level)
  {
    case 1:
      level1();
      break;
    case 2:
      level2();
      break;
    case 3:
      level3();
      break;
    case 4:
      level4();
      break;
    case 5:
      level5();
      break;
    case 6:
      level6();
      break;
    case 7:
      level7();
      break;
    case 8:
      level8();
      break;
    case 9:
      level9();
      break;
    case 10:
      level10();
      break;
  }
} //printing the monster graphics

void BattleStatus::skills_bar() //No input
{
  for(int i=0;i<3;i++){//Display availible skills
    player.Skills[i].skill_colour();
    cout << "[" << player.Skills[i].name << "("<<player.Skills[i].code << ") CD: ";
    if(player.Skills[i].cd <=0){
      cout << "READY" << "]  ";
    }
    else{
      cout<< player.Skills[i].cd << "]  ";
    }
  }
  cout << endl;
  cout << endl;
} //printing the skills bar



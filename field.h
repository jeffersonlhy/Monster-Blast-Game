#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <random>
#include <cstring>
#include <time.h>

using namespace std;

#define HP '@'
#define FIRE '%'
#define ELECTRIC '$'
#define WOOD '#'
#define HP_E '^' //matched HP (E = Eliminated)
#define FIRE_E '&'
#define ELECTRIC_E '*'
#define WOOD_E '('
#define BLANK ' '

struct damage
{ //Storing damage dealt per round w.r.t the type of tiles
  vector<int> fire;
  vector<int> wood;
  vector<int> electric;
  vector<int> hp;
};

struct emn_info
{
  string dir;
  int main; //row or column
  int start;
  int end;
};

class Field
{
public:
  //void Field();
  void iniField();                      //initialize the field randomly
  void getMove();                       //change the flag according the the key pressed by the user
  void swap();                          //swap the field
  void printfield();                    //print the field
  bool checkstart();                    //return true if start flag is true
  int horizontalmatch(int, int &, int); //(horizontal matched tiles searching)
  int verticalmatch(int, int &, int);   //(algorithm for searching vertical matched tiles)
  void field_regen();                   //regenerate the matched tiles
  void tile_searching();                //search matching tiles and store in an vector
  void field_elimination();             //change all the matched tiles to " ";
  bool field_need_emn();                //indicate the field has tile to be matched
  void printcombobuff();                //print the combobuffer
  void combobuff_divider();             //add "==ADDITIONAL COMMBO==" to the buff
  void combobuff_reset();               //reset the buff that stores the combo info to be print
  void damagebyuser_reset();            //reset the vector storing the combo info
  void highlight_combo();               //displaying the additional combo
  void start_false();                   //to indicate the player has ended swapping
  void load_field(string);              //load the field from saved file
  void store_field(string);             //store the field to the file to be saved
  void fieldfalling();                  //refersh the map by upadating the field char array
  void printshortcombo();               //printing "X combos" under the tile field
  int combototal();                     //returning the number of combos the player matched
  void printHLfield();                  //print only according to the type of types but not player's choice
  void printinstruction();              //printing instruction
private:
  friend class BattleStatus;
  char field[5][6];
  int x = 0;                            //the location of tile that the user is currently choosing 
  int y = 0;                            //the location of tile that the user is currently choosing
  int x_start = 0;                      //the location of tile that the user is currently choosing after ENTER is clicked (starts swapping)
  int y_start = 0;                      //the location of tile that the user is currently choosing after ENTER is clicked (starts swapping)

  bool up = false;                
  bool down = false;
  bool left = false;
  bool right = false;
  bool start = false;
  bool need_emn = false;
  vector<string> combobuffer;           //Date Structure for storing the combo info so that it could be displayed for the player as a reference (dynamically in a vector)
  vector<emn_info> info;                //Date Structure for storing the tiles' elimination info (dynamically in a vector)
  damage damage_byuser;                 //Data Structure for storing the combo info for further damage calculation (dynamically stored in four vectors (HP, FIRE, WOOD, ELECTRIC) respectively)
};

void Field::getMove() //taking users' key pressed as input by calling getKey() declared in setup.h
{
  char k = getKey();
  switch (k)
  {
  case K_UP:
    if (y && !start)
    {      //case of before clicking enter (before choosing the first tile)
      --y; //record the current y;
    }
    if (start)
    { //case of after enter is clicked (first tile is choosen)
      if (y_start)
      { //y_start != 0
        up = true;
        --y_start;
      }
    }
    break;
  case K_DOWN:
    if (y <= 3 && !start)
    {
      ++y;
    }
    if (start)
    {
      if (y_start <= 3)
      {
        down = true;
        ++y_start;
      }
    }
    break;
  case K_LEFT:
    if (x && !start)
    {
      --x;
    }
    if (start)
    {
      if (x_start)
      {
        left = true;
        --x_start;
      }
    }
    break;
  case K_RIGHT:
    if (x <= 4 && !start)
    {
      ++x;
    }
    if (start)
    {
      if (x_start <= 4)
      {
        right = true;
        ++x_start;
      }
    }
    break;
  case K_ENTER:
    //cout << "enter clicked" << endl;
    if (!start)
    { //prevent cases of users clicking enter when enter is already pressed;
      start = true;
      x_start = x;
      y_start = y;
    }
    break;
  }
} //update up, down, left, right flag respectively and x_start & y_start if users starts swapping, otherwise update x & y only

void Field::iniField() 
{ //initializing the field
  const char fieldelement[4] = {HP, WOOD, ELECTRIC, FIRE};
  srand(time(NULL));
  for (int y = 0; y < 5; ++y)
  {
    for (int x = 0; x < 6; ++x)
    {
      field[y][x] = fieldelement[rand() % 4];
    }
  }
  tile_searching();
  while (field_need_emn()) //prevent >3 tiles in a row at the beginning
  {
    field_elimination();
    field_regen();
    tile_searching();
  }
  damagebyuser_reset();
  combobuff_reset();
} //initializing the char array

void Field::swap() //Input: Base on which flag is true and do the swapping accordingly
{
  if (up)
  {
    if (y_start >= 0)
    {
      char temp = field[y_start][x_start];
      field[y_start][x_start] = field[y_start + 1][x_start];
      field[y_start + 1][x_start] = temp;
    }
  }
  else if (down)
  {
    if (y_start <= 4)
    {
      char temp = field[y_start][x_start];
      field[y_start][x_start] = field[y_start - 1][x_start];
      field[y_start - 1][x_start] = temp;
    }
  }
  else if (left)
  {
    if (x_start >= 0)
    {
      char temp = field[y_start][x_start];
      field[y_start][x_start] = field[y_start][x_start + 1];
      field[y_start][x_start + 1] = temp;
    }
  }
  else if (right)
  {
    if (x_start <= 5)
    {
      char temp = field[y_start][x_start];
      field[y_start][x_start] = field[y_start][x_start - 1];
      field[y_start][x_start - 1] = temp;
    }
  }
  up = false;
  down = false;
  left = false;
  right = false;
} //updating the field as a result of swaping

void Field::printfield() //Input: the field char array
{
  if (start)
  {
    for (int i = 0; i < 5; ++i)
    {
      for (int j = 0; j < 6; ++j)
      {
        switch (field[i][j])
        {
        case HP:
          if (i == y_start && j == x_start)
            cout << setw(12) << lightblue_chosen << field[i][j] << reset;
          else
            cout << setw(9) << lightblue << field[i][j] << reset;
          break;
        case FIRE:
          if (i == y_start && j == x_start)
            cout << setw(12) << red_chosen << field[i][j] << reset;
          else
            cout << setw(9) << red << field[i][j] << reset;
          break;
        case ELECTRIC:
          if (i == y_start && j == x_start)
            cout << setw(12) << yellow_chosen << field[i][j] << reset;
          else
            cout << setw(9) << yellow << field[i][j] << reset;
          break;
        case WOOD:
          if (i == y_start && j == x_start)
            cout << setw(12) << green_chosen << field[i][j] << reset;
          else
            cout << setw(9) << green << field[i][j] << reset;
          break;
        }
      }
      cout << endl;
    }
  }
  else
  {
    for (int i = 0; i < 5; ++i)
    {
      for (int j = 0; j < 6; ++j)
      {
        switch (field[i][j])
        {
        case HP:
          if (i == y && j == x)
            cout << setw(12) << lightblue_chosen << field[i][j] << reset;
          else
            cout << setw(9) << lightblue << field[i][j] << reset;
          break;
        case FIRE:
          if (i == y && j == x)
            cout << setw(12) << red_chosen << field[i][j] << reset;
          else
            cout << setw(9) << red << field[i][j] << reset;
          break;
        case ELECTRIC:
          if (i == y && j == x)
            cout << setw(12) << yellow_chosen << field[i][j] << reset;
          else
            cout << setw(9) << yellow << field[i][j] << reset;
          break;
        case WOOD:
          if (i == y && j == x)
            cout << setw(12) << green_chosen << field[i][j] << reset;
          else
            cout << setw(9) << green << field[i][j] << reset;
          break;
        case HP_E:
          cout << setw(13) << lightblue_highlight << HP << reset;
          break;
        case FIRE_E:
          cout << setw(13) << red_highlight << FIRE << reset;
          break;
        case ELECTRIC_E:
          cout << setw(13) << yellow_highlight << ELECTRIC << reset;
          break;
        case WOOD_E:
          cout << setw(13) << green_highlight << WOOD << reset;
          break;
        }
      }
    cout << endl;
    }
  }
} //printing the tile field

bool Field::checkstart() //Input: the "start" flag
{
  if (start)
  {
    return true;
  }
  else
    return false;
} //Return true if "start" flag is true

int Field::horizontalmatch(int i, int &j, int count) //Input the row position (i), column position (j) which will be altered, and count variable
{
  if (j == 5)
  {
    return count;
  }
  if (field[i][j + 1] != field[i][j])
  {
    j++;
    return count;
  }
  if (field[i][j + 1] == field[i][j])
  {
    if (j == 4)
    { //second last 2 tile
      count += 1;
      j += 2; //return j=6 for storing info
      return count;
    }
    else
    {
      j++;
      count += 1;
      horizontalmatch(i, j, count);
    }
  }
} //Recursive function that returns the number of count of tiles locating togther (horizontal) and also the new column position when the next horizontal tile does not match the previous one 

int Field::verticalmatch(int i, int &j, int count) //Input the column position (i), row position (j) which will be altered, and count variable
{
  if (j == 4)
  {
    return count;
  }
  if (field[j + 1][i] != field[j][i])
  {
    j++;
    return count;
  }
  if (field[j + 1][i] == field[j][i])
  {
    if (j == 3)
    {
      j += 2; //return j=5 if last 3 vertical element matchs
      count += 1;
      return count;
    }
    else
    {
      j++;
      count += 1;
      verticalmatch(i, j, count);
    }
  }
} //Recursive function that returns the number of count of tiles locating togther (vertical) also the new column position when the next horizontal tile does not match the previous one 

//Both function will only be called within the tile_searching function for searching the tile that can be matched and eliminated 

void Field::tile_searching() //Input: the information in the field char array
{
  //horizontal searching
  for (int i = 0; i < 5; ++i)
  {
    int j = 0;
    while (j < 5)
    {
      int count = horizontalmatch(i, j, 1);
      if (count >= 3) //three or more in a row
      {
        //storing the info for elimination
        need_emn = true;
        emn_info temp;
        temp.dir = "x";
        temp.main = i;
        temp.start = j - count;
        temp.end = j - 1;
        info.push_back(temp);
        /*cout << "x " << temp.start << " "
             << temp.end << endl;*/
        string strr;
        //storing the info for calculating damage w.r.t the type
        switch (field[i][j - 1])
        {
        case HP:
          damage_byuser.hp.push_back(count);
          strr.append("+1 HORIZONTAL COMBO (");
          strr.append(to_string(count));
          strr.append(" ");
          strr.append(lightblue);
          strr.append("@");
          strr.append(reset);
          strr.append(" MATCHED)");
          strr.append("\n");
          combobuffer.push_back(strr);
          break;
        case FIRE:
          damage_byuser.fire.push_back(count);
          strr.append("+1 HORIZONTAL COMBO (");
          strr.append(to_string(count));
          strr.append(" ");
          strr.append(red);
          strr.append("%");
          strr.append(reset);
          strr.append(" MATCHED)");
          strr.append("\n");
          combobuffer.push_back(strr);
          break;
        case ELECTRIC:
          damage_byuser.electric.push_back(count);
          strr.append("+1 HORIZONTAL COMBO (");
          strr.append(to_string(count));
          strr.append(" ");
          strr.append(yellow);
          strr.append("$");
          strr.append(reset);
          strr.append(" MATCHED)");
          strr.append("\n");
          combobuffer.push_back(strr);
          break;
        case WOOD:
          damage_byuser.wood.push_back(count);
          strr.append("+1 HORIZONTAL COMBO (");
          strr.append(to_string(count));
          strr.append(" ");
          strr.append(green);
          strr.append("#");
          strr.append(reset);
          strr.append(" MATCHED)");
          strr.append("\n");
          combobuffer.push_back(strr);
          break;
        }
      }
    }
  }

  //vertical searching
  for (int i = 0; i < 6; ++i)
  {
    int j = 0;
    while (j < 4)
    {
      int count = verticalmatch(i, j, 1);
      if (count >= 3)
      {
        //storing info for elimination
        need_emn = true;
        emn_info temp;
        temp.dir = "y";
        temp.main = i;
        temp.start = j - count;
        temp.end = j - 1;
        info.push_back(temp);
        /*cout << "y " << temp.start << " "
             << temp.end << endl;*/
        string strr;
        //storing combo info for calculating damage w.r.t the type
        switch (field[j - 1][i])
        {
        case HP:
          damage_byuser.hp.push_back(count);
          strr.append("+1 VERTICAL COMBO (");
          strr.append(to_string(count));
          strr.append(" ");
          strr.append(lightblue);
          strr.append("@");
          strr.append(reset);
          strr.append(" MATCHED)");
          strr.append("\n");
          combobuffer.push_back(strr);
          break;
        case FIRE:
          damage_byuser.fire.push_back(count);
          strr.append("+1 VERTICAL COMBO (");
          strr.append(to_string(count));
          strr.append(" ");
          strr.append(red);
          strr.append("%");
          strr.append(reset);
          strr.append(" MATCHED)");
          strr.append("\n");
          combobuffer.push_back(strr);
          break;
        case ELECTRIC:
          damage_byuser.electric.push_back(count);
          strr.append("+1 VERTICAL COMBO (");
          strr.append(to_string(count));
          strr.append(" ");
          strr.append(yellow);
          strr.append("$");
          strr.append(reset);
          strr.append(" MATCHED)");
          strr.append("\n");
          combobuffer.push_back(strr);
          break;
        case WOOD:
          damage_byuser.wood.push_back(count);
          strr.append("+1 VERTICAL COMBO (");
          strr.append(to_string(count));
          strr.append(" ");
          strr.append(green);
          strr.append("#");
          strr.append(reset);
          strr.append(" MATCHED)");
          strr.append("\n");
          combobuffer.push_back(strr);
          break;
        }
      }
    }
  }
} //Update the damage_byuser, eliminiation_info (emn_info) and also the combo buffer  

void Field::field_elimination() //Input: emn_info
{

  /*//x elimination
  for (int i = 0; i < info[0].size(); ++i)
  {
    for (int j = info[0][i].start; j <= info[0][i].end; ++j)
    {
      field[info[0][i].main][j] = ' ';
    }
  }
  //y elimination
  for (int i = 0; i < info[1].size(); ++i)
  {
    for (int j = info[1][i].start; j <= info[1][i].end; ++j)
    {
      field[j][info[1][i].main] = ' ';
    }
  }*/
  // info = {{x,1,1,4},{y,1,2,4}}
  for (int i = 0; i < info.size(); ++i)
  {
    if (info[i].dir == "x")
    {
      for (int j = info[i].start; j <= info[i].end; ++j)
      {
        switch (field[info[i].main][j])
        {
        case HP:
          field[info[i].main][j] = HP_E;
          break;
        case FIRE:
          field[info[i].main][j] = FIRE_E;
          break;
        case ELECTRIC:
          field[info[i].main][j] = ELECTRIC_E;
          break;
        case WOOD:
          field[info[i].main][j] = WOOD_E;
          break;
        case HP_E:
          field[info[i].main][j] = HP_E;
          break;
        case FIRE_E:
          field[info[i].main][j] = FIRE_E;
          break;
        case ELECTRIC_E:
          field[info[i].main][j] = ELECTRIC_E;
          break;
        case WOOD_E:
          field[info[i].main][j] = WOOD_E;
          break;
        }
      }
    }
    else
    {
      for (int j = info[i].start; j <= info[i].end; ++j)
      {
        switch (field[j][info[i].main])
        {
        case HP:
          field[j][info[i].main] = HP_E;
          break;
        case FIRE:
          field[j][info[i].main] = FIRE_E;
          break;
        case ELECTRIC:
          field[j][info[i].main] = ELECTRIC_E;
          break;
        case WOOD:
          field[j][info[i].main] = WOOD_E;
          break;
        case HP_E:
          field[j][info[i].main] = HP_E;
          break;
        case FIRE_E:
          field[j][info[i].main] = FIRE_E;
          break;
        case ELECTRIC_E:
          field[j][info[i].main] = ELECTRIC_E;
          break;
        case WOOD_E:
          field[j][info[i].main] = WOOD_E;
          break;
        }
      }
    }
  }

  info.clear();
  need_emn = false;
} //Updating the field char array by replacing the tiles matched with specified symbols (will not be displayed)

void Field::field_regen() //Input: the field char array
{
  const char fieldelement[4] = {HP, WOOD, ELECTRIC, FIRE};
  srand(time(NULL));
  for (int y = 0; y < 5; ++y)
  {
    for (int x = 0; x < 6; ++x)
    {
      if (field[y][x] == HP_E || field[y][x] == WOOD_E || field[y][x] == ELECTRIC_E || field[y][x] == FIRE_E)
        field[y][x] = fieldelement[rand() % 4];
    }
  }
} //Updating the field char array by regenerating the eliminated items

bool Field::field_need_emn() //the need_emn flag
{
  if (need_emn)
    return true;
  else
    return false;
} //return true/false with respect to the flag

void Field::printcombobuff() //Input: combobuffer
{
  for (auto it : combobuffer)
  {
    cout << it;
  }
  if (combobuffer.size()>=1 && combobuffer[combobuffer.size() - 1] == "==ADDITIONAL COMBO==\n")
  {
    cout << setw(14) << "NONE\n";
  }
} //printing the combobuffer

void Field::combobuff_divider()//Input: NONE
{
  combobuffer.push_back("==ADDITIONAL COMBO==\n");
} //Updating the combobuffer by adding "==ADDITIONAL COMBO==" to clearer styling 

void Field::combobuff_reset() //Input: combobuffer
{
  combobuffer.clear();
} //clearing the combobuffer

void Field::damagebyuser_reset() //Input:: damage_byuser
{
  damage_byuser.hp.clear();
  damage_byuser.wood.clear();
  damage_byuser.electric.clear();
  damage_byuser.fire.clear();
} //clearing the dmaage_byuser

void Field::start_false() //Input "start" flag
{
  start = false;
}//return correspondingly 

void Field::load_field(string savedfield) //string of the information in the savedfile
{
  char a [60];
  strcpy(a, savedfield.c_str());
  int j=0;
  while (j<60)
  {
    field[j/12][(j%12)/2]=a[j];
    j+=2;
  }

} //update the field with the datat stored in the loadfile

void Field::store_field(string name) //string of the save file name
{
 ofstream savefile;
 name.append(".txt");
 savefile.open(name, ios::app);
 for (int i=0; i<5; ++i){
   for (int j=0; j<6; ++j){
     savefile << field[i][j];
     if (i!=4 || j!=5){
      savefile << " ";
     }
   }
 }
 savefile.close();
} //write the field info to the save file

void Field::fieldfalling() //Input: field char array
{
  for (int i=0; i<6; ++i)
  {
    vector<char> e;
    vector<char> t;
    for (int j=0; j<5; ++j)
    {
      if (field[j][i]==FIRE_E || field[j][i]==ELECTRIC_E || field[j][i]==HP_E || field[j][i]==WOOD_E)
      {
        e.push_back(field[j][i]);
      }
      else 
        t.push_back(field[j][i]);
    }
    int index_count = 0;
    for (int k =0; k<e.size(); ++k)
    {
      field[index_count][i] = e[k];
      index_count+=1;
    }
    for (int p=0; p<t.size(); ++p)
    {
      field[index_count][i] = t[p];
      index_count +=1;
    }
    e.clear();
    t.clear();
  }
} //updating the field by letting the field not eliminated to "fall"

void Field::printshortcombo() //Input: damage_byuser
{
  if (combototal()==1)
    cout << to_string(combototal()) << " COMBO" << endl;
  else if (combototal()==0)
    cout << "NO COMBO DONE" << endl;
  else if (1<combototal() && combototal() <=5)
    cout << green << to_string(combototal()) << reset << " COMBOS" << endl;
  else if (5<combototal() && combototal() <=7)
    cout << lightred << to_string(combototal()) << reset << " COMBOS" << endl;
  else if (7<combototal() && combototal() <=9)
    cout << red << to_string(combototal()) << reset << " COMBOS" << endl;
  else
    cout << red_chosen << to_string(combototal()) << reset << " COMBOS" << endl; 
} //printing "x combo" for x subject to the combo that the users matched

int Field::combototal() //Input: damage_byuser
{
  int t=damage_byuser.hp.size()+damage_byuser.fire.size()+damage_byuser.electric.size()+damage_byuser.wood.size();
  return t;
} //outputing how many combo the user made

void Field::printHLfield() //Input: field char array
{
  for (int i = 0; i < 5; ++i)
    {
      for (int j = 0; j < 6; ++j)
      {
        switch (field[i][j])
        {
        case HP:
            cout << setw(9) << lightblue << field[i][j] << reset;
          break;
        case FIRE:
            cout << setw(9) << red << field[i][j] << reset;
          break;
        case ELECTRIC:
            cout << setw(9) << yellow << field[i][j] << reset;
          break;
        case WOOD:
            cout << setw(9) << green << field[i][j] << reset;
          break;
        case HP_E:
          cout << setw(13) << lightblue_highlight << HP << reset;
          break;
        case FIRE_E:
          cout << setw(13) << red_highlight << FIRE << reset;
          break;
        case ELECTRIC_E:
          cout << setw(13) << yellow_highlight << ELECTRIC << reset;
          break;
        case WOOD_E:
          cout << setw(13) << green_highlight << WOOD << reset;
          break;
        }
      }
    cout << endl;
    }
} //print field only with respect to the types of tiles

void Field::printinstruction()//Input: None
{
  cout << endl;
  cout << endl;
  cout << "Use ↑ ↓ → ← to choose where to start. Press Enter to confirm." << endl;
  cout << endl;
  cout << "After Enter is pressed, you will have 7 seconds to do swapping." << endl;
} //printing the instruction
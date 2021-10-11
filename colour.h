#pragma once
#include <string>
#include <iostream>
using namespace std;

//text color changed
std::string def = "\033[0;39m";
std::string red = "\033[0;31m"; //10 characters
std::string green = "\033[0;32m";
std::string yellow = "\033[0;33m";
std::string lightblue = "\033[0;34m";
std::string lightred = "\033[0;91m";
//highlight & bold
std::string red_chosen = "\033[1;97;41m"; //13 characters
std::string green_chosen = "\033[1;97;42m";
std::string yellow_chosen = "\033[1;97;43m";
std::string lightblue_chosen = "\033[1;97;44m";
//Grey highlight with respective colour
std::string red_highlight = "\033[1;31;100m";
std::string green_highlight = "\033[1;32;100m";
std::string yellow_highlight = "\033[1;33;100m";
std::string lightblue_highlight = "\033[1;34;100m";
std::string reset = "\033[0m";

std::string white_solid = "\033[0;97m";
std::string lightred_solid = "\033[0;91m";
std::string red_solid = "\033[0;31m";

std::string blue_chosen = "\033[1;97;34m";
std::string blue = "\033[0;97;34m";
std::string magenta_highlight = "\033[0;97;35m";
std::string cyan_highlight = "\033[0;97;36m";

/*"\033[{FORMAT_ATTRIBUTE};
{FORGROUND_COLOR};
{BACKGROUND_COLOR}m
{TEXT}
\033[{RESET_FORMATE_ATTRIBUTE}m"*/

//FORMAT_ATTRIBUTE
/*{ "Default", "0" },
{ "Bold", "1" },
{ "Dim", "2" },
{ "Underlined", "3" },
{ "Blink", "5" },
{ "Reverse", "7" },
{ "Hidden", "8" }*/

//FORGROUND_COLOR
/*{ "Default", "39" },
{ "Black", "30" },
{ "Red", "31" },
{ "Green", "32" },
{ "Yellow", "33" },
{ "Blue", "34" },
{ "Magenta", "35" },
{ "Cyan", "36" },
{ "Light Gray", "37" },
{ "Dark Gray", "90" },
{ "Light Red", "91" },
{ "Light Green", "92" },
{ "Light Yellow", "93" },
{ "Light Blue", "94" },
{ "Light Magenta", "95" },
{ "Light Cyan", "96" },
{ "White", "97" }*/

//BACKGROUND_COLOR
/*{ "Default", "49" },
{ "Black", "40" },
{ "Red", "41" },
{ "Green", "42" },
{ "Yellow", "43" },
{ "Blue", "44" },
{ "Megenta", "45" },
{ "Cyan", "46" },
{ "Light Gray", "47" },
{ "Dark Gray", "100" },
{ "Light Red", "101" },
{ "Light Green", "102" },
{ "Light Yellow", "103" },
{ "Light Blue", "104" },
{ "Light Magenta", "105" },
{ "Light Cyan", "106" },
{ "White", "107" }*/

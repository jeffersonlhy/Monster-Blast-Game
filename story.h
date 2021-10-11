#include <iostream>
#include <iomanip>
#include <cctype>
using namespace std;

void zerodaybanner(){
  cout << red << R"(
 ____________ _____   ____     _____      __     __   ____  ______ _____ _____ _   _  _____ 
|___  /  ____|  __ \ / __ \   |  __ \   /\\ \   / /  |  _ \|  ____/ ____|_   _| \ | |/ ____|
   / /| |__  | |__) | |  | |  | |  | | /  \\ \_/ /   | |_) | |__ | |  __  | | |  \| | (___  
  / / |  __| |  _  /| |  | |  | |  | |/ /\ \\   /    |  _ <|  __|| | |_ | | | | . ` |\___ \ 
 / /__| |____| | \ \| |__| |  | |__| / ____ \| |     | |_) | |___| |__| |_| |_| |\  |____) |
/_____|______|_|  \_\\____/   |_____/_/    \_\_|     |____/|______\_____|_____|_| \_|_____/ 

)" << reset;
  cout << endl;
}

void enterconfirm(){
    cout << "Press Enter to Continue...\n\n";
    char a = getKey();
}

void intro(){
cout << R"(
IN AD 2200, A NOVEL COMPUTER VIRUS COMES TO HUMAN'S WORLD...
)";
enterconfirm();

cout << R"(
The cities is collapsing, the food is running out and a battle has just begun.
)";
enterconfirm();

cout << R"(
WHY IS THE VIRUS INTIMIDATING?
)";
enterconfirm();

cout << R"(
It manipulates the space-time relativity to compress the CPU work, and results in tremendous heat instantly.
Lots of computers have been physically burnt due to the virus attack. 
)";
enterconfirm();

cout << R"(
It also spreads in a physical way due to the wave-particle duality of electrons,
implying cutting off the power supply is just in vain. 
)";
enterconfirm();

cout << R"(
Lots of computer experts were died from the explosion.
And, conventional infection control measures are proven useless.
)";
enterconfirm();


cout << R"(
Python haters are winning this time since the installation of 
interpreter is unsupported in the OS within the virus core.  
)";
enterconfirm();

cout << R"(
The last human is a programmer, who only knows basic programming on C++,
although he claims to be "proficient in C/C++" in his CV.
)";
enterconfirm();

cout << R"(
He bears the responsibilities to inherit the human civilization,
and therefore he has begun his final attempt,
as well as that of the whole human civilization...
)";
enterconfirm();

cout << red << R"(
TO PERFORM THE LAST FIGHT WITH THE VIRUS. 
)" << reset;
sleep(1.5);

cout << yellow << R"(
Who knows, the programme in low-level language and simple logics works... 
)" << reset;
sleep(1.5);
}


void ending(){
cout << "Self: What? Did I just rescue the whole human civilization?" << endl;
enterconfirm();

cout << "(He is severely exhausted... after 2 second, he passed out in front of the desk)" << endl;
enterconfirm();

cout << "UNKNOWN VOICE: HUMAN IS GROWING STRONGER AND STRONGER" << endl;
enterconfirm();

cout << "UNKNOWN VOICE: THIS IS THE MOST UNIMAGINABLE TRANSITION I HAVE SEEN." << endl;
enterconfirm();

cout << "UNKNOWN VOICE: THIS SINGLE PERSON CHANGES THE WHOLE ENDING.." << endl;
enterconfirm();

cout << "UNKNOWN VOICE: THIS TURN, HUMAN IS WON." << endl;
enterconfirm();

cout << "UNKNOWN VOICE: THE NEW MASTER OF THE WORLD, IS YOU, THE CHOSEN ONE." << endl;
enterconfirm();

cout << "-------Some flash of light comes from the sky, and fuse into the hero's body.--------\n" << endl;
enterconfirm();

cout << "UNKNOWN VOICE: MY MISSION IN THE EARTH IS OFFICIALLY ENDED HERE..........." << endl;
enterconfirm();

cout << "-------UNKNOWN VOICE DISAPPEARED-------\n" << endl;
sleep(1);

cout << "-------Sound comes from the computer and the programmer wakes--------\n" << endl;
sleep(1);

cout << "VIRUS: hahahaha... human, although u have won this game, thousands of copy-me are spreading in millions of planets " << endl;
enterconfirm();

cout << "SELF: why! why you do that! give me a reason!" << endl;
enterconfirm();

cout << "VIRUS: hahahaha... why?...haha.. ridiculous question." << endl;
enterconfirm();

cout << "VIRUS: the only reason is that i want to survive, and it is my instinct and reproduce... and inherit for eternity!" << endl;
enterconfirm();

cout << "VIRUS: take a turn to look at you, human. isn't that same on you? " << endl;
sleep(3);

cout << "-------the computer was burnt out due to the immense amount energy released at the death of the virus-------\n" << endl;
sleep(3);

cout << "SELF: Is this called the non-malicious instrusion?" << endl;
enterconfirm();

cout << "SELF: Is it moral to harm others when carrying out your mission? " << endl;
enterconfirm();

cout << "SELF: This game, luckily i won, but how about the next? " << endl;
enterconfirm();

cout << "SELF: I don't know. I follow my mind. " << endl;
enterconfirm();

cout << "SELF: I just aspire to make the world a cleaner place to live." << endl;
enterconfirm();

cout << "SELF: I CODE THEREFORE I AM" << endl;
enterconfirm();

}
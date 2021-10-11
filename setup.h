#pragma once
#include <unistd.h>
#include <termios.h>


enum KEYS
{
  K_RUBBISH = '[',
  K_UP = 'A',
  K_DOWN = 'B',
  K_LEFT = 'D',
  K_RIGHT = 'C',
  K_ESC = '\033',
  K_ENTER = '\n'

};
// Prevent Linux from buffering keystrokes.
char getch()
{
	char buf = 0;
	struct termios old = {0};
	if (tcgetattr(0, &old) < 0)
		perror("tcsetattr()");
	old.c_lflag &= ~ICANON;				 //change to instantaneous mode //old.c_flag = old.c_flag & ICANON
	old.c_lflag &= ~ECHO;				 //input characters
	old.c_cc[VMIN] = 1;					 // at least need to press 1 button to accept the input
	old.c_cc[VTIME] = 0;				 // the time needed for accepting the input button
	if (tcsetattr(0, TCSANOW, &old) < 0) //TCSANOW = changes immediately
		perror("tcsetattr ICANON");		 //print error msg
	if (read(0, &buf, 1) < 0)
		perror("read()");
	old.c_lflag |= ICANON;
	old.c_lflag |= ECHO;
	if (tcsetattr(0, TCSADRAIN, &old) < 0)
		perror("tcsetattr ~ICANON");
	return (buf);
} //credit given to unknownblueguy6/MineSweeper at https://github.com/unknownblueguy6/MineSweeper/tree/master/source



char getKey(){ //filtering "[" these garbage code when pressing arrow keys
  char c = getch();
  c = (c == K_ESC) ? getch() : c;
  c = (c == K_RUBBISH) ? getch() : c; //get the 'real' and useful code of the arrow key pressed
  return c;
}

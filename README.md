# Monster Blast Game

## Game description
Monster Blast a tile matching game. The ZERO day unveiled by the advance of a novel computer virus with AI-capabilities in AD 2030. You, the last programmer who survives, bears the responsibilities to inherit human civilization by fighting with the virus by defeating all the monsters. 

### Goal of the game:
Defeat all levels of monsters by matching at least 3 tiles a line to deal damage to monsters without being killed by the monsters.

### Rules
The core game challenge is composed by the ten levels of monsters with randomized type, HP and ATTACK. Firstly, player can choose whether to use the skills chosen at the beginning at each round. Then, player can choose the starting tile freely by using arrow keys. After clicking Enter to start swapping, the 7-second timelimit will start to count down. Then, tiles will be eliminated and combos will be counted automatically whenever more than 3 tiles with same type are arranged horizontally or vertically. Lastly, the tiles eliminated will be regenerated randomly. The monster will attack the player each round completed swapping. 

### Tiles:
@=HP
%=FIRE
#=WOOD
$=ELECTRIC
Counter: FIRE > WOOD > ELECTRIC > FIRE > WOOD ... (in a cycle)



## Usage

**1. Clone the repository.**
```
$ git clone https://@github.com/jeffersonlhy/monster-blast-game.git
```

**2. Build the file using make command**
```bash
$ make
```

**3. Start the game**
```bash
$ ./tilegame
```


### General Description:
- "field.h" develops mainly the functions in the field operation such as searching, elimination, regeneration, printing
- "battle.h" includes mainly the battle mechanism like the attributes of Monsters and Player.
- "skills.h" includes the skills that are available for the player.
- "story.h" includes the function for displaying the introduction and ending of the story plot.
- "setup.h" includes the function for preventing linux from buffering keystrokes.
- "display.h" includes the functions for displaying the monster graphics.
- "colour.h" includes the functions for styling.
- "main.cpp" includes all the header files mentioned above.
These matches the code requirement 5. 

    
 

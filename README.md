# Lab5_Game
=========

## Basic Idea

implements a simple game using interrupts to detect button pushes on MSP430.

##Functions:

- 'unsigned char gameOver(unsigned char  player);'
	- displays "Game Over!" on the screen.
	- returns the value of initPlayer() to reset player value/

- 'unsigned char initPlayer();'
	- returns the value 0x80, the first spot on the LCD
	
- 'void printPlayer(unsigned char player);'
	- prints the game piece "*" to the screen
	- position is designated by player

- 'void clearPlayer(unsigned char player);'
	- similar to printPlayer, but prints " " instead.

- 'unsigned char movePlayer(unsigned char player, unsigned char direction);'
	- uses case staments to direct direction of game piece
	- returns the new position and prints it

- 'unsigned char youWon(unsigned char player);'
	- returns initPlayer to reinitalize the game piece.
	- writes "you won!!" to lcd

- 'void clearScreen();'
	- blanks the screen so that something new can be written. 

- 'void testAndRespondToButtonPush(char buttonToTest)'
	- debounces buttons
	- written by Capt Branchflower
 
- 'void init_timer()'
	- initialized Timer_A on MSP430.
	
- 'void init_buttons()'
	-initalized buttons on MSP430.



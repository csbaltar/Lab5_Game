#include <msp430g2553.h>
#include "game.h"
#include "../LCD/LCD.h"
#include "../buttons/button.h"

#define True = 0x1
#define False = 0x0

char you[]="You";
char won[]="Won!!";
char game[]="Game";
char over[]="Over!";
char boom[]="boom";

unsigned char initPlayer()
{
	return 0x80;
}

void printPlayer(unsigned char player)
{
	writeCommandByte(player);
	writeDataByte('*');
}

void clearPlayer(unsigned char player)
{
	writeCommandByte(player);
	writeDataByte(' ');
}



unsigned char movePlayer(unsigned char player, unsigned char direction)
{

	switch (direction) {
		//
		// update player position based on direction of movement
		//
	case UP:		//UP
		if (0xc0<=player<=0xc7)
			{
				player = 0x80+(player&0x0f);
				printPlayer(player);
			}
		break;

	case DOWN:		//DOWN
		if (0x80<=player<=0x87)
			{
				player = 0xC0+(player&0x0f);
				didPlayerWin(player);
				printPlayer(player);
			}

		break;

	case LEFT:		//LEFT
		if (player != 0xc0|0x80)
				{
					player = player--;
					printPlayer(player);
				}
		if(player == 0xc0)
		{
			player = 0x87;
			printPlayer(player);
		}
		break;

	case RIGHT:		//RIGHT
		if (player != 0xc7|0x87)
			{
				player = player++;
				didPlayerWin(player);
				printPlayer(player);
			}
		if (player == 0x87)
				{
					player = 0xc0;
					printPlayer(player);
				}

	}

	return player;
}

char didPlayerWin(unsigned char player)
{
	if (player == 0xC7)
	{
		clearPlayer(player);
		cursorToLineOne();
		writeString(you);
		cursorToLineTwo();
		writeString(won);
	}

	return player == 0xC8;
}

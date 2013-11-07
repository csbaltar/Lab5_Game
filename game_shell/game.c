#include <msp430g2553.h>
#include "game.h"
#include "../LCD/LCD.h"
#include "../buttons/button.h"

#define True = 0x1
#define False = 0x0

unsigned char initPlayer()
{
	return 0x80;
}

unsigned char direction()
{
	#define True = 0x1
	#define False = 0x0

	if (BIT1 =True)
	{
		direction = UP;
	}
	else if (BIT2=True)
	{
		direction = RIGHT;
	}

	else if(BIT3=True)
	{
		direction=LEFT;
	}
	else if (BIT4=True)
	{
		direction = DOWN;
	}
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
	case UP:
		{
			player |= ~BIT6;
		}
		break;

	case RIGHT:
		if(player&0x0f<7)
		{
			player = 1 + player;
		}
		break;

	case LEFT:
		if(player&0x0f<0)
		{
			player = player - 1;
		}
		break;

	case DOWN:
		player |= BIT6;
		break;

	}

	return player;
}

char didPlayerWin(unsigned char player)
{
	return player == 0xC7;
}

#include <msp430g2553.h>
#include "game.h"
#include "../LCD/LCD.h"
#include "../buttons/button.h"


char you[]="You";
char won[]="Won!!";
char game[]="Game";
char over[]="Over!";
char boom[]="boom";
char clear[]="        ";



unsigned char Winning = 0;

void clearScreen()
{
	cursorToLineOne();
	writeString(clear);
	cursorToLineTwo();
	writeString(clear);
}


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
	case BIT1:		//UP

		clearScreen();
		clearPlayer(player);
		if (player == 0xc7)
				{
					player = 0x80;
				}
		else if (0xc0<=player<=0xc7)
			{
				player = 0x80+(player&0x0f);
			}
				debounce();
				printPlayer(player);

		break;

	case BIT2:		//DOWN

		clearScreen();
		clearPlayer(player);
		if (player == 0xc7)
				{
					player = 0x80;
				}
		else if (0x80<=player<=0x87)
			{
				player = 0xC0+(player&0x0f);
				didPlayerWin(player);
			}

		debounce();
		printPlayer(player);

		break;

	case BIT3:		//LEFT

		clearScreen();
		clearPlayer(player);

		if (player == 0xc7)
				{
					player = 0x80;
				}

		else if(player == 0xc0)
		{
			player = 0x87;
		}
		else if (player == 0x80)
		{
			player = 0x80;
		}else
			player = player-0x01;

		debounce();
		printPlayer(player);
		break;

	case BIT4:		//RIGHT

		clearScreen();
		clearPlayer(player);

		if (player == 0xc7)
				{
					player = 0x80;
				}

		else if (player == 0x87)
				{
					player = 0xc0;
				}
		else if(player == 0xc7)
		{
			player =0xc7;
		}else
			player = player + 0x01;
			didPlayerWin(player);

		debounce();
		printPlayer(player);

	}

	return player;
}


unsigned char youWon(unsigned char player)
{
	clearPlayer(player);
	cursorToLineOne();
	writeString(you);
	cursorToLineTwo();
	writeString(won);

	return initPlayer();
}

unsigned char didPlayerWin(unsigned char player)
{
	if (player == 0xC7)
	{
		youWon(player);
	}

	return initPlayer();
}

unsigned char gameOver(unsigned char  player)
{
	clearPlayer(player);
	cursorToLineOne();
	writeString(game);
	cursorToLineTwo();
	writeString(over);
	return initPlayer();
}

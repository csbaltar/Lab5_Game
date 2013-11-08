#include <msp430.h>
#include "game_shell/game.h"
#include "buttons/button.h"
#include "LCD/LCD.h"

#define True = 0x01
#define False = 0x00

void init_timer();
void init_buttons();

char flag=0;	//timer interrupt flag
char buttonPressed =0;	//button flag
char count;
unsigned char direction = (UP|DOWN|LEFT|RIGHT);

void clearTimer()
{
	count=0;
	TACTL |= TACLR;
}

int main(void)
{
	WDTCTL = (WDTPW|WDTHOLD);

	 initSPI();
	 LCDinit();
	 LCDclear();

	unsigned char player = initPlayer();



	printPlayer(player);

	init_timer();
	init_buttons();
	__enable_interrupt();

	while(1)
	{

	    if (flag)
		{
			flag = 0;
			count++;

	    	if (count>4)
	    	{
	    		player = gameOver(player);
	    		clearTimer();
	    	}
	    }

	    if(buttonPressed)
	    {
	    	buttonPressed=0;
	    	clearTimer();
	    	player = movePlayer(player, direction);
	    }

		/*
		 * while (game is on)
		 * {
		 * 		check if button is pushed (you don't want to block here, so don't poll!)
		 * 		if button is pushed:
		 * 			clear current player marker
		 * 			update player position based on direction
		 * 			print new player
		 * 			clear two second timer
		 * 			wait for button release (you can poll here)
		 * }
		 *
		 * print game over or you won, depending on game result
		 *
		 * wait for button press to begin new game (you can poll here)
		 * wait for release before starting again
		 */

	}

	return 0;
}

//
// YOUR TIMER A ISR GOES HERE
//

#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR()
{
    TACTL &= ~TAIFG;            // clear interrupt flag
    flag = 1;
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1_ISR(void)
{
    // do some stuff in response to an interrupt

	if (P1IFG & BIT1)
	    {
	        P1IFG &= ~BIT1;                            // clear flag
	        direction = UP;
	        buttonPressed=1;
	    }

	if (P1IFG & BIT2)
	    {
	        P1IFG &= ~BIT2;                         // clear flag
	        direction=DOWN;
	        buttonPressed =1;
	    }

	if (P1IFG & BIT3)
	    {
	        P1IFG &= ~BIT3;                         // clear P1.3 interrupt flag
	        direction = LEFT;
	        buttonPressed =1;
	    }
	if(P1IFG & BIT4)
		{
			P1IFG &= ~BIT4;                         // clear P1.4 interrupt flag
			direction = RIGHT;
	        buttonPressed =1;
		}

}


void init_timer()
{
	// do timer initialization work

	TACTL &= ~(MC1|MC0);        // stop timer

	TACTL |= TACLR;             // clear TAR

	TACTL |= TASSEL1;           // configure for SMCLK - what's the frequency (roughly)?

	TACTL |= ID1|ID0;           // divide clock by 8 - what's the frequency of interrupt?

	TACTL &= ~TAIFG;            // clear interrupt flag

	TACTL |= MC1;               // set count mode to continuous

	TACTL |= TAIE;              // enable interrupt
}

void init_buttons()
{
	// do button initialization work
	configureP1PinAsButton(BIT1|BIT2|BIT3|BIT4);

	P1IES |= BIT1|BIT2|BIT3|BIT4;                   // configure interrupt to sense falling edges
	P1IFG &= ~(BIT1|BIT2|BIT3|BIT4);                // clear flags
	P1IE |= BIT1|BIT2|BIT3|BIT4;                 	// enable the interrupts
}

#include <msp430.h>
#include "switches.h"
#include "led.h"

extern int redrawScreen;
char switch_state_down1, switch_state_down2, switch_state_down3, switch_state_down4,  switch_state_changed; /* effectively boolean */

static char 
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);	/* if switch down, sense up */
  return p2val;
}

void 
switch_init()			/* setup switch */
{  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE |= SWITCHES;		/* enable interrupts from switches */
  //P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
  led_update();
}

//where changes happen to both the buzzer and the graphics

void
switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();

  int prev1 = switch_state_down1;
  int prev2 = switch_state_down2;
  int prev3 = switch_state_down3;
  int prev4 = switch_state_down4;
  
  switch_state_down1 = (p2val & SW1) ? 0 : 1; /* 0 when SW1 is up */
  switch_state_down2 = (p2val & SW2) ? 0 : 1;
  switch_state_down3 = (p2val & SW3) ? 0 : 1;
  switch_state_down4 = (p2val & SW4) ? 0 : 1;
  //switch_state_changed = 1;

  if(prev1 != switch_state_down1 && switch_state_down1){
    o1 ^= 1;
    o2 = 0, o3 = 0, o4 = 0;
  }
  if(prev2 != switch_state_down1 && switch_state_down2){
    o2 ^= 1;
    o1 = 0, o3 = 0, o4 = 0;
  }
  if(prev3 != switch_state_down1 && switch_state_down3){
    o3 ^= 1;
    o1 = 0, o2 = 0, o4 = 0;
  }
  if(prev4 != switch_state_down1 && switch_state_down4){
    o4 ^= 1;
    o1 = 0, o2 = 0, o3 = 0;
  }
  
  /*redrawScreen = 1;
  led_update();*/
}

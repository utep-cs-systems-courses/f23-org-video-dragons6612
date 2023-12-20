#ifndef switches_included
#define switches_included

#define SW1 BIT0
#define SW2 BIT1
#define SW3 BIT2
#define SW4 BIT3
#define SWITCHES (SW1 | SW2 | SW3 | SW4)

void switch_init();
void switch_interrupt_handler();

extern int switch_state_down1, switch_state_down2, switch_state_down3, switch_state_down4; /* effectively boolean */

extern int o1, o2, o3 , o4;

#endif // included

#include <msp430.h>
#include <libTimer.h>
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "lcdutils.h"
#include "lcddraw.h"

int o1 = 0;
int o2 = 0;
int o3 = 0;
int o4 = 0;

// WARNING: LCD DISPLAY USES P1.0.  Do not touch!!! 

#define LED BIT6		/* note that bit zero req'd for display */

int redrawScreen = 0;

void wdt_c_handler(){
  static int clockCount = 0;

  clockCount++;
  if(clockCount >= 63 && o1 == 1){
    buzzer_set_period(5555);
    redrawScreen = 1;
    clockCount = 0;
  }
  if(clockCount >= 63 && o2 == 1){
    buzzer_set_period(7000);
    redrawScreen = 1;
    clockCount = 0;
  }
  if(clockCount >= 63 && o3 == 1){
    buzzer_set_period(2575);
    redrawScreen = 1;
    clockCount = 0;
  }
  if(clockCount >= 126 && o4 == 1){
    buzzer_set_period(0);
    redrawScreen = 1;
    clockCount = 0;
  }
}

void draw1(void){
  //clearScreen(COLOR_BLACK);
  for(int i = 0; i < 30; i++){
    clearScreen(COLOR_BLACK);
    //drawPixel(i,i, COLOR_PINK);
    //drawPixel(i, 30 - i, COLOR_PINK);
    fillRectangle(20, 82, 44 + i, 64, 0);
  }
  buzzer_set_period(5555);
}
	  
void draw2(){
  clearScreen(COLOR_BLUE);
  for(int i = 0; i < 30; i++){
    drawPixel(30 + i, 30 - i, COLOR_PINK);
  }
}

void draw3(){
  clearScreen(COLOR_BLACK);
  u_char width = screenWidth, height = screenHeight;

  //clearScreen(COLOR_BLACK);

  drawString5x7(20,20, "hello", COLOR_GREEN, COLOR_RED);

  fillRectangle(30,30, 60, 60, COLOR_ORANGE);
}

void draw4(){
  u_char width = screenWidth, height = screenHeight;

  //clearScreen(COLOR_BLACK);

  drawString5x7(20,20, "hello", COLOR_GREEN, COLOR_RED);

  fillRectangle(30,30, 60, 60, COLOR_ORANGE); 
}

/*void wdt_c_handler(){
  static int timer = 0;

  timer++;
  if(timer){
    redrawScreen = 1;
    f1();
    timer = 0;
  }
  if(switch_state_down2){
    redrawScreen = 1;
    timer = 0;
  }
  if(switch_state_down3){
    redrawScreen = 1;
    timer = 0;
  }
  if(switch_state_down4){
    redrawScreen = 1;
    timer = 0;
  }
  }*/

void main()
{
  
  //P1DIR |= LED;		/**< Green led on when CPU on */
  //P1OUT |= LED;
  configureClocks();
  lcd_init();
  led_init();
  switch_init();
  buzzer_init();
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);
  clearScreen(COLOR_BLACK);
  
  while(1){
    if(redrawScreen){
      if(o1){
	draw1();
      }else if(o2){
	draw2();
      }else if(o3){
	draw3();
      }else if(o4){
	draw4();
      }
      
    }
    P1OUT &= ~LED;	/* led off */
    or_sr(0x10);	/**< CPU OFF */
    P1OUT |= LED;	/* led on */
  }
}

/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */

#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

/** Initializes everything, clears the screen, draws "hello" and a square */

void f1(){
  clearScreen(COLOR_BLUE);
  for(int i = 0; i < 30; i++){
    
    drawPixel(i, i, COLOR_PINK);
    drawPixel(i, 30 - i, COLOR_PINK);
  }
}

void f2(){
  clearScreen(COLOR_BLUE);
  for(int i = 0; i < 30; i++){
    
    drawPixel(30 + i, 30 - i, COLOR_PINK);
  }
}

void f3(){
  clearScreen(COLOR_BLACK);
  u_char width = screenWidth, height = screenHeight;

  //clearScreen(COLOR_BLACK);

  drawString5x7(20,20, "hello", COLOR_GREEN, COLOR_RED);

  fillRectangle(30,30, 60, 60, COLOR_ORANGE);
}

int
main()
{
  configureClocks();
  lcd_init();
  /*u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_BLACK);

  drawString5x7(20,20, "hello", COLOR_GREEN, COLOR_RED);

  fillRectangle(30,30, 60, 60, COLOR_ORANGE);*/
  f1();
  //f2();
  //f3();
}

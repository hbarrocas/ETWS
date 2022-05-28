#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "menuclass.h"
#include "repleti.h"

// ==== heli's ascii canvas
#define SCREEN_W  40
#define SCREEN_H  40
#define SCREEN_SIZE  SCREEN_W * SCREEN_H

// Define position in canvas as a macro.
#define position(x, y) SCREEN_W * y + x

int buffer[SCREEN_SIZE];

void render () {
  // map: int -> ASCII pixel 
  char map[] = {'.', 'x', 'o', 'C'};
  for (int j = 0; j < SCREEN_H; j++) {
    for (int i = 0; i < SCREEN_W; i++) 
      printf ("%c ", map[ buffer[j*SCREEN_W+i] ]);
    printf("\n");
  }
}

void initbuffer(void) {
  for (int i = 0; i < SCREEN_SIZE; i++)
    buffer[i] = 0;
}

void setPixel(int x, int y) {
  buffer[position (x,y)] = 2;
}

void line(int x0, int y0, int x1, int y1) {
 
  int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
  int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
  int err = (dx>dy ? dx : -dy)/2, e2;
 
  for(;;){
    setPixel(x0,y0);
    if (x0==x1 && y0==y1) break;
    e2 = err;
    if (e2 >-dx) { err -= dy; x0 += sx; }
    if (e2 < dy) { err += dx; y0 += sy; }
  }
}

// ====== end heli canvas


// == Menu objects
Menu mainmnu;
Menu drawmnu;

// == ETWS functions ====

void main_exit(void){
  printf("quit main\n");
  //mnuFlg=0;
}

void main_cls (void){
  initbuffer();
  render();
  //clsGL();   
} // == end main_cls

void main_matsiz (){
  printf("matsiz"); 
}

void main_ac_draw (){
  //printf("main2draw"); 
  Menu_exec(drawmnu);
}

void main_ac_quitX11 (){
  //exitcode();	 
  exit(1); 
}

void main_ac_gdb(){
  system("gdb --quiet"); 
  system("clear");
}

void main_ac_editcode(){
  system("nedit mnuconfig.c mnuconfig.h hellomain.c hellomain.h &"); 
  exit(0);
}

void main_repl(){
  repl();
}

// ------ draw actions 
void draw_exit(){
  printf ("Exit draw menu\n");
  //curmnu=mainmnu;
}

void draw_cls (void){
  //clsGL();
  initbuffer();
  render();
} // == end draw_cls

void draw_line() {
  printf("draw_line\n");
  line(0,0,30,30);
  render();
} 

void draw_dot(){
  printf("draw_dot\n");
  setPixel(30,30);
  render();
} 

// == ETWS Functions END ===


// Menu initialisation
void cremenus () {

  drawmnu = Menu_new ("xdraw cls line dot");
  drawmnu->actions[0]= draw_exit;
  drawmnu->actions[1]= draw_cls;	
  drawmnu->actions[2]= draw_line;
  drawmnu->actions[3]= draw_dot;

  mainmnu = Menu_new ("xmain cls matsiz draw quitX11 gdb editcode repl");
  mainmnu->actions[0]=main_exit;
  mainmnu->actions[1]=main_cls;
  mainmnu->actions[2]=main_matsiz;
  mainmnu->actions[3]=main_ac_draw;
  mainmnu->actions[4]=main_ac_quitX11;
  mainmnu->actions[5]=main_ac_gdb;
  mainmnu->actions[6]=main_ac_editcode;
  mainmnu->actions[7]=main_repl;

}

//void initglutlarg(void);


int main(void) {
  // build menu structures
  cremenus();

  // initialise canvas memory space
  //initglutlarg();
  initbuffer();

  // Render canvas and menu. Listen for options
  //render(buffer);
  render();
  Menu_exec(mainmnu);

  return 0;
}

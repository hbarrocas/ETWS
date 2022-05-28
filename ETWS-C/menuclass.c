#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menuclass.h"

Menu Menu_new (char *cmdstring) {
  char tmpstr[256];
  char *token;

  // === create the mnu pointer
  Menu pthis = malloc(sizeof *pthis);
  
  pthis->cmdcnt=0;
  strcpy(pthis->cmdstr,cmdstring); 
  
  // ====  count the cmds and collect first letters ===
  strcpy(tmpstr,cmdstring);
  token = strtok(tmpstr, "( )"); 

  while (token) {
    pthis->cmdlettrs[pthis->cmdcnt]= token[0];
    printf("pthis->cmdletr[cnt]: %i\n",pthis->cmdlettrs[pthis->cmdcnt]);
    token = strtok(NULL, " -\n");
    pthis->cmdcnt++;
  }
  
  printf("mnu count is: %i\n", pthis->cmdcnt);
  // ====  returns pointer to created menu
  printf("cmdstr: %s\n",pthis->cmdstr);
  return pthis;
}

void Menu_delete(Menu *pthis) {
  if (pthis)  {
    free(*pthis);
    *pthis = NULL;
  }
}

// ======  methods
void Menu_disp(Menu pthis) {
  //system("clear");
  printf( "%s\n",pthis->cmdstr);
}

void Menu_exec (Menu m) {

  char strvar[100];
  
  // ex mnuFlg
  m->flag = 1;
  while (m->flag) {
    Menu_disp (m);
    fgets (strvar, 100, stdin);

    // Find command
    for (int i = 0; i < m->cmdcnt; i++) {
      // x is a fixed menu-exit command
      if (strvar[0] == 'x') m->flag = 0;
      else if (m->cmdlettrs[i] == strvar[0])
	m->actions[i]();
    }
  }
}

// ===== end methods

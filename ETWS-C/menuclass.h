
typedef void (*fp)(void);

typedef struct sMenu {
  int flag;
  char cmdstr[255];
  char cmdlettrs[10];
  int cmdcnt;
  fp actions[10];
} *Menu;

Menu Menu_new (char*);
void Menu_delete (Menu*);
void Menu_disp (Menu);
void Menu_exec (Menu);

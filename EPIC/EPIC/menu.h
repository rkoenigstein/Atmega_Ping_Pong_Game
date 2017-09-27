#ifndef MENU
#define MENU

#include <stdlib.h>
#include <stdint.h>

#define MAX_TITLE_LENGTH 32
#define MAX_NUM_OF_SUBMENUS 10

typedef struct menu{
	char* menu_title;
	uint8_t title_length;
	void (*operation)();
	uint8_t num_of_submenus;
	struct menu *submenu;
	struct menu *parent_menu;
	} menu;
	
menu createMenu(void);
	
#endif
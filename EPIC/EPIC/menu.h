#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING 25
#define MAX_SUBMENUS 16

typedef struct MenuNode MenuNode;
typedef struct MenuContent MenuContent;

struct MenuContent {
	uint8_t title_id;
	void (*operation)(void);
};

struct MenuNode {
	MenuContent m_content;
	MenuNode* m_parent;
	MenuNode** m_submenus;
	uint8_t m_num_submenus;
};

/* returns root of menu */
MenuNode* getMenuRoot(void);

/* creates menu */
void createMenu(void);

/* returns next entry in the hierarchy if there is any or the current node elsewise */
MenuNode* getNextEntry(MenuNode* node);

/* returns previous entry in the hierarchy if there is any or the current node elsewise */
MenuNode* getPreviousEntry(MenuNode* node);

/* opens submenu with index index */
MenuNode* menuLevelDown(MenuNode* const node, uint8_t index_of_submenu);

/* opens parent menu */
MenuNode* menuLevelUp(MenuNode* const node);

#endif

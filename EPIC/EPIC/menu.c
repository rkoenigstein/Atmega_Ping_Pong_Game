#include "menu.h"

extern void printDumb(void);
extern void print1(void);
extern void print2(void);
extern void print3(void);
extern void print4(void);
extern void printMain(void);

static MenuNode* _menu;

MenuNode* createMenuNode(char* title, int title_length, void (*operation)(void), uint8_t num_of_submenus)
{
	MenuNode* _mnode = malloc(sizeof(MenuNode));
	_mnode->m_submenus = malloc(num_of_submenus * sizeof(MenuNode*));
	_mnode->m_num_submenus = num_of_submenus;
	_mnode->m_content.title = title;
	_mnode->m_content.title_length = title_length;
	_mnode->m_content.operation = operation;
	return _mnode;
}

static void assignParents(MenuNode* node)
{
	for(uint8_t i = 0; i < node->m_num_submenus; i++)
	{
		node->m_submenus[i]->m_parent = node;
		assignParents(node->m_submenus[i]);
	}
}

MenuNode* getMenuRoot(void)
{
	if(_menu == NULL)
	{
		createMenu();
	}
	return _menu;
}


void createMenu(void)
{
	_menu = createMenuNode("root", 4, &printMain, 4);
	_menu->m_submenus[0] = createMenuNode("Games", 5, &print1, 1);
	_menu->m_submenus[0]->m_submenus[0] = createMenuNode("PingPong", 8, &print2, 0);
	_menu->m_submenus[1] = createMenuNode("Players", 7, &print3, 1);
	_menu->m_submenus[1]->m_submenus[0] = createMenuNode("Create User", 11, NULL, 0);
 	_menu->m_submenus[2] = createMenuNode("Settings", 8, &print4, 1);
	_menu->m_submenus[2]->m_submenus[0] = createMenuNode("Calibrate Joystick", 18, NULL, 0);
	_menu->m_submenus[3] = createMenuNode("Dummy", 5, &printDumb, 1);
	_menu->m_submenus[3]->m_submenus[0] = createMenuNode("Printdummy", 20, NULL, 0);
	assignParents(_menu);	
}

MenuNode* getNextEntry(MenuNode* node)
{
	if(node->m_parent)
	{
        	for(uint8_t i = 0; i < node->m_parent->m_num_submenus-1; i++)
		{
			if(node->m_parent->m_submenus[i] == node)
			{
                		return node->m_parent->m_submenus[i+1];
            		}
        	}
    	}
	return node; 
}

MenuNode* getPreviousEntry(MenuNode* node)
{
	if(node->m_parent)
	{
		for(uint8_t i = 1; i < node->m_parent->m_num_submenus; i++)
		{
			if(node->m_parent->m_submenus[i] == node)
			{
				return node->m_parent->m_submenus[i-1];
			}
		}
	}
	return node;
}

MenuNode* menuLevelDown(MenuNode* const node, uint8_t index_of_submenu)
{
	if(0 <= index_of_submenu && index_of_submenu <= node->m_num_submenus)
		return node->m_submenus[index_of_submenu];
	return node;
}

MenuNode* menuLevelUp(MenuNode* const node)
{
	if(node->m_parent)
		return node->m_parent;
	return node;
}

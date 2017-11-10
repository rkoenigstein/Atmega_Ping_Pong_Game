#include "menu.h"

#define F_CPU 4915200 // Clock speed
#include <util/delay.h>

//include external functions passed to the menu
extern void song_harry_potter(void);
extern void song_tetris(void);
extern void song_cantina_band(void);
extern void song_pokemon(void);

extern void printGreetings(void);
extern void print1(void);
extern void print2(void);
extern void print3(void);
extern void print4(void);
extern void printMain(void);

extern void storeHighscore(void);
extern void resetHighscore(void);
extern void calibrateLeftSlider(void);
extern void calibrateRightSlider(void);
extern void calibrateJoystick(void);
extern void showHighscore(void);

static MenuNode* _menu;

MenuNode* createMenuNode(char* title, void (*operation)(void), uint8_t num_of_submenus)
{
	MenuNode* _mnode = malloc(sizeof(MenuNode));
	_mnode->m_submenus = malloc(num_of_submenus*sizeof(MenuNode*));
	_mnode->m_num_submenus = num_of_submenus;
	_mnode->m_content.title = title;
	_mnode->m_content.operation = operation;
	return _mnode;
}

static void assignParents(MenuNode* node)
{
	if(node)
	{
		for(uint8_t i = 0; i < node->m_num_submenus; i++)
		{
			node->m_submenus[i]->m_parent = node;
			assignParents(node->m_submenus[i]);
		}
	}
	if(!node)
		printf("NULL node\n");
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
	_menu = createMenuNode("root", NULL, 4);
	_menu->m_submenus[0] = createMenuNode("Games", NULL, 2);
	_menu->m_submenus[0]->m_submenus[0] = createMenuNode("PingPong", &print2, 0);
	_menu->m_submenus[0]->m_submenus[1] = createMenuNode("PingPang", &print1, 0);
	_menu->m_submenus[1] = createMenuNode("Highscore", &showHighscore, 0);
	_menu->m_submenus[2] = createMenuNode("Settings", NULL, 3);
	_menu->m_submenus[2]->m_submenus[0] = createMenuNode("Store Highscore", &storeHighscore, 0);
	_menu->m_submenus[2]->m_submenus[1] = createMenuNode("Reset Highscore", &resetHighscore, 0);
	_menu->m_submenus[2]->m_submenus[2] = createMenuNode("Calibrate Joystick", &calibrateJoystick, 0);
	_menu->m_submenus[2]->m_submenus[3] = createMenuNode("Calibrate Sliders", NULL, 2);
	_menu->m_submenus[2]->m_submenus[2]->m_submenus[0] = createMenuNode("Left Slider", &calibrateLeftSlider, 0);
	_menu->m_submenus[2]->m_submenus[2]->m_submenus[1] = createMenuNode("Right Slider", &calibrateRightSlider, 0);
	_menu->m_submenus[3] = createMenuNode("Songs", NULL, 4);
	_menu->m_submenus[3]->m_submenus[0] = createMenuNode("Harry Potter", &play_song, 0);
	_menu->m_submenus[3]->m_submenus[1] = createMenuNode("Tetris", &play_song, 0);
	_menu->m_submenus[3]->m_submenus[2] = createMenuNode("Cantina Band", &play_song, 0);
	_menu->m_submenus[3]->m_submenus[3] = createMenuNode("Pokemon", &play_song, 0);
	assignParents(_menu);
	printf("PARENTS ASSIGNED\n");

}

MenuNode* getNextEntry(MenuNode* node)
{
	if(node->m_parent)
    for(uint8_t i = 0; i < node->m_parent->m_num_submenus-1; i++)
			if(node->m_parent->m_submenus[i] == node)
	  		return node->m_parent->m_submenus[i+1];
	return node;
}

MenuNode* getPreviousEntry(MenuNode* node)
{
	if(node->m_parent)
		for(uint8_t i = 1; i < node->m_parent->m_num_submenus; i++)
			if(node->m_parent->m_submenus[i] == node)
				return node->m_parent->m_submenus[i-1];
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

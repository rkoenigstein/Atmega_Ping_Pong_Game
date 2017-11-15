#include "menu.h"
#include "Parameters.h"

#ifdef ATMEGA2560
	#define F_CPU 16000000
#else
	#define F_CPU 4915200
#endif
#include <util/delay.h>

#include <string.h>

//include external functions passed to the menu
extern void song_harry_potter(void);
extern void song_tetris(void);
extern void song_cantina_band(void);
extern void song_pokemon(void);

extern void storeHighscore(void);
extern void resetHighscore(void);
extern void calibrateLeftSlider(void);
extern void calibrateRightSlider(void);
extern void calibrateJoystick(void);
extern void showHighscore(void);
extern void ping_pong_idle(void);
extern void playPingPong(void);

static MenuNode* _menu;

MenuNode* createMenuNode(uint8_t title_id, void (*operation)(void), uint8_t num_of_submenus)
{
	MenuNode* _mnode = malloc(sizeof(MenuNode));
	if(!_mnode)
	{
		printf("NO memory for menu %d\n", title_id);
	}
	_mnode->m_submenus = malloc(num_of_submenus*sizeof(MenuNode*));
	if(!(_mnode->m_submenus))
	{
		printf("NO memory for submenu of menu %d\n", title_id);
	}
	_mnode->m_num_submenus = num_of_submenus;
	_mnode->m_content.title_id = title_id;
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
	_menu = createMenuNode(0, NULL, 4);
	_menu->m_submenus[0] = createMenuNode(1, NULL, 2);
	_menu->m_submenus[0]->m_submenus[0] = createMenuNode(2, &ping_pong_idle, 0);
	_menu->m_submenus[0]->m_submenus[1] = createMenuNode(3, &playPingPong, 0);
	_menu->m_submenus[1] = createMenuNode(4, &showHighscore, 0);
	_menu->m_submenus[2] = createMenuNode(5, NULL, 4);
	_menu->m_submenus[2]->m_submenus[0] = createMenuNode(6, &storeHighscore, 0);
	_menu->m_submenus[2]->m_submenus[1] = createMenuNode(7, &resetHighscore, 0);
	_menu->m_submenus[2]->m_submenus[2] = createMenuNode(8, &calibrateJoystick, 0);
	_menu->m_submenus[2]->m_submenus[3] = createMenuNode(9, NULL, 2);
	_menu->m_submenus[2]->m_submenus[3]->m_submenus[0] = createMenuNode(10, NULL, 0);
	_menu->m_submenus[2]->m_submenus[3]->m_submenus[1] = createMenuNode(11, NULL, 0);
	_menu->m_submenus[3] = createMenuNode(12, NULL, 4);
	/*
	_menu->m_submenus[3]->m_submenus[0] = createMenuNode("Harry Potter", &play_song, 0);
	_menu->m_submenus[3]->m_submenus[1] = createMenuNode("Tetris", &play_song, 0);
	_menu->m_submenus[3]->m_submenus[2] = createMenuNode("Cantina Band", &play_song, 0);
	_menu->m_submenus[3]->m_submenus[3] = createMenuNode("Pokemon", &play_song, 0);
	*/
	_menu->m_submenus[3]->m_submenus[0] = createMenuNode(13, NULL, 0);
	_menu->m_submenus[3]->m_submenus[1] = createMenuNode(14, NULL, 0);
	_menu->m_submenus[3]->m_submenus[2] = createMenuNode(15, NULL, 0);
	_menu->m_submenus[3]->m_submenus[3] = createMenuNode(16, NULL, 0);
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

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
extern void song_octaves(void);
extern void song_merry_x_mas(void);
extern void song_jingle_bells(void);
extern void song_last_christmas(void);

extern void ping_pong_idle(void);
extern void playPingPong(void);
extern void irSettings(void);
extern void animations(void);

static MenuNode* _menu;

MenuNode* createMenuNode(uint8_t title_id, void (*operation)(void), uint8_t num_of_submenus)
{
	static uint16_t current_adress = 0x1C00;

	MenuNode* _mnode = (void *) current_adress;
	current_adress += sizeof(MenuNode);

	_mnode->m_submenus = (void *) current_adress;
	current_adress += num_of_submenus * sizeof(MenuNode *);

	_mnode->m_num_submenus = num_of_submenus;
	_mnode->m_content.title_id = title_id;
	//printf("title id: %d, memory addr: 0x%02x\n", title_id, current_adress - num_of_submenus * sizeof(MenuNode *));
	_mnode->m_content.operation = operation;

	if(current_adress >= 0x1FFF)
		printf("Menu out of memory\n");
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
	createMenu();
	return _menu;
}


void createMenu(void)
{
	_menu = createMenuNode(0, NULL, 5);
	_menu->m_submenus[0] = createMenuNode(1, NULL, 2);
	_menu->m_submenus[0]->m_submenus[0] = createMenuNode(2, &playPingPong, 0);
	_menu->m_submenus[0]->m_submenus[1] = createMenuNode(3, &ping_pong_idle, 0);
	_menu->m_submenus[1] = createMenuNode(5, NULL, 1);
	_menu->m_submenus[1]->m_submenus[0] = createMenuNode(35, &irSettings, 0);
	_menu->m_submenus[2] = createMenuNode(12, NULL, 8);
	_menu->m_submenus[2]->m_submenus[0] = createMenuNode(13, &song_harry_potter, 0);
	_menu->m_submenus[2]->m_submenus[1] = createMenuNode(14, &song_tetris, 0);
	_menu->m_submenus[2]->m_submenus[2] = createMenuNode(15, &song_cantina_band, 0);
	_menu->m_submenus[2]->m_submenus[3] = createMenuNode(16, &song_pokemon, 0);
	_menu->m_submenus[2]->m_submenus[4] = createMenuNode(17, &song_octaves, 0);
	_menu->m_submenus[2]->m_submenus[5] = createMenuNode(18, &song_merry_x_mas, 0);
	_menu->m_submenus[2]->m_submenus[6] = createMenuNode(19, &song_jingle_bells, 0);
	_menu->m_submenus[2]->m_submenus[7] = createMenuNode(20, &song_last_christmas, 0);
	_menu->m_submenus[3] = createMenuNode(44, &animations, 0);
	_menu->m_submenus[4] = createMenuNode(43, &printGreetings, 0);
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
	if(node <= (MenuNode *) 0x1C00)
		return node;
	if(node->m_parent)
		return node->m_parent;
	return node;
}

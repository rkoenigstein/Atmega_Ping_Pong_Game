#include "menu.h"
#include <stdio.h>
#include <stdlib.h>

/* simple test function for the menu if no board is available */
int main()
{

	MenuNode* menu = getMenuRoot();
	printf("Menu title: %s\n", menu->m_content.title);

	menu->m_content.operation(); //"Main"
	menu = getNextEntry(menu);
	menu->m_content.operation(); //"Main"
	menu = getPreviousEntry(menu);
	menu->m_content.operation(); //"Main"
	menu = menuLevelDown(menu, 0);
	menu->m_content.operation(); //"1"
	menu = menuLevelDown(menu, 0);
	menu->m_content.operation(); //"2"
	menu = menuLevelUp(menu);
	menu->m_content.operation(); //"1"
	menu = getNextEntry(menu);
	menu->m_content.operation(); //"3"
	menu = getNextEntry(menu);
	menu->m_content.operation(); //"4"
	menu = getNextEntry(menu);
	menu->m_content.operation(); //"I am dumb"
	menu = getPreviousEntry(menu);
	menu->m_content.operation(); //"4"
	menu = menuLevelUp(menu);
	menu->m_content.operation(); //"Main"
	return 0;
}

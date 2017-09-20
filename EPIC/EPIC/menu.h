#ifndef MENU
#define MENU

typedef struct {
	void (*operation)();
	} Menu;
	
typedef struct {
	Menu menu;
	
	} MenuItem;
	
typedef struct {
	Menu menu;
	void (*addMenuItemOrSubMenu)();
	void (*removeMenuItemOrSubMenu)();
	void (*getSubMenu)();
	} SubMenu;
	
#endif
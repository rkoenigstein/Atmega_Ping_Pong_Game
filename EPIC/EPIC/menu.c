#include "menu.h"
#include "oled_driver.h"

#define MAX_SUBS_MAIN 24

menu createMenu(void)
{
	
	menu main_menu;
	menu greetings = { .menu_title = "greetings", .title_length = 9, &printGreetings, .num_of_submenus=0, .submenu=NULL, .parent_menu = &main_menu};
	menu blub = { .menu_title = "blob", .title_length = 4, &printBlobs, .num_of_submenus=0, .submenu=NULL, .parent_menu = &main_menu };
	
	//menu settings = { .menu_title = "main menu", , .num_of_submenus=num_subs_main, .submenu=&sub_settings };
	
	//int num_subs_main = 6;
	//menu sub_main[num_subs_main] = {settings, calibration, start_game, highscore, history, greetings};
	
	uint8_t num_subs_main = 2;
	menu sub_main[] = {blub, greetings};
	main_menu.menu_title = "main menu";
	main_menu.title_length = 9;
	main_menu.num_of_submenus=num_subs_main;
	main_menu.submenu=&sub_main;
	main_menu.parent_menu = NULL;
}
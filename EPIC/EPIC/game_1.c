#include "game_1.h"
#include "oled_driver.h"

#ifdef ATMEGA2560
	#define F_CPU 16000000
#else
	#define F_CPU 4915200
#endif
#include <stdio.h>
#include <util/delay.h>

//GLOBAL VARIABLE FOR THE GAME
PLAYER player;
BALL ball;
int n_lives=3;
int n_catched_balls=0;
int level=0;
int grid[N_X][N_Y];		//Gives the status of each little block in the grid


void draw_heart_to_buffer(POS pos)
{
	TRI tri;
	tri.full=1;
	tri.l=9;
	tri.pos=pos;
	tri.ori=DOWN;
	
	draw_triangle_buffer(tri);
	
	tri.pos.x +=5;
	tri.ori=UP;
	tri.l=4;
	
	draw_triangle_buffer(tri);
	
	tri.pos.x -=5;
	
	draw_triangle_buffer(tri);
}

void draw_lives_buffer(int n_lives)
{
	POS pos;
	pos.x=N-10;
	pos.y=5;
	int i=0;
	for(i=0;i<n_lives;i++)
	{
		draw_heart_to_buffer(pos);
		pos.x -= 11;
	}
	
}

void update_ball(void)
{
	switch (ball.dir)
	{
		case UP_RIGHT:
		{
			if(ball.pos.x == LIM_RIGHT)
			{
				ball.dir=UP_LEFT;
				update_ball();
				return;
			}
			if(ball.pos.y == LIM_UP)
			{
				ball.dir=DOWN_RIGHT;
				update_ball();
				return;
			}
			ball.pos.x++;
			ball.pos.y--;
		} break;
		case UP_LEFT:
		{
			if(ball.pos.x == LIM_LEFT)
			{
				ball.dir=UP_RIGHT;
				update_ball();
				return;
			}
			if(ball.pos.y == LIM_UP)
			{
				ball.dir=DOWN_LEFT;
				update_ball();
				return;
			}
			ball.pos.x--;
			ball.pos.y--;
		}break;
		case DOWN_RIGHT:
		{
			if(ball.pos.x == LIM_RIGHT)
			{
				ball.dir=DOWN_LEFT;
				update_ball();
				return;
			}
			if(ball.pos.y == LIM_DOWN)
			{
				ball.dir=UP_RIGHT;
				n_lives--;
				ball.pos.x=B_X;
				ball.pos.y=B_Y;
				ball.dir=DOWN_RIGHT;
				n_catched_balls = 0;
				return;
			}
			if((ball.pos.y == Y_PLAYER) && ((ball.pos.x >= player.rect.pos.x) && (ball.pos.x <= player.rect.pos.x+player.rect.Lx)))
			{
				ball.dir=UP_RIGHT;
				n_catched_balls++;
				update_ball();
				return;
			}
			ball.pos.x++;
			ball.pos.y++;
		}break;
		case DOWN_LEFT:
		{
			if(ball.pos.x == LIM_LEFT)
			{
				ball.dir=DOWN_RIGHT;
				update_ball();
				return;
			}
			if(ball.pos.y == LIM_DOWN)
			{
				ball.dir=UP_LEFT;
				n_lives--;
				ball.pos.x=B_X;
				ball.pos.y=B_Y;
				ball.dir=DOWN_RIGHT;
				n_catched_balls = 0;
				return;
			}
			if((ball.pos.y == Y_PLAYER) && ((ball.pos.x >= player.rect.pos.x) && (ball.pos.x <= player.rect.pos.x+player.rect.Lx)))
			{
				ball.dir=UP_LEFT;
				n_catched_balls++;
				update_ball();
				return;
			}
			ball.pos.x--;
			ball.pos.y++;
			
		}break;
	}
	return;
}

void update_player(void)
{
	// Get player direction form CAN (JOYSTICK)
	switch (player.dir)
	{
		case RIGHT:
		{
			if(player.rect.pos.x+player.rect.Lx >= LIM_RIGHT)
				return;
			player.rect.pos.x += 2;
		}break;
		case LEFT:
		{
			if(player.rect.pos.x <= LIM_LEFT+1)
				return;
			player.rect.pos.x -= 2;
		}break;
	}
	return;
}

void draw_borders_buffer (void)
{
	RECT border;
	border.pos.x = LIM_LEFT;
	border.pos.y = LIM_UP;
	border.Lx = LIM_RIGHT-LIM_LEFT;
	border.Ly = 1;
	border.full = FULL;
	draw_rectangle_buffer(border);
	border.Lx = 1;
	border.Ly = LIM_DOWN-LIM_UP;
	draw_rectangle_buffer(border);
	border.pos.y = LIM_DOWN;
	border.Lx = LIM_RIGHT-LIM_LEFT;
	border.Ly = 1;
	draw_rectangle_buffer(border);
	border.pos.x = LIM_RIGHT;
	border.pos.y = LIM_UP;
	border.Ly = LIM_DOWN-LIM_UP+1;
	border.Lx = 1;
	draw_rectangle_buffer(border);
}

void draw_grid_buffer (void)
{
	int i=0;
	int j=0;
	
	RECT rect;
	
	for(i=0;i<N_X;i++)
		for(j=0;j<N_Y;j++)
		{
			rect.pos.x=LIM_LEFT+EMPTY_SPACE_X+i*(EMPTY_SPACE_X+L_X);
			rect.pos.y=LIM_UP+EMPTY_SPACE_Y+j*(EMPTY_SPACE_Y+L_Y);
			rect.Ly=L_Y;
			rect.Lx=L_X;
			rect.full=grid[i][j];
			draw_rectangle_buffer(rect);
		}
}
int bounce_ball_rect (RECT rect)
{
	switch (ball.dir)
	{
		case UP_RIGHT:
		{
			if((ball.pos.x == rect.pos.x) && ((ball.pos.y >= rect.pos.y) && (ball.pos.y <= rect.pos.y + rect.Ly))) //LIMIT RIGHT
			{
				ball.dir=UP_LEFT;
				return 1;
			}
			if((ball.pos.y == rect.pos.y+rect.Ly) && ((ball.pos.x >= rect.pos.x) && (ball.pos.x <= rect.pos.x + rect.Lx))) //LIMIT UP
			{
				ball.dir=DOWN_RIGHT;
				return 1;
			}
		} break;
		case UP_LEFT:
		{
			if((ball.pos.x == rect.pos.x + rect.Lx) && ((ball.pos.y >= rect.pos.y) && (ball.pos.y <= rect.pos.y + rect.Ly)))//LIMIT_LEFT
			{
				ball.dir=UP_RIGHT;
				return 1;
			}
			if((ball.pos.y == rect.pos.y+rect.Ly) && ((ball.pos.x >= rect.pos.x) && (ball.pos.x <= rect.pos.x + rect.Lx)))
			{
				ball.dir=DOWN_LEFT;
				return 1;
			}
		}break;
		case DOWN_RIGHT:
		{
			if((ball.pos.x == rect.pos.x) && ((ball.pos.y >= rect.pos.y) && (ball.pos.y <= rect.pos.y + rect.Ly)))
			{
				ball.dir=DOWN_LEFT;
				return 1;
			}
			if((ball.pos.y == rect.pos.y) && ((ball.pos.x >= rect.pos.x) && (ball.pos.x <= rect.pos.x + rect.Lx)))//LIMIT_DOWN
			{
				ball.dir=UP_RIGHT;
				return 1;
			}
		}break;
		case DOWN_LEFT:
		{
			if((ball.pos.x == rect.pos.x + rect.Lx) && ((ball.pos.y >= rect.pos.y) && (ball.pos.y <= rect.pos.y + rect.Ly)))
			{
				ball.dir=DOWN_RIGHT;
				return 1;
			}
			if((ball.pos.y == rect.pos.y) && ((ball.pos.x >= rect.pos.x) && (ball.pos.x <= rect.pos.x + rect.Lx)))
			{
				ball.dir=UP_LEFT;
				return 1;
			}
		}break;
	}
	return 0;
}

void bounce_ball_grid (void)
{
	RECT rect;
	int i=0;
	int j=0;
	
	for(i=0;i<N_X;i++)
		for(j=0;j<N_Y;j++)
			if(grid[i][j] != DESTROYED)
			{
				rect.pos.x=LIM_LEFT+EMPTY_SPACE_X+i*(EMPTY_SPACE_X+L_X);
				rect.pos.y=LIM_UP+EMPTY_SPACE_Y+j*(EMPTY_SPACE_Y+L_Y);
				rect.Ly=L_Y;
				rect.Lx=L_X;
				rect.full=grid[i][j];
				if(bounce_ball_rect(rect) == 1)
				{
					if(grid[i][j]==RECT_EMPT)
						grid[i][j]=DESTROYED;
					if(grid[i][j]==FULL)
						grid[i][j]=RECT_EMPT;
				}
			}
			return;
}

int get_direction(void)
{
	JOY_POS pos = JOY_getPosition();
	return pos.dir;
}
void ping_pong_idle(void)
{
	int i=0;
	int j=0;
	
	bool pause = false;
	
	//Starting conditions
	ball.pos.x=B_X;
	ball.pos.y=B_Y;
	ball.dir=DOWN_RIGHT;
	
	player.rect.pos.x=15;
	player.rect.pos.y=Y_PLAYER;
	player.rect.Lx=DIM_PLAYER;
	player.rect.Ly=1;
	player.rect.full=1;
	
	//initialize grid to perfect
	for(i=0;i<N_X;i++)
		for(j=0;j<N_Y;j++)
			grid[i][j]=FULL;

	//idle function
	while (1)
	{
		while(n_lives>=0 )
		{
			clear_buffer();
			if(!(pause))
			{
				player.dir=get_direction();
			
				if(DIM_PLAYER > level)
				player.rect.Lx = DIM_PLAYER - level;
				if(DIM_PLAYER <= level)
				player.rect.Lx = 1;
			
				level = n_catched_balls % DIM_PLAYER;
			
				draw_lives_buffer(n_lives);
				draw_borders_buffer();
				draw_rectangle_buffer(player.rect);
				draw_lives_buffer(n_lives);
				draw_grid_buffer();
				draw_one_bit_buffer(ball.pos);
			
				bounce_ball_grid();
				update_ball();
				update_player();
				print_buffer();
				if(JOY_button(R))
					pause = true;
			}
			if(pause)
			{
				clear_buffer();
				position pos;
				pos.column=45;
				pos.page=1;
				print_string_to_buffer("PAUSE", pos);
				pos.page = 3;
				pos.column=2;
				print_string_to_buffer("LEFT: resume", pos);
				pos.page++;
				print_string_to_buffer("RIGHT: leave", pos);
				if (JOY_getPosition().dir == LEFT)
					pause = false;
				if(JOY_getPosition().dir == RIGHT)
					return;
				print_buffer();
			}
			_delay_ms(10);
			//printf("%d,-%d;",ball.pos.x, ball.pos.y);
			//printf("%d,-%d;",player.rect.pos.x, player.rect.pos.y);
		}
		position pos;
		pos.column=30;
		pos.page=3;
		clear_buffer();
		print_string_to_buffer("GAME OVER!", pos);
		print_buffer();
		_delay_ms(2000);
		
		clear_buffer();
		pos.page = 3;
		pos.column = 2;
		print_string_to_buffer("LEFT: restart", pos);
		pos.page++;
		print_string_to_buffer("RIGHT: leave", pos);
		print_buffer();
		
		while(1)
		{
			_delay_ms(10);
			if (JOY_getPosition().dir == LEFT)
			{
				n_lives=3;
				break;
			}
			if(JOY_getPosition().dir == RIGHT)
				return;
		}

	}
}

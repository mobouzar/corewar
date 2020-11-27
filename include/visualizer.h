#ifndef VISUALIZER_H
# define VISUALIZER_H

# include <ncurses.h>

/*
** Define colors 8509
*/


# define PLAYER1 1
# define PLAYER2 2
# define PLAYER3 3
# define PLAYER4 4

# define OUT_PROCE 11

# define BOARD_COLOR 9
# define BORDER_COLOR 10

typedef struct	s_point
{
	int			alpha;
	int			id;
	int			y;
	int			x;
}				t_point;

t_point			g_coords[4096];

typedef struct  s_visu
{
    WINDOW      *menu;
    WINDOW      *arena;
	WINDOW		*winner;
    int			pause;
	int			cycle_speed;
	int			speed;
	int			last_live_color;
    int			key;
	int			sleep;
	int			close;
	int			color;
	int			step;
	int			win;
}				t_visu;


#endif

#ifndef VISUALIZER_H
# define VISUALIZER_H

# include <ncurses.h>

/*
** Define colors
*/

# define WHITE 1
# define GRAY 8509
# define GREEN 3

# define PROCE_COLOR 0

typedef struct	s_point
{
	int			alpha;
	int			id;
	int			y;
	int			x;
	int			color;
}				t_point;

typedef struct  s_visu
{
    WINDOW      *menu;
    WINDOW      *arena;
	t_point		*coords;
    int			pause;
	int			cycle;
	int			cycle_speed;
    int         key;
	int			cursor;
	int			sleep;
	int			close;
	int			color;
	int			color_a;
	int			color_b;
}				t_visu;


#endif

#ifndef VISUALIZER_H
# define VISUALIZER_H

# include <ncurses.h>

/*
** Define colors
*/

# define WHITE 1
# define GRAY 860997
# define GREEN 3

# define PROCE_COLOR 0

typedef struct  s_visu
{
    WINDOW      *menu;
    WINDOW      *arena;
    int			pause;
	int			cycle;
	int			cycle_speed;
    int         key;
	int			cursor;
	int			sleep;
	int			close;
	int			color_a;
	int			color_s;
}               t_visu;

#endif

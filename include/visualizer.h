#ifndef VISUALIZER_H
# define VISUALIZER_H

# include <ncurses.h>

/*
** Define colors
*/

# define WHITE 1
# define GRAY 2
# define GREEN 3

typedef struct  s_visu
{
    WINDOW      *mwin;
    WINDOW      *bwin;
    char        *pause;
    int         key;
}               t_visu;

#endif

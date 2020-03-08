/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 18:06:05 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/08 17:54:17 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include <unistd.h>
#include "../libft/libft.h"
#include <fcntl.h>

typedef struct s_process
{
    int pc;
    int carry;
    int id;
    unsigned int regster[16];
    int nbr_cycler_live;
    struct s_process *next;

} t_process;

typedef struct s_player
{
    char *name;
    char *comment;
    size_t  size_prog;
    int     live;
    int id;
    t_process *process;
    t_header *data_file;
}               t_player;

typedef struct s_corewar
{
    unsigned char *arena;
    int cycle;
    int cycle_to_die;
    int nbr_live;
    int nbr_checks;
    int nbr_process;
    int player_last_live;
    t_player *players[4];
} t_corewar;

t_corewar *get_struct(t_corewar *lst);
void ft_print_arena();
unsigned char *ft_get_arena(void);
char *addr_to_hex(void *addr, size_t size);
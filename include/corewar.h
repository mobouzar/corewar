/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouzar <mobouzar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 18:06:05 by yelazrak          #+#    #+#             */
/*   Updated: 2020/11/16 17:07:52 by mobouzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
#define COREWAR_H
#include "op.h"
// #include "op.c"
#include <unistd.h>
#include "../libft/libft.h"
# include "../include/visualizer.h"
#include <fcntl.h>

// typedef enum
// {
// 	false,
// 	true
// } bool;
/*
** global var
*/
bool G_error;

typedef struct s_process
{
	int pc;
	int carry;
	int id;
	int erorr;
	int size_of_flg;
	int put_value_pos;
	int wait;
	unsigned int regster[16];
	int is_live_more;
	int cycle_count;
	struct s_process *next;

} t_process;

typedef struct s_player
{
	char *name;
	char *comment;
	size_t size_prog;
	int    Starting_point;
	int count_live;
	int id;
	int last_cycle_to_live;
	t_process *process;
	t_header *data_file;
} t_player;

typedef struct s_corewar
{
	unsigned char *arena;
	int cycle;
	int combat;
	int cycle_to_die;
	int nbr_live;
	int dump;
	int nbr_checks;
	int nbr_process;
	int nbr_fighters;
	int cycle_last_check;
	t_player players[4];
} t_corewar;

/*
** funcs in machine_virtuelle
**
*/

void ft_init_process(t_corewar *war);
t_header *ft_cin_file(char *file);
/*
** funcs in machine_virtuelle/calcul
**
*/
char *addr_to_hex(void *addr, size_t size);
int ft_sign(unsigned int s, int size);
int hex(char *value);
int hextodecimal(char val);
unsigned int binary_rev(unsigned int s);

/*
** funcs in machine_virtuelle/arena
**
*/
char_t *ft_get_arena(void);
t_corewar *get_struct(t_corewar *lst);
void ft_print_arena();

/*
** funcs in machine_virtuelle/arena
**
*/

/*
** func exec 
*/

void ft_loop(t_visu *visu);
void ft_exec(t_process *p, t_corewar *war);
/*
** funcs instructoin_assembly 
*/

int ft_live(t_process *p);
int ft_ld(t_process *p);
int ft_st(t_process *p);
int ft_add(t_process *p);
int ft_sub(t_process *p);
int ft_and(t_process *p);
int ft_or(t_process *p);
int ft_xor(t_process *p);
int ft_zjmp(t_process *p);
int ft_ldi(t_process *p);
int ft_sti(t_process *p);
int ft_fork(t_process *p);
int ft_lld(t_process *p);
int ft_lfork(t_process *p);
int ft_aff(t_process *p);
int ft_lldi(t_process *p);

/*
** tools funcs 
**
*/

int get_size_arg(unsigned char flg, int nb_arg, int opcode, int *err);
int get_size_beyt_flag(t_process *p, unsigned char flg, int opcode);
int overrided_pos(int pos, int cur0);
void cpy_reg_to_arena(t_process *p, int cursor0, int size, int reg);
int read_regster(t_process *proc);
void cpy_arena_to_reg(t_process *p, int cursor0, int size, int reg); //(t_corewar *war, t_process *p, int size, char_t r);
unsigned int cpy_arena_to_var(t_process *p, int size, int cursor0, int opcode);
unsigned int return_data_of_arg(t_process *proc, unsigned char flg, int opcode, int cursor0);

/*
**	VISUALIZER FUNCTIONS
*/

int		board(t_corewar *war, t_visu *visu);
void	menu_handler(t_corewar *war, t_visu *visu);
void	event_handler(t_visu *visu);
void	border_maker(t_visu *visu);
void	init_struct(t_visu *visu);
int		event_listenner(void);
void	pause_handler(t_visu *visu);

void		init_colors(t_visu *visu);

#endif
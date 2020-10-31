/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 18:06:05 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/13 18:26:19 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H 

# include "op.h"
# include "./visualizer.h"
# include "../libft/libft.h"
# include <fcntl.h>

typedef struct s_process
{
	int pc;
	int carry;
	int id;
	int		wait;
	unsigned int regster[16];
	int nbr_cycler_live;
	int		cycle_count;
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
	long long  cycle;
	int cycle_to_die;
	int nbr_live;
	int nbr_checks;
	int nbr_process;
	int  nbr_fighters;
	int player_last_live;
	t_player players[4];
} t_corewar;

// typedef enum {0, true} bool;
t_corewar *get_struct(t_corewar *lst);
void ft_print_arena();
unsigned char *ft_get_arena(void);
char *addr_to_hex(void *addr, size_t size);
int ft_sign( unsigned  int s, int size);


int hex(char *value);
char *addr_to_hex(void *addr, size_t size);

/*
** ==> instructions 
*/

int		ft_live(t_process *p);
int		ft_ld(t_process *p);
int		ft_st(t_process *p);
int		ft_add(t_process *p);
int		ft_sub(t_process *p);
int		ft_and(t_process *p);
int		ft_or(t_process *p);
int		ft_xor(t_process *p);
int		ft_zjmp(t_process *p);
int		ft_ldi(t_process *p);
int		ft_sti(t_process *p);
int		ft_fork(t_process *p);
int		ft_lld(t_process *p);
int		ft_lfork(t_process *p);
int		ft_aff(t_process *p);
int		ft_lldi(t_process *p);

/*
**
**
*/

void ft_loop(void);

/*
**
**
*/

int get_flag_2(char_t d, unsigned int *arg, int p);
int get_flag_1(char_t d, unsigned int *arg, int p);
int get_flag_3(char_t d, unsigned int *arg, int p);

int overrided_pos(int pos);
int get_size_of_flag(char_t d, int index, int *ret);
int	 read_regster(int p,t_corewar *war);
unsigned int	binary_rev( unsigned int s);
void ft_exec(t_process *p, t_corewar *war);

unsigned int ldi_cpy(t_process *p, int size);
void cpy_arena_to_reg(t_corewar *war, t_process *p, int size, char_t r);
void cpy_reg_to_arena(t_corewar *war, t_process *p, int size, char_t r);
unsigned int shift_data(char_t d, int *len, t_process *p, int *status, int pos, int shift, int s_dir);
unsigned int shift_byte(char_t d, int *len, t_process *p, int *status, int pos, int shift, int s_dir);
int shift_data_int(char_t d, int *len, t_process *p, int *status, int pos, int shift, int s_dir);

int board(t_corewar *war);

#endif
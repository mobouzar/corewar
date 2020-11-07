/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   battlefield.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 22:04:41 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/13 21:50:39 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"
// #include "../include/op_tab.h"

t_op op_tab[17] =
	{
		{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
		{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
		{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
		{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
		{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
		{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6, "et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
		{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6, "ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
		{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6, "ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
		{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
		{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25, "load index", 1, 1},
		{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25, "store index", 1, 1},
		{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
		{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
		{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50, "long load index", 1, 1}, /**/
		{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
		{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
		{0, 0, {0}, 0, 0, 0, 0, 0}};

void ft_exec(t_process *p, t_corewar *war)
{
	int (*func[])(t_process *) = {ft_live, ft_ld, ft_st, ft_add, ft_sub, ft_and,
								  ft_or, ft_xor, ft_zjmp, ft_ldi, ft_sti, ft_fork, ft_lld, ft_lldi, ft_lfork, ft_aff};
	int i;
	// p->regster[1] = 0x01566600;
	// p->regster[2] = 0xfeffffff;
	p->pc %= MEM_SIZE;
	i = hex(addr_to_hex(&war->arena[p->pc], 1));
	if (i >= 1 && i <= 16)
	{
		
		//  p->wait = 1;
		if (p->cycle_count == op_tab[i - 1].nbr_cycler)
		{ 
			// printf("instructoin =  = %u\n\n", i);
			func[i - 1](p); //
			// printf("rogester4 = %s\n\n", addr_to_hex(&p->regster[3], 4));
			// printf(" \n\nopsitoin  = = %d \n\n", p->pc);
			p->cycle_count = 0;
			// p->wait = 0;
		}
		else
			p->cycle_count++;
	}
	else
		p->pc++;
}

static t_process *Die_Cursor(t_corewar *war, t_process *list_process)
{
	t_process *tmp;
	t_process *first;

	tmp = list_process;
	first = tmp;
	while (list_process)
	{
		 printf("is_live  =  %d  pos_cursor = %d id_plyer   = %d  \n\n", list_process->is_live_more, list_process->pc, list_process->id);
		if (!list_process->is_live_more)
		{

			war->nbr_process--;
			 first = list_process;
			tmp->next = list_process->next;
			//  free(first);
			// list_process = NULL;
			// ft_memdel((void **)&list_process);
			list_process = tmp;
		}
		tmp = list_process;
		if (list_process)
		{
			list_process->is_live_more = 0;
			list_process = list_process->next;
		}
	}
	return tmp;
}

static void ft_Controlle(t_corewar *war)
{
	int i;

	i = -1;
	while (++i < war->nbr_fighters)
	{
		war->players[i].count_live = 0;
		war->players[i].process = Die_Cursor(war, war->players[i].process);
		
	}
	if (war->nbr_live >= NBR_LIVE || war->nbr_checks >= 10)
	{
		war->cycle_to_die -= 50;
		war->nbr_checks = 0;
	}
	else
		war->nbr_checks++;
	war->nbr_live = 0;
}

void ft_loop(void)
{
	int i;
	t_corewar *war;
	t_process *p;

	war = get_struct(0);
	//< MAX_CYCLE
	//  war->arena[800] = 1;
	//  war->arena[800] = 1;
	// war->arena[2000] = 1;
	//  war->arena[2600] = 1;
	//  war->arena[2800] = 1;
	//  war->arena[3000] = 1;
	// war->arena[4000] = 1;
	// war->arena[3300] = 1;
	// war->arena[4088] = 1;
	// war->arena[36] = 1;
	// war->arena[360] = 1;
	// war->arena[3000] = 1;
	// war->arena[3800] = 1;
	// war->arena[4040] = 1;
	//  war->arena[3400] = 1;
	// war->arena[300] = 1;
	// war->arena[2700] = 1;
	// war->arena[2100] = 1;
	// war->arena[2600] = 1;
	// war->arena[2200] = 1;
	// war->arena[4000] = 1;
	// war->arena[900] = 1;
	// war->arena[1200] = 1;
	// war->arena[1400] = 1;
	// war->arena[1600] = 1;
	// war->arena[1800] = 1;
	// war->arena[2000] = 1;
	// war->arena[2200] = 1;
	// war->arena[2100] = 1;
	// war->arena[2300] = 1;
	// war->arena[2400] = 1;

	war->players[0].process->regster[3] = 5445545;

	while (++war->cycle && war->nbr_process)
	{
		i = -1;
		// printf("cycle === %d\n\n", war->cycle);
		while (++i < war->nbr_fighters)
		{
			p = war->players[i].process;
			while (p)
			{
				//  printf("  CYCLE =  %d       position curso11 = %d     cycle_must_be_WAIT  = %d   ID = %d  instarauctoin = %s \n\n",\
				//  war->cycle,  p->pc, p->cycle_count , p->id,   addr_to_hex(&war->arena[p->pc],1));		

				ft_exec(p, war);
				// printf("  CYCLE =  %d       position cursor22 = %d\n\n",war->cycle,  p->pc);
				// printf("value regster = %s\n\n", addr_to_hex(&p->regster[3], 4));
				p = p->next;
			}
		}
		if (war->cycle == (war->cycle_last_check + war->cycle_to_die ) ||  war->cycle_to_die < 1)
		{
			war->cycle_last_check = war->cycle;
			printf("\n\ncycle  = %d       9ABLEnbrprocess = %d \n\n", war->cycle, war->nbr_process);
			ft_Controlle(war);
			printf("\n\ncycle  = %d       nbrprocess = %d \n\n", war->cycle, war->nbr_process);
		}
		// if (war->cycle == 2002)
		// 	printf("\n\n  222222            nbr_cycle out = %d					cycle_die == %d   \
	 	// 		nbr_cursor == %d	    cycle_last_check == %d     nbr_check ==  %d     nbr_process    = %d  \n\n",
		//    war->cycle, war->cycle_to_die, war->players[0].process->pc, war->cycle_last_check, war->nbr_checks, war->nbr_process);
	}

	printf("\n\nnbr_cycle out = %d					cycle_die == %d   \
	 nbr_cursor == %d	    cycle_last_check == %d     nbr_check ==  %d     nbr_process    = %d  \n\n",
		   war->cycle, war->cycle_to_die, war->players[0].process->pc, war->cycle_last_check, war->nbr_checks, war->nbr_process);
	ft_print_arena();
}
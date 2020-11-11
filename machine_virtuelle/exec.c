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





// .name		"Sliders"
// .comment	"And the winner is ..."

// 		sti     r1,%:leon_live,%1
// 		sti	r1,%:fork1,%1
// 		sti	r1,%:fork2,%1
// 		sti	r1,%:roger_live,%1
// 		sti	r1,%:torp,%1
// 		sti	r1,%:torp_,%1
// 		sti	r1,%:fork3,%1
// 		sti	r1,%:fork_live,%1
// 		sti	r1,%:live,%1
// 		sti	r1,%:live,%6
// 		sti	r1,%:live,%11
// 		sti	r1,%:live,%16
// 		sti	r1,%:live,%21
// 		sti	r1,%:live,%26
// 		sti	r1,%:live,%31
// 		sti	r1,%:live,%36
// 		sti	r1,%:live,%41
// 		sti	r1,%:live,%46
// 		sti	r1,%:live,%51
// 		sti	r1,%:live,%56
// 		sti	r1,%:live,%61
// 		sti	r1,%:live,%66
// 		sti	r1,%:live,%71
// 		sti	r1,%:live,%76
// 		sti	r1,%:live,%81
// 		sti	r1,%:live,%86
// 		sti	r1,%:live,%91
// 		sti	r1,%:live,%96
// 		sti	r1,%:live,%101	
// 		sti	r1,%:live,%106
// 		add r4, r4, r6
// 		sti	r1,%:live,%111
// 		sti	r1,%:live,%116
// 		ld	%48,r14	
// 		ld      %4,r4
// 		ld      %48,r6
// 		ld	%48,r13
// 		ld	%:leon_ecrit,r8
// 		ld	%330,r9
// 		ld	%:roger,r12
// 		sub	r12,r8,r12
// fork1:		live	%42
// fork2:		live	%42
// fork3:		live	%42
// 		ld	%0,r15
// 		ld %0 ,r8
// 		ld %0 ,r9
// 		add	r8,r9,r8	
// 		zjmp	%:torp
// leon:		ld      %0,r2
// leon_live:	live    %42
// 		ldi     %:leon,r2,r3
// 		sti     r3,r8,r2
// 		add     r2,r4,r2
// 		xor     r13,r2,r7
// 		ld %0 ,r8
// 		ld %0 ,r9
// 		add	r8,r9,r8
// 		zjmp    %415
// 		ld      %0,r15
// leon_ecrit:	zjmp    %:leon_live
// roger:		ld	%0,r10
// roger_live:	live	%42
// 		ldi	%:roger,r10,r11
// 		sti	r11,r12,r10
// 		add	r10,r4,r10
// 		xor	r6,r10,r7
// 		zjmp	%-361
// 		ld	%0,r15
// roger_ecrit:	zjmp	%:roger_live
// torp:		live	%42	
// torp_:		live	%42
// 		ld	%0,r15
// 		zjmp	%:torp
// live:		live	%42
// 		live	%42
// 		live	%42
// 		live	%42
// 		live	%42
// 		live	%42
// 		live	%42
// 		live	%42
// 		live	%42
// 		live	%42
// 		live	%42
// 		live	%42
// 		live	%42
// 		live	%42
// 		live	%42
// 		live	%42
// 		live	%42
// 		live	%42
// 		live	%42
// 		live	%42
// 		live	%42
// 		live	%42
// 		live	%42
// 		live	%42	
// 		zjmp	%:live
// fork_live:	live	%42
// 		ld	%0,r15
// 		ld %0 ,r8
// 		ld %0 ,r9
// 		add	r8,r9,r8
// 		zjmp	%55
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
		if ((1 + p->cycle_count) == op_tab[i - 1].nbr_cycler)
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

void ft_test(t_process *p)
{
	t_corewar *war;

	war = get_struct(0);
	if (!p)
	{
		printf("\n\nprocess_is NULL\n\n");
		return;
	}
	while (p)
	{
		if (p->is_live_more != -1)
			printf("\n\nTESTTTTT = = = is_live  =  %d  pos_cursor = %d id_plyer   = %d         CYCLE = %d       	nbr_process = %d \n\n",p->is_live_more, p->pc, p->id, war->cycle, war->nbr_process);

		p = p->next;
	}
}

static t_process *Die_Cursor(t_corewar *war, t_process *list_process)
{

	t_process *head;

	
	head = list_process;
	 t_process *tmp = NULL;

	while (list_process != NULL)
	{
		//printf("is_live  =  %d  pos_cursor = %d id_plyer   = %d     nbr_process = %d    cycle = %d \n\n", list_process->is_live_more, list_process->pc, list_process->id, war->nbr_process, war->cycle);
		if (!list_process->is_live_more)
		{

			war->nbr_process--;
			if (!tmp)
			{
				head = list_process->next;
				tmp = list_process;
				list_process = list_process->next;
				free(tmp);
				// ft_memdel((void **)&tmp);
				tmp = NULL;
			}
			else
			{
				tmp->next = list_process->next;
				// ft_memdel((void **)&list_process);
				free(list_process);
				list_process = NULL;
				list_process = tmp->next;
			}
		}
		else
		{
			list_process->is_live_more = 0;
			tmp = list_process;
			list_process = list_process->next;
		}
	}

	// while (list_process)
	// {
	// 	//printf("9able is_live  =  %d  pos_cursor = %d id_plyer   = %d     nbr_process = %d    cycle = %d \n\n", list_process->is_live_more, list_process->pc, list_process->id, war->nbr_process, war->cycle);
	// 	if (list_process->is_live_more == 0)
	// 	{

	// 		war->nbr_process--;
	// 		list_process->is_live_more = -1;
		
	// 	}
	// 	else if (list_process->is_live_more == 1)
	// 	{
	// 		list_process->is_live_more = 0;	
		
	// 	}
	// //	printf(" ba3eddd   is_live  =  %d  pos_cursor = %d id_plyer   = %d     nbr_process = %d    cycle = %d \n\n", list_process->is_live_more, list_process->pc, list_process->id, war->nbr_process, war->cycle);

	// 	list_process = list_process->next;
	// }

	// ft_putendl("\n\n\n\ncursosr\n\n");
	// ft_test(head);
	// 	ft_putendl("\n\n\n\ncursosr\n\n");
	return head;
}

static void ft_Controlle(t_corewar *war)
{
	int i;

	i = -1;
	while (++i < war->nbr_fighters)
	{
		war->players[i].count_live = 0;
		war->players[i].process = Die_Cursor(war, war->players[i].process);
		// ft_putendl("\n\ntest_\n\n");
		// ft_test(war->players[0].process );
		// ft_putendl("\n\nend_test_\n\n");

	}
	if (war->nbr_live >= NBR_LIVE || war->nbr_checks == 9)
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

	//war->players[0].process->regster[3] = 5445545;

	while (++war->cycle < 17457 && war->nbr_process)
	{
		i = -1;
		// ft_putendl("hehe\n\n");
		//  printf("cycle === %d    NBR_PROCESS   =  %d    instarcution   = %s   \n\n", war->cycle, war->nbr_process, addr_to_hex(&war->arena[war->players[0].process->pc], 1));//
		// ft_putendl("hehe22\n\n");

	
		while (++i < war->nbr_fighters)
		{
			// ft_putendl("playerdebuttt\n\n");
			p = war->players[i].process;
			while (p != NULL)
			{
				// ft_putendl("player_RUN\n\n");
				// printf("n\n\n  plyer_run_ID  = %d     nbr_process = %d    cycler = %d \n\n", p->id,  war->nbr_process, war->cycle);
				// printf(" \n\n CYCLE =  %d       position curso11 = %d     cycle_must_be_WAIT  = %d   ID = %d  instarauctoin = %s \n\n",
				// 	   war->cycle, p->pc, p->cycle_count, p->id, addr_to_hex(&war->arena[p->pc], 1));
				if(p->is_live_more != -1)
				{
					ft_exec(p, war);

				}
				//ft_putendl("player_RUN_enad_EXECCCC\n\n");
				// printf("  CYCLE =  %d       position cursor22 = %d\n\n",war->cycle,  p->pc);
				// printf("value regster = %s\n\n", addr_to_hex(&p->regster[3], 4));
				p = p->next;
			}
			//ft_putendl("playerend\n\n");
		}

		if (war->cycle + 1 == (war->cycle_last_check + war->cycle_to_die) || war->cycle_to_die < 1)
		{
			war->cycle_last_check = war->cycle;

					printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
				printf("\n\n+++++++++++++++++++++++++++++++++++9ABELLLE    nbr_cycle out = %d					cycle_die == %d   \
	 nbr_cursor == %d	    cycle_last_check == %d     nbr_check ==  %d     nbr_process    = %d   nbr_live_totall  = %d \n\n",
		   war->cycle, war->cycle_to_die, 0, war->cycle_last_check, war->nbr_checks, war->nbr_process, war->nbr_live);
			printf("\n\ncycle  = %d     LEnbrprocessDAKHELO = %d \n\n", war->cycle, war->nbr_process);


			ft_Controlle(war);/////


			printf("\n\ncycle  = %d       LYBA9INE = nbrprocess = %d \n\n", war->cycle, war->nbr_process);

			printf("\n\n   BA3EDEDDDE   nbr_cycle out = %d					cycle_die == %d   \
	 nbr_cursor == %d	    cycle_last_check == %d     nbr_check ==  %d     nbr_process    = %d   nbr_live_totall  = %d          nbr_fork_ ====  %d\n\n",
		   war->cycle, war->cycle_to_die, 0, war->cycle_last_check, war->nbr_checks, war->nbr_process, war->nbr_live , war->dg);
	
		}
		// if (war->cycle == 2002)
		// 	printf("\n\n  222222            nbr_cycle out = %d					cycle_die == %d   \
	 	// 		nbr_cursor == %d	    cycle_last_check == %d     nbr_check ==  %d     nbr_process    = %d  \n\n",
		//    war->cycle, war->cycle_to_die, war->players[0].process->pc, war->cycle_last_check, war->nbr_checks, war->nbr_process);
	}


	printf("\n\nnbr_cycle out = %d					cycle_die == %d   \
	 nbr_cursor == %d	    cycle_last_check == %d     nbr_check ==  %d     nbr_process    = %d  \n\n",
		   war->cycle, war->cycle_to_die, war->players[0].process->pc , war->cycle_last_check, war->nbr_checks, war->nbr_process);
	ft_print_arena();
}
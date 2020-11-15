#include "../include/corewar.h"

void	ft_init_process(t_corewar *war)
{
	int	i;
	unsigned int index[] = {0xffffffff, 0xfffffffe,0xfffffffd,0xfffffffc};

	i = -1;
	war->nbr_process =  war->nbr_fighters;
	war->cycle_to_die = 1536;
	while (++i < war->nbr_fighters)
	{
		if (!(war->players[i].process = (t_process*)malloc(sizeof(t_process))))
			return ;
		ft_memset((void*)war->players[i].process, 0, sizeof(t_process));
		war->players[i].process->id = i + 1;
		war->players[i].process->regster[0] = index[i];
		war->players[i].process->pc = war->players[i].Starting_point;
	}
}


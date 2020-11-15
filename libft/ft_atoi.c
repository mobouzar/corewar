#include <stdio.h>


int		ft_atoi(const char *str)
{
	unsigned int	a;
	int				s;
	int				i;

	a = 0;
	s = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' ||
	str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-')
	{
		i++;
		s = -1;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		a = a * 10 + (str[i++] - '0');
	return ((int)(s * a));
}

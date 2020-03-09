
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>


int	main(int ac, char **av)
{
	int		fd;
	char	tab[4];
	int		i;

	fd = open(av[1], O_RDONLY);
	i   = 3;
	while (i >= 0)
		read(fd, tab + i--, 1);
	printf("%d\n", *(int *)tab);
	close(fd);

}

#ifndef MINI_PAINT_H

# define MINI_PAINT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_conf
{
	int		width;
	int		height;
	char	bg;
}	t_conf;

typedef struct s_circle
{
	float	x;
	float	y;
	float	radius;
	char	bg;
	char	type;
}	t_circle;

void	ft_putchar(char c);
void	ft_putstr(char *s);

#endif

#ifndef MICRO_PAINT_H

# define MICRO_PAINT_H

// # include <math.h>
# include <stdio.h>
# include <stdlib.h>
// # include <string.h>
# include <unistd.h>

typedef struct	s_conf
{
	int	width;
	int	height;
	char	bg;
}				t_conf;

typedef struct	s_rect
{
	char	type;
	int	x;
	int	y;
	int	width;
	int	height;
	char	bg;
}				t_rect;

int				ft_strlen(char *str);
void			ft_putchar(char c);
void			ft_putstr(char *str);

#endif

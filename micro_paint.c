#include "micro_paint.h"

typedef struct	s_conf {
		int		width;
		int		height;
		char	bg;
}				t_conf;

typedef struct	s_rect {
		char	type;
		int		x;
		int		y;
		int		width;
		int		height;
		char	bg;
}				t_rect;

void	ft_init_scr(t_conf *c)
{
	c->width = -1;
	c->height = -1;
	c->bg = 0;
}

void	ft_init_rect(t_rect *r)
{
	r->type = -1;
	r->x = -1;
	r->y = -1;
	r->width = -1;
	r->height = -1;
	r->bg = 0;
}

char	**ft_new_map(int w, int h, char c)
{
	int		i;
	int		j;
	char	**m;

	i = 0;
	m = malloc(h * sizeof(char *) + 1);
	while (i < h)
	{
		j = 0;
		m[i] = malloc(w * sizeof(char) + 1);
		while (j < w)
		{
			m[i][j] = c;
			j++;
		}
		m[i][j] = '\0';
		i++;
	}
	m[i] = "\0";
	return (m);
}

void	ft_print_map(char **m, int width, int height)
{
	int	i;
	int	j;

	ft_putstr("---\n");
	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			ft_putchar(m[i][j]);
			j++;
		}
		ft_putchar('\n');
		i++;
	}
	ft_putstr("---\n");
}

void	ft_free_map(char ***m, int h)
{
	int	i;

	i = 0;
	if (***m)
	{
		while (i < h)
		{
			free(*m[i]);
			*m[i] = NULL;
			i++;
		}
		free(*m);
		*m = NULL;
	}
}

void	ft_draw_in_map(char ***m, t_rect *r, t_conf c)
{
	int	i;
	int	j;

	i = 0;
	while (i <= r->height && i < c.height)
	{
		j = 0;
		while (j <= r->width && j < c.width)
		{
			if (r->type = 'r')
			m[i][j] = r->bg;
			j++;
		}
		i++;
	}
}

/*
** return 1 on error
*/
int		main(int argc, char *argv[])
{
	FILE	*f;
	char	*op_file;
	char	**map;
	t_conf	conf;
	t_rect	rect;
	int		ret;

	if (argc == 2)
	{
		op_file = argv[1];
		if ((f = fopen(op_file, "r")) != NULL)
		{
			// read file with fscanf
			// WIDTH HEIGHT BACKGROUND_CHAR
			ft_init_scr(&conf);
			ret = fscanf(f, "%d %d %c\n", &conf.width, &conf.height, &conf.bg);

			// screen information invalid or insufficient
			if (ret < 3)
			{
				ft_putstr("Error: Operation file corrupted\n");
				return (1);
			}

			// allocate map and fill map
			map = ft_new_map(conf.width, conf.height, conf.bg);

			printf("vars : %d\n", ret);
			printf("screen w : %d, h : %d, char : %c\n",
				conf.width, conf.height, conf.bg);

			// r X Y WIDTH HEIGHT CHAR : empty rectangle
			// R X Y WIDTH HEIGHT CHAR : filled rectangle
			// ft_init_rect(&rect);
			while ((ret = fscanf(f, "%c %d %d %d %d %c\n",
					&rect.type, &rect.x, &rect.y, &rect.width,
					&rect.height, &rect.bg)) > 0)
			{
				// ft_init_rect(&rect);
								printf("vars : %d\n", ret);
				printf("|%c| %d %d %d %d |%c|\n",
					rect.type, rect.x, rect.y, rect.width, rect.height, rect.bg);
				if (ret == 6)
				{
					ft_draw_in_map(&map, &rect, conf);
				}
				else
				{
					ft_free_map(&map, conf.height);
					// invalid rectangle information
					ft_putstr("Error: Operation file corrupted\n");
					return (1);
				}
			}
			ft_print_map(map, conf.width, conf.height);
			ft_free_map(&map, conf.height);
		}
		else
		{
			// cant open file
			ft_putstr("Error: Operation file corrupted\n");
			return (1);
		}
	}
	else
	{
		// invalid number of arguments
		ft_putstr("Error: argument");
		return (1);
	}
	// return 0 at the end
	return (0);
}

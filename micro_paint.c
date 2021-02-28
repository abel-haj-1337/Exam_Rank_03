#include "micro_paint.h"

char	**g_map;

void	ft_free_map(int len)
{
	int	i;

	if (g_map)
	{
		i = 0;
		while (i < len)
		{
			free(g_map[i]);
			g_map[i] = NULL;
			i++;
		}
		free(g_map);
		g_map = NULL;
	}
}

char	**ft_init_map(int width, int height, char c)
{
	int	i;
	int	j;

	g_map = malloc(height * sizeof(char *));

	if (!g_map)
	{
		return (NULL);
	}

	i = 0;
	while (i < height)
	{
		g_map[i] = malloc(width * sizeof(char) + 1);

		if (!g_map[i])
		{
			ft_free_map(i + 1);
			return (NULL);
		}

		j = 0;
		while (j < width)
		{
			g_map[i][j] = c;
			j++;
		}
		g_map[i][j] = '\0';
		i++;
	}
	return (g_map);
}

void	ft_draw_in_map(t_rect r, t_conf c)
{
	int	i;
	int	j;

	i = r.y;
	while (i <= r.height + 1 && i < c.height)
	{
		j = r.x;
		while (j <= r.width + 1 && j < c.width)
		{
			if (r.type == 'R')
			{
				g_map[i][j] = r.bg;
			}
			else if (r.type == 'r'
					&& ((i == r.height + 1 || i == r.y)
					|| (j == r.width + 1 || j == r.x)))
			{
				g_map[i][j] = r.bg;
			}
			j++;
		}
		i++;
	}
}

void	ft_print_map(int w, int h)
{
	int	i;
	int	j;

	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			ft_putchar(g_map[i][j]);
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}

int	main(int argc, char *argv[])
{
	int	ret;
	FILE *file;
	t_conf	conf;
	t_rect	rect;

	if (argc == 2)
	{
		// open operation file
		file = fopen(argv[1], "r");
		if (!file)
		{
			ft_putstr("Error: Operation file corrupted\n");
			return (1);
		}

		// store map configuration
		ret = fscanf(file, "%d %d %c\n", &conf.width, &conf.height, &conf.bg);

		// error
		if (ret != 3)
		{
			ft_putstr("Error: Operation file corrupted\n");
			return (1);
		}

		// allocating map
		g_map = ft_init_map(conf.width, conf.height, conf.bg);
		if (!g_map)
			ft_putstr("Error: Well crap\n");

		while (ret > 0)
		{
			// read data
			ret = fscanf(file, "%c %d %d %d %d %c\n",
				&rect.type, &rect.x, &rect.y,
				&rect.width, &rect.height, &rect.bg);

			// data is correct
			if (ret == 6)
			{
				// the important part
				ft_draw_in_map(rect, conf);
			}
			else if (ret != -1)
			{
				ft_free_map(conf.height);
				ft_putstr("Error: Operation file corrupted\n");
				return (1);
			}
		}

		// output the map
		ft_print_map(conf.width, conf.height);
		// cleaning
		ft_free_map( conf.height);
	}
	// if more arguments or less
	else
	{
		ft_putstr("Error: argument");
		return (1);
	}
	return (0);
}
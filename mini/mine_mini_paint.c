#include "mine_mini_paint.h"

char	**ft_init_map(int w, int h, char c)
{
	int	i;
	int	j;
	char	**m;

	m = malloc(h * sizeof(char *));

	if (m)
	{
		i = 0;
		while (i < h)
		{
			j = 0;
			m[i] = malloc(w * sizeof(char));
			while (j < w)
			{
				m[i][j] = c;
				j++;
			}
			m[i][j] = 0;
			i++;
		}
	}

	return (m);
}

void	ft_free_map(char ***m, int h)
{
	int	i;

	i = 0;
	while (i < h)
	{
		free((*m)[i]);
		i++;
	}
	free(*m);
}

void	ft_print_map(char **m, int w, int h)
{
	int	i;
	int	j;

	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			printf("%c", m[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	ft_draw_in_map(char ***m, t_conf co, t_circle ci)
{
	int	i;
	int	j;

	i = 0;
	while (i)
	{
		j = 0;
		while (j)
		{
			j++;
		}
		i++;
	}
}

// TODO
	// replace printf with putchar/str
	// remove //debbuging
	// draw in map
int		main(int argc, char *argv[])
{
	int	ret;
	t_conf	co;
	t_circle	ci;
	FILE	*file;
	char	**map;

	if (argc == 2)
	{
		file = fopen(argv[1], "r");
		if (!file)
		{
			ft_putstr("Error: Operation file corrupted\n");
			return (1);
		}

		// read map configuration
		ret = fscanf(file, "%d %d %c\n", &co.width, &co.height, &co.bg);

		// debugging
			printf("%d: %d %d %c\n",
				ret, co.width, co.height, co.bg);

		if (ret != 3 || co.width <= 0 || co.width > 300
			|| co.height <= 0 || co.height > 300)
		{
			ft_putstr("Error: Operation file corrupted\n");
			return (1);
		}

		// init map with given configuration
		map = ft_init_map(co.width, co.height, co.bg);
		// print map
		ft_print_map(map, co.width, co.height);

		// read circles dimensions
		while ((ret = fscanf(file, "%c %f %f %f %c\n",
				&ci.type, &ci.x, &ci.y, &ci.radius, &ci.bg)) > 0)
		{
			// all 5 dimensions are given
			if (ret == 5)
			{

				// debuggin
				printf("%d: %c %f %f %f %c\n",
					ret, ci.type, ci.x, ci.y, ci.radius, ci.bg);

				// draw in map
				ft_draw_in_map(&map, co, ci);
			}
			else
			{
				ft_putstr("Error: Operation file corrupted\n");
				return (1);
			}
		}

		// debugging
		printf("ret %d\n", ret);

		// prevent leaks
		ft_free_map(&map, co.height);
	}
	else
	{
		ft_putstr("Error: argument\n");
		return (1);
	}
	return (0);
}

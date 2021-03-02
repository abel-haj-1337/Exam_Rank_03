#include "mine_mini_paint.h"

char	**ft_init_map(int w, int h, char c)
{
	int		i;
	int		j;
	char	**m;

	m = malloc(h * sizeof(char *));
	if (m)
	{
		i = 0;
		while (i < h)
		{
			j = 0;
			m[i] = malloc(w * sizeof(char) + 1);
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

void	ft_draw_in_map(char ***m, t_conf co, t_circle ci)
{
	int		i;
	int		j;
	float	d;

	i = 0;
	while (i < co.height)
	{
		j = 0;
		while (j < co.width)
		{
			// calculate distance between current position and circle center
			d = sqrt((j - ci.x) * (j - ci.x) + (i - ci.y) * (i - ci.y));
			if (d < 0)
				d *= -1;

			// if distance is equal or lower to circle center
			if (d <= ci.radius)
			{
				// if circle is not empty
				// or
				// current position is at the border of the circle
				if (ci.type == 'C' || floor(d) == ci.radius
					|| ceil(d) == ci.radius)
					(*m)[i][j] = ci.bg;
			}
			j++;
		}
		i++;
	}
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
			ft_putchar(m[i][j]);
			j++;
		}
		ft_putchar('\n');
		i++;
	}
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

int	main(int argc, char *argv[])
{
	int			ret;
	t_conf		co;
	t_circle	ci;
	FILE		*file;
	char		**map;

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

		if (ret != 3 || co.width <= 0 || co.width > 300
			|| co.height <= 0 || co.height > 300)
		{
			ft_putstr("Error: Operation file corrupted\n");
			return (1);
		}

		// init map with given configuration
		map = ft_init_map(co.width, co.height, co.bg);

		while (ret > 0)
		{
			// read circles dimensions
			ret = fscanf(file, "%c %f %f %f %c\n",
					&ci.type, &ci.x, &ci.y, &ci.radius, &ci.bg);

			// all 5 dimensions are given
			if (ret == 5)
			{
				if (ci.x < 0 || ci.y < 0 || ci.radius <= 0
					|| (ci.type != 'c' && ci.type != 'C'))
				{
					ft_free_map(&map, co.height);
					ft_putstr("Error: Operation file corrupted\n");
					return (1);
				}
				ft_draw_in_map(&map, co, ci);
			}
			else if (ret != -1)
			{
				ft_putstr("Error: Operation file corrupted\n");
				return (1);
			}
		}

		ft_print_map(map, co.width, co.height);

		// no leaks tolarated
		ft_free_map(&map, co.height);
	}
	else
	{
		ft_putstr("Error: argument\n");
		return (1);
	}
	return (0);
}

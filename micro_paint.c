#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		ft_putchar(s[i]);
		i++;
	}
}

void	ft_free_map(char ***m, int len)
{
	int	i;

	if (m)
	{
		i = 0;
		while (i < len)
		{
			free(*m[i]);
			*m[i] = NULL;
			i++;
		}
		free(*m);
		*m = NULL;
	}
}

char	**ft_init_map(int width, int height, char c)
{
	int	i;
	int	j;
	char	**m;

	m = malloc(height * sizeof(char *));

	if (!m)
	{
		printf("shit1\n");
		return (NULL);
	}

	i = 0;
	while (i < height)
	{
		m[i] = malloc(width * sizeof(char) + 1);

		if (!m[i])
		{
			printf("shit2\n");
			ft_free_map(&m, i + 1);
			return (NULL);
		}

		j = 0;
		while (j < width)
		{
			m[i][j] = c;
			j++;
		}
		m[i][j] = '\0';
		i++;
	}
}

void	ft_draw_in_map(char ***m, t_rect r, t_conf c)
{
	int	i;
	int	j;

	i = r.y;
	while (i <= r.height && i < c.height)
	{
		j = r.x;
		while (j <= r.width && j < c.width)
		{
			printf("%d %d\n", i, j);
			if (r.type == 'R' ||
				(r.type == 'r' &&
				(j == r.x + r.width || i == r.y, + r.height)))
				*m[i][j] = r.bg;
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

int	main(int argc, char *argv[])
{
	int	ret;
	int	fd;
	FILE *file;
	char	**map;
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
		map = ft_init_map(conf.width, conf.height, conf.bg);
		if (!map)
			ft_putstr("Error: Well crap\n");

		ft_print_map(map, conf.width, conf.height);
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
				ft_draw_in_map(&map, rect, conf);
			}
			else
			{
				ft_free_map(&map, conf.height);
				ft_putstr("Error: Operation file corrupted\n");
				return (1);
			}
		}

		// output the map
		ft_print_map(map, conf.width, conf.height);
		// cleaning
		ft_free_map(&map, conf.height);
	}
	// if more arguments or less
	else
	{
		ft_putstr("Error: argument");
		return (1);
	}
	return (0);
}
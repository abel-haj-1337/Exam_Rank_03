#include "mine_mini_paint.h"

int		main(int argc, char *argv[])
{
	int	ret;
	t_conf	co;
	t_circle	ci;
	FILE	*file;

	if (argc != 2)
	{
		file = fopen(argv[1], "r");
		if (!file)
		{
			ft_putstr("Error: Operation file corrupted\n");
			return (1);
		}

		ret = fscanf("%d %d %c\n", &co.width, &co.height, &co.bg);

			printf("%d: %d %d %c\n",
				ret, co.width, co.height, co.bg);

		if (ret != 3 || co.width <= 0 || co.width > 300
			|| co.height <= 0 || co.height > 300)
		{
			ft_putstr("Error: Operation file corrupted\n");
			return (1);
		}

		// read circles
		while ((ret = fscanf("%c %f %f %f %c",
				&ci.type, &ci.x, &ci.y, &ci.radius, &ci.bg)) > 0)
		{
			printf("%d: %c %f %f %f %c\n",
				ret, ci.type, ci.x, ci.y, ci.radius, ci.bg);
		}
	}
	else
	{
		ft_putstr("Error: argument\n");
		return (1);
	}

	return (0);
}

#include "mini_paint.h"

int		main(int argc, char *argv[])
{
	int	ret;
	FILE	*file;

	if (argc != 2)
	{
		file = fopen(argv[1], "r");
		if (!file)
		{
			ft_putstr("Error: Operation file corrupted\n");
			return (1);
		}

		// There must be one space between each variable in a line?
	}
	else
	{
		ft_putstr("Error: argument\n");
		return (1);
	}

	return (0);
}

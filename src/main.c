#include "../../includes/cube3d.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		error_arg;
		return (1);
	}
    init(&data);
	parse(argv[1], &data);
	start_game(&data);
	free_game(&data);
	return (0);
}

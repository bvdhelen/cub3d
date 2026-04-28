#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int	fd;
	char *file;

	if (argc != 2)
	{
		error_arg();
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		error("incorrect file\n");
		return (1);
	}
	file = get_next_line(fd);
	while (file)
	{
		if (parse_elements(file, &data) == -1)
		{
			error("misconfiguration file\n");
			close(fd);
			return (1);
		}
		free(file);
		file = get_next_line(fd);
	}
	printf("hola\n");
    //init(&data);
	//parse(argv[1], &data);
	//start_game(&data);
	//free_game(&data);
	close(fd);
	return (0);
}

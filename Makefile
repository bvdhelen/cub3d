# Nombre del archivo de la biblioteca
NAME = cub3d

# Compilador y banderas de compilación
CC = cc
FLAGS_1 = -Wall -Werror -Wextra
FLAGS_2 = -Imlx_linux -O3#?

# Linkeo
LINK = -L./mlx_linux -l:libmlx.a -lXext -lX11 -lm -lz

# Rutas de bibliotecas auxiliares
LIBFT_DIR = ./src/aux/libft/
GNL_DIR = ./src/aux/gnl/

# Archivo de encabezado / Inclusión de las bibliotecas
# -L ./libft sirve para decirle donde buscar la biblioteca
# -lft = libft.a sirve para indicar que biblioteca enlazar
INCLUDE = ./includes/cub3d.h
INCLUDE_LIBFT = -L LIBFT_DIR -lft
INCLUDE_GNL = -L GNL_DIR -l:get_next_line.a
INCLUDE_MLX = -Lmlx_linux -lmlx

# Definir códigos de color
BLACK = \033[0;30m
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN =  \033[0;36m
WHITE = \033[0;37m
GREY = \033[0;90m
RESET = \033[0m

# Archivos fuente y archivos objeto
SRC =	main.c \
		init.c \
		parse.c \
		error.c \

OBJ = $(SRC:.c=.o)

# Regla para compilar fdf con libft, ft_printf y get_next_line
# -C sirve para cambiar UNA VEZ al directorio especificado antes de ejecutar el Makefile
$(NAME): header $(OBJ)
	@make -C $(LIBFT_DIR) --no-print-directory
	@make -C $(GET_NEXT_LINE_DIR) --no-print-directory
	@$(CC) $(FLAGS_1) $(FLAGS_2) $(OBJ) -o $(NAME) \
		$(LINK) \
		$(INCLUDE) \
		$(INCLUDE_MLX) \
		$(INCLUDE_LIBFT) \
		$(INCLUDE_GNL)
	@echo
	@echo "$(GREEN)<<< cub3d compiled >>>$(RESET)"
	@echo

# Regla principal que lo compila todo
all: $(NAME)

# Eliminar todos los archivos .o y .a
clean:
	@rm -f $(OBJ)
	@$(MAKE) clean -C $(LIBFT_DIR) --no-print-directory
	@$(MAKE) clean -C $(GET_NEXT_LINE_DIR) --no-print-directory
	@echo
	@echo "$(CYAN)<<< clean complete >>>$(RESET)"
	@echo

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR) --no-print-directory
	@$(MAKE) fclean -C $(GET_NEXT_LINE_DIR) --no-print-directory
	@echo "$(BLUE)<<< full clean complete >>>$(RESET)"
	@echo

re: fclean all

# ASCII Art
header:
	@echo
	@echo "$(GREY)           __    _ __                       __                  ";
	@echo "$(GREY)    ____  / /_  (_) /___  _________  ____  / /_  ___  __________";
	@echo "$(GREY)   / __ \/ __ \/ / / __ \/ ___/ __ \/ __ \/ __ \/ _ \/ ___/ ___/";
	@echo "$(GREY)  / /_/ / / / / / / /_/ (__  ) /_/ / /_/ / / / /  __/ /  (__  ) ";
	@echo "$(GREY) / .___/_/ /_/_/_/\____/____/\____/ .___/_/ /_/\___/_/  /____/  ";
	@echo "$(GREY)/_/        ____  _________  __  _/_/_  _____/ /_                ";
	@echo "$(GREY)          / __ \/ ___/ __ \/ / / / _ \/ ___/ __/                ";
	@echo "$(GREY)         / /_/ / /  / /_/ / /_/ /  __/ /__/ /_                  ";
	@echo "$(GREY)        / .___/_/   \____/\__, /\___/\___/\__/                  ";
	@echo "$(GREY)       /_/               /____/                                 ";
	@echo " $(RESET) "
	@echo

# Indica que las siguientes reglas no son archivos reales
.PHONY: all clean fclean re header
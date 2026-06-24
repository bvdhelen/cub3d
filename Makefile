# Nombre del archivo de la biblioteca
NAME = cub3D

# Compilador y banderas de compilación
CC = cc
CFLAGS = -Wall -Werror -Wextra -O3 -g3 -fsanitize=address
INCLUDES = -I./includes -Imlx_linux -I./includes/aux/libft -I./includes/aux/gnl

# Linkeo
MLX_DIR = ./mlx_linux
MLX = -L$(MLX_DIR) -l:libmlx.a -lXext -lX11 -lm -lz

# Rutas de bibliotecas auxiliares
LIBFT_DIR = ./includes/aux/libft
GNL_DIR = ./includes/aux/gnl

# Archivo de encabezado / Inclusión de las bibliotecas
# -L ./libft sirve para decirle donde buscar la biblioteca
# -lft = libft.a sirve para indicar que biblioteca enlazar
LIBFT = -L$(LIBFT_DIR) -lft
GNL = -L$(GNL_DIR) -l:get_next_line.a

# Carpeta para objetos
OBJ_DIR = obj

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
SRC =	src/main.c \
		src/utils/error.c \
		src/utils/free.c \
		src/utils/utils.c \
		src/parse/parse.c \
		src/parse/parse_map.c \
		src/parse/parse_color.c \
		src/parse/parse_elements.c \
		src/parse/map_utils1.c \
		src/parse/map_utils2.c \
		src/parse/load_textures.c \
		src/init/init.c \
		src/hooks/hooks.c \
		src/render/drawing.c \
		src/render/drawing_utils.c \
		src/render/move.c \
		src/render/render.c \
		src/render/render_utils.c \
		src/render/minimap.c \
		src/render/dda.c \

OBJ = $(SRC:src/%.c=$(OBJ_DIR)/%.o)

# Regla principal que lo compila todo
all: $(NAME)

# Regla para compilar fdf con libft, ft_printf y get_next_line
# -C sirve para cambiar UNA VEZ al directorio especificado antes de ejecutar el Makefile
$(NAME): header $(OBJ)
	@make -C $(LIBFT_DIR) --no-print-directory
	@make -C $(GNL_DIR) --no-print-directory
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) -o $(NAME) \
		-L$(LIBFT_DIR) -lft \
		-L$(GNL_DIR) -l:get_next_line.a \
		$(MLX)
	@echo
	@echo "$(GREEN)<<< cub3D compiled >>>$(RESET)"
	@echo

# Regla para crear los archivos objeto (.o)
# -c indica que se debe commpilar el código sin enlazar (crear solo el .o)
# $< representa el archivo de entrada (el .c que se está compilando)
# -o $@ especifica el nombre del archivo de salida que se está generando
$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Eliminar todos los archivos .o y .a
clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) clean -C $(LIBFT_DIR) --no-print-directory
	@$(MAKE) clean -C $(GNL_DIR) --no-print-directory
	@echo
	@echo "$(CYAN)<<< clean complete >>>$(RESET)"
	@echo

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR) --no-print-directory
	@$(MAKE) fclean -C $(GNL_DIR) --no-print-directory
	@echo "$(BLUE)<<< full clean complete >>>$(RESET)"
	@echo

re: fclean all

# ASCII Art
header:

	@echo
	@echo "$(YELLOW)              __   _____ ____                        _           __ ";
	@echo "$(YELLOW)  ____,__  _,/ /_ |__  // __ \   ____  ____,____    (_)__  ____,/ /_";
	@echo "$(YELLOW) / ___/ / / / __ \ /_ </ / / /  / __ \/ ___/ __ \  / / _ \/ ___/ __/";
	@echo "$(YELLOW)/ /__/ /_/ / /_/ /__/ / /_/ /  / /_/ / /  / /_/ / / /  __/ /__/ /_  ";
	@echo "$(YELLOW)\___/\__,_/_.___/____/_____/  / .___/_/   \____/_/ /\___/\___/\__/  ";
	@echo "$(YELLOW)                             /_/              /___/                 ";
	@echo "$(GREY)                      by ptrapero & eldiaz-c                         ";
	@echo " $(RESET)"
	@echo

# Indica que las siguientes reglas no son archivos reales
.PHONY: all clean fclean re header

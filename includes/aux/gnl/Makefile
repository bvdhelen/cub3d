# Nombre del archivo de la biblioteca
NAME = get_next_line.a

# Compilador y banderas de compilacion
CC = cc
CFLAGS = -Wall -Werror -Wextra

# Archivos fuente y archivos objeto
SOURCES = get_next_line.c get_next_line_utils.c

BONUS_SOURCES = get_next_line_bonus.c get_next_line_utils_bonus.c

OBJECTS = $(SOURCES:.c=.o)

BONUS_OBJECTS = $(BONUS_SOURCES:.c=.o)

# Archivo de encabezado
INCLUDE = get_next_line.h

# Regla por defecto que lo compila todo
all: $(NAME)

# Regla para crear la biblioteca
$(NAME): $(OBJECTS) $(INCLUDE)
		@ar rcs $(NAME) $(OBJECTS)

# Regla para crear los archivos .o
$(OBJECTS):
		@$(CC) -c $(CFLAGS) $(SOURCES)

# Regla para crear los archivos bonus .o sin hacer relink
bonus:
		@make SOURCES="$(SOURCES) $(BONUS_SOURCES)"

# Eliminar todos los archivos .o y .a
clean:
		@rm -f $(OBJECTS)

fclean: clean
		@rm -f $(NAME)

re: fclean $(NAME)

# Indica que las siguientes reglas no son archivos reales
.PHONY: all bonus clean fclean re
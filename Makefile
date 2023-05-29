
NAME = cub3D

CC = cc
INCLUDE = -Wall -Werror -Wextra -I ./include/ -I ./minilibx-linux/
CFLAGS = -g $(INCLUDE)
MLXFLAGS = -lmlx -Ilmlx -lXext -lX11


RM = rm -rf

LIBFT = ./libft/libft.a
VECTOR = ./vector/libvector.a
PATH_SRC = ./src/
PATH_LIBFT = ./libft/
PATH_VECTOR = ./vector/
PATH_OBJS = ./objs/

SRC =   $(PATH_SRC)main.c \
        $(PATH_SRC)apply_texture.c \
        $(PATH_SRC)buttons.c \
        $(PATH_SRC)draw_base.c \
        $(PATH_SRC)get_next_line.c \
        $(PATH_SRC)get_params_respawn.c \
        $(PATH_SRC)get_texture.c \
        $(PATH_SRC)init_free.c \
        $(PATH_SRC)init_free_utils.c \
        $(PATH_SRC)make_image.c \
        $(PATH_SRC)make_rgb.c \
        $(PATH_SRC)movement.c \
        $(PATH_SRC)parse_map.c \
        $(PATH_SRC)parse_texture.c \
        $(PATH_SRC)raycast.c \
        $(PATH_SRC)read_map.c \
        $(PATH_SRC)validate.c

OBJS = $(patsubst $(PATH_SRC)%.c, $(PATH_OBJS)%.o, $(SRC))

all: $(NAME)

$(NAME): $(LIBFT) $(VECTOR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(VECTOR) -lm -o $(NAME) $(MLXFLAGS)

$(PATH_OBJS)%.o:    $(PATH_SRC)%.c
	@mkdir -p $(PATH_OBJS)
	@mkdir -p $(PATH_OBJS)libft/
	@mkdir -p $(PATH_OBJS)vector/
	@mkdir -p $(PATH_OBJS)main/
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C ./libft

$(VECTOR):
	make -C ./vector

clean:
	$(RM) ./objs
	make clean -C ./vector
	make clean -C ./libft

fclean: clean
	$(RM) $(NAME)
	make fclean -C ./libft
	make fclean -C ./vector

re: fclean all

.PHONY: all $(PATH_OBJS) clean fclean re

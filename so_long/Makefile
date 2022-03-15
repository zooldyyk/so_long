CC = cc
NAME = so_long

SRC = src/*.c
OBJ = $(src:.c=.o)


all: $(NAME)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

$(NAME):	$(OBJ)
	$(CC) -I mlx/ $(SRC) -L mlx/ -lmlx -framework OpenGL -framework Appkit -o so_long

clean:
	rm -rf src/*.o

fclean:
	rm -rf src/*.o
	rm -rf so_long

re: fclean all

.PHONY: all re clean fclean

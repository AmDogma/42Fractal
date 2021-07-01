NAME = fractol
CC = gcc

CFLAGS = -Wall -Werror -Wextra

SRCS =	main.c fractals.c hooks.c

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -fsanitize=address -lmlx -framework OpenGL -Ofast -framework AppKit

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I .

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

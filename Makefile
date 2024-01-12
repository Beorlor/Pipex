NAME = pipex

CC = gcc

CFLAGS = -Werror -Wall -Wextra -fsanitize=address

RM = rm -rf

SRCS =	src/pipex.c \
		src/utils.c \
		libft/libft.a

SRCS_BONUS =	src_bonus/pipex_bonus.c \
				src_bonus/utils_bonus.c \
				libft/libft.a \
				gnl/libgnl.a

$(NAME):
	make all -C libft
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

all: $(NAME)

fclean: clean
	$(RM) $(NAME)
	make fclean -C libft
	make fclean -C gnl

clean:
	$(RM) $(NAME)
	make clean -C libft
	make clean -C gnl

re: fclean all

bonus: clean
	make all -C libft
	make all -C gnl
	$(CC) $(CFLAGS) $(SRCS_BONUS) -o $(NAME)

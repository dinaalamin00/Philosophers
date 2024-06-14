SRC = main.c parse.c routine.c  shared.c monitor.c init_destroy.c
CC = gcc
CFLAGS = -Wall -Wextra -Werror
OBJ = ${SRC:.c=.o}
NAME = philo

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME) -lpthread

%.o: %.c
	$(CC) $(CFLAGS)  -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
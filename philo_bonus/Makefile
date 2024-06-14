SRC = main.c init.c child_process.c parse_bonus.c utils_bonus.c semaphore.c monitor_bonus.c 
CC = cc
CFLAGS = -Wall -Wextra -Werror
OBJ = ${SRC:.c=.o}
NAME = philo_bonus

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
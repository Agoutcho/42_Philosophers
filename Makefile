NAME = philo

SRCS =			main.c \

BONUS = 		main.c \

HEADER_FILES = philosopher.h

OBJS = $(SRCS:.c=.o)

BOBJS = $(BONUS:.c=.o)

DEPS = philo.d

CC = gcc
C_FLAGS = -Wall -Wextra -Werror -pthread -I.
LEAKS_FLAGS = -Wall -Wextra -Werror -fsanitize=address -g3 -pthread -I. -MD

%.o: %.c $(HEADER_FILES)
	$(CC) $(C_FLAGS) -c $< -o $@

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS) $(HEADER_FILES)
	@$(CC) $(C_FLAGS) -c $(SRCS)
	@$(CC) $(C_FLAGS) -o $(NAME) $(OBJS)

.PHONY: leaks
leaks: $(OBJS) $(HEADER_FILES)
	@$(CC) $(LEAKS_FLAGS) -c $(SRCS)
	@$(CC) $(LEAKS_FLAGS) -o $(NAME) $(OBJS)

.PHONY: bonus
bonus: $(BOBJS) $(INCL)
	rm -f $(BOBJS)
	@$(CC) $(C_FLAGS) -c $(BONUS)
	@$(CC) $(C_FLAGS) -o $(NAME) $(BOBJS)

.PHONY: clean
clean:
	rm -f $(OBJS) $(BOBJS) $(NAME)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean all

.PHONY: releaks
releaks: fclean leaks

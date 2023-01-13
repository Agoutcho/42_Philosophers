NAME = philo

SRCS =			main.c \
				parsing.c \
				post_parse.c \
				routine.c \
				utils.c \

BONUS = 		main.c \
				parsing.c \
				post_parse.c \
				routine.c \
				utils.c \

HEADER_FILES = philosopher.h

OBJS = $(SRCS:.c=.o)

BOBJS = $(BONUS:.c=.o)

DEPS = philo.d

CC = gcc
C_FLAGS = -Wall -Wextra -Werror -pthread -I.
LEAKS_FLAGS = -fsanitize=address -O1 -fno-omit-frame-pointer -fsanitize=undefined -g3

%.o: %.c $(HEADER_FILES)
	@$(CC) $(C_FLAGS) -c $< -o $@

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS) $(HEADER_FILES)
	@$(CC) $(C_FLAGS) -o $(NAME) $(OBJS)
	@printf "✅ \033[0;32mCompilation done \033[0m\n"

.PHONY: leaks
leaks: $(OBJS) $(HEADER_FILES)
	@$(CC) $(C_FLAGS) $(LEAKS_FLAGS) -c $(SRCS)
	@$(CC) $(C_FLAGS) $(LEAKS_FLAGS) -o $(NAME) $(OBJS)
	@printf "✅ \033[0;32mCompilation done \033[0m\n"

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

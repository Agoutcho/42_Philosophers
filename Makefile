NAME = philo

SRCS = 			checker.c \
				error.c \
				fill_min_max.c \
				find_position.c \
				init.c \
				key_pressing.c \
				parsing.c \
				render_map.c \
				route_checker.c \
				main.c

BONUS = 		checker_bonus.c \
				error.c \
				fill_min_max.c \
				find_position.c \
				init.c \
				key_pressing.c \
				parsing.c \
				render_map.c \
				route_checker.c \
				main.c

HEADER_FILES = philosopher.h

OBJS = $(SRCS:.c=.o)

OBJS_DEPS = $(SRCS:.c=.d)

BOBJS_DEPS = $(BONUS:.c=.d)

BOBJS = $(BONUS:.c=.o)

DEPS = philo.d

CC = gcc
C_FLAGS = -Wall -Wextra -Werror -I. -MD

%.o: %.c $(HEADER_FILES)
	$(CC) $(C_FLAGS) -c $< -o $@

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS) $(HEADER_FILES)
	@$(CC) $(C_FLAGS) -c $(SRCS)
	@$(CC) $(C_FLAGS) -o $(NAME) $(OBJS)

.PHONY: bonus
bonus: $(BOBJS) $(INCL)
	rm -f $(BOBJS)
	@$(CC) $(C_FLAGS) -c $(BONUS)
	@$(CC) $(C_FLAGS) -o $(NAME) $(BOBJS)

.PHONY: clean
clean:
	rm -f $(OBJS) $(BOBJS) $(NAME) $(OBJS_DEPS) $(BOBJS_DEPS)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean all

-include $(DEPS)

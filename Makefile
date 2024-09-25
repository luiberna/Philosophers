# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 12:32:15 by luiberna          #+#    #+#              #
#    Updated: 2024/09/24 17:38:40 by luiberna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = check.c dinner.c eating_dinner.c dinner_routine.c init.c philo.c utils.c

CC = cc

OBJS = $(SRCS:.c=.o)

CFLAGS = -g -pthread -Wall -Wextra -Werror

RM = rm -f

GREEN = \033[1;32m
YELLOW = \033[1;33m
RED = \033[1;31m
RESET = \033[0m

SANITIZE_FLAG = -fsanitize=thread

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)Compiling $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(SANITIZE_FLAG)
	@echo "$(GREEN)$(NAME) compiled successfully!$(RESET)"

valgrind:
	@echo "$(YELLOW)Compiling without sanitizer for Valgrind...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)  # No sanitizer
	@echo "$(YELLOW)Running Valgrind with Helgrind tool...$(RESET)"
	@read -p "Enter arguments ./philo: " args; \
	valgrind --tool=helgrind ./$(NAME) $$args

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@$(RM) $(OBJS)

fclean: clean
	@echo "$(RED)Cleaning executable...$(RESET)"
	@$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re valgrind

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/14 16:21:28 by carlaugu          #+#    #+#              #
#    Updated: 2025/06/11 13:21:39 by carlaugu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

# ============================================================================ #
# FILES                                                                        #
# ============================================================================ #

SRC	=$(addprefix $(SRC_DIR)/, end.c errors.c init.c main.c mini_libft.c \
mutex_utils.c mutex_utils2.c philo_utils.c)

OBJS	=$(addprefix $(BUILD_DIR)/, $(notdir $(SRC:.c=.o)))
# ============================================================================ #
# PATHS                                                                        #
# ============================================================================ #

SRC_DIR		= src/

BUILD_DIR	= .build

# ============================================================================ #
# COMPILER, FLAGS & COMMANDS                                                   #
# ============================================================================ #
CC	= cc
CFLAGS	=  -Wall -Wextra -Werror
CFLAGS	+= -fsanitize=thread -g

MAKE	= make -C

RM	= rm -rf
MKDIR	= mkdir -p

$(BUILD_DIR):
	@$(MKDIR) $(BUILD_DIR)
	@printf "$(GRN)>> Created .build/ directory for object files$(NC)\n"

# ============================================================================ #				
# RULES                                                                        #	
# ============================================================================ #

all: $(NAME)

$(NAME): $(BUILD_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) 
	@printf "$(GRN)>> Compilation completed!$(NC)\n"; \

$(BUILD_DIR)/%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	
##@ CLEAN-UP RULES
clean:	## Remove object files
	@$(RM) $(BUILD_DIR)
	@printf "$(GRN)>> Objects cleaned!$(NC)\n"; \

fclean: clean	## Remove executable files
	@$(RM) $(NAME)
	@printf "$(GRN)>> Everything cleaned!$(NC)\n\n"; \

re: fclean all	## Purge and recompile

vg:
	valgrind --tool=helgrind ./${NAME} ////////////////<args>.
	valgrind --tool=drd ./${NAME}

# ============================================================================ #
# UTILS: SHELL FORMATTING                                                      #
# ============================================================================ #

# Reset to default
NC = \033[0m

# Regular text colors
RED = \033[0;31m
GRN = \033[0;32m
YEL = \033[0;33m
BLU = \033[0;34m
MAG = \033[0;35m
CYA = \033[0;36m
WHI = \033[0;37m

# Bold text colors
RED_B = \033[1;31m
GRN_B = \033[1;32m	
YEL_B = \033[1;33m
BLU_B = \033[1;34m
MAG_B = \033[1;35m
CYA_B = \033[1;36m
WHI_B = \033[1;37m
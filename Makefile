# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zweng <zweng@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/25 17:24:40 by zweng             #+#    #+#              #
#    Updated: 2019/04/05 15:45:06 by zweng            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang

# ----- part to change -----

NAME 			= ft_ssl

HEADER_PATH 	= includes
SRC_PATH 		= srcs
LIBFT_PATH      = libft

LIB 			= libft.a

HEADER 			= ft_ssl.h
HEADERSP 		= -I$(HEADER_PATH) -I$(LIBFT_PATH)/$(HEADER_PATH)
LIBSP 			= -L$(LIBFT_PATH)
LIBS 			= -lft #-fsanitize=address

SRC_NAME		= main.c md5.c mddriver.c md5_functions.c md5_functions2.c

OBJ_PATH 		= obj
OBJ_NAME 		= $(SRC_NAME:.c=.o)
CFLAGS 			= -Wall -Wextra -Werror

# ----- part automatic -----
SRCS 			:= $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJS 			:= $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

# ----- Colors -----
BLACK			:="\033[1;30m"
RED				:="\033[1;31m"
GREEN			:="\033[1;32m"
CYAN			:="\033[1;35m"
PURPLE			:="\033[1;36m"
WHITE			:="\033[1;37m"
EOC				:="\033[0;0m"

# ----- part rules -----

all: $(NAME)

$(NAME): $(LIBFT_PATH)/$(LIB) $(OBJS)
	@$(CC) $(OBJS) $(HEADERSP) $(LIBSP) $(LIBS) -o $@
	@printf $(GREEN)"$(NAME) Finish linking\n"$(EOC)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(HEADER_PATH)/$(HEADER)| $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(HEADERSP) -o $@ -c $<
	@printf $(GREEN)"compiling %s\n"$(GREEN) $<

$(LIBFT_PATH)/$(LIB):
	@make -C $(LIBFT_PATH)/ fclean && make -C $(LIBFT_PATH)/

$(OBJ_PATH):
	@mkdir $(OBJ_PATH) 2> /dev/null

clean:
	@rm -f $(OBJS)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@printf $(GREEN)"$(NAME) clean\n"$(EOC)

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C $(LIBFT_PATH)/ fclean
	@printf $(GREEN)"$(NAME) fclean\n"$(EOC)

re: fclean all

norme:
	@norminette $(SRCS)
	@norminette $(HEADER_PATH)/*.h

.PHONY: clean fclean all re norme
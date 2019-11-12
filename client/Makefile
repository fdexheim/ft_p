# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/26 14:02:22 by fdexheim          #+#    #+#              #
#    Updated: 2019/09/25 11:23:35 by fdexheim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = client

INCLUDES_PATH = ./inc/
INCLUDE_LIBCOM_PATH = ../com/inc/

NAME_LIBCOM = libcom.a
PATH_LIBCOM = ../com/
FULL_LIBCOM_PATH = $(addprefix $(PATH_LIBCOM), $(NAME_LIBCOM))

SRC_PATH = ./src/
SRC_NAME = ft_p_client_com_utils.c ft_p_client_create_client.c \
		   ft_p_client_get_file.c \
		   ft_p_client_get_input.c ft_p_client_local_commands.c \
		   ft_p_client_ls.c \
		   ft_p_client_parsing.c ft_p_client_put_file.c main.c \
		   ft_p_client_run.c ft_p_client_simple_command.c \
		   ft_p_client_special_command.c \

OBJ_PATH = ./obj/
OBJ_NAME =	$(SRC_NAME:.c=.o)

CC = gcc
CC_FLAGS = -Wall -Werror -Wextra

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

all: libcom $(NAME)

libcom:
	@make -C $(PATH_LIBCOM)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@echo "\033[1;32;m[$@]\033[0m : " | tr -d '\n'
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	$(CC) $(CC_FLAGS) -I $(INCLUDES_PATH) -o $@ -c $<

$(NAME):	$(OBJ)
	$(CC) $(CC_FLAGS) -o $@ $(OBJ) $(FULL_LIBCOM_PATH)
	@echo "\033[1;32;m[Compilation Successful]\033[0m"
	@echo "\033[1;36;m$(NAME)\033[1;32;m ready to go !\033[0m"

clean:
	@make clean -C $(PATH_LIBCOM)
	@echo "\033[0;33;m[Clean]\033[0m              : " | tr -d '\n'
	rm -f $(OBJ)

fclean:		clean
	@make fclean -C $(PATH_LIBCOM)
	@echo "\033[0;31;m[Deleting $(NAME)]\033[0m : " | tr -d '\n'
	rm -f $(NAME)
	@rm -rf $(OBJ_PATH)

re:			fclean all

.PHONY:		all clean fclean re libcom

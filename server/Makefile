# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/26 14:02:22 by fdexheim          #+#    #+#              #
#    Updated: 2019/09/25 11:26:55 by fdexheim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = server

INCLUDES_PATH = ./inc/

NAME_COM = libcom.a
PATH_LIBCOM = ../com/
FULL_LIBCOM_PATH = $(addprefix $(PATH_LIBCOM), $(NAME_COM))

SRC_PATH = ./src/
SRC_NAME = ft_p_server_access_check.c ft_p_server_client_loop.c \
		   ft_p_server_com_utils.c \
		   ft_p_server_command_cd.c \
		   ft_p_server_command_get.c \
		   ft_p_server_command_ls.c \
		   ft_p_server_command_put.c \
		   ft_p_server_command_pwd.c ft_p_server_command_quit.c \
		   ft_p_server_create_server.c ft_p_server_err_handle.c \
		   ft_p_server_ls_checks.c ft_p_server_command_unknown.c \
		   ft_p_server_parse_commands.c ft_p_server_parsing.c \
		   ft_p_server_run.c main.c sighandle.c \

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

$(NAME): $(OBJ)
	@$(CC) $(CC_FLAGS) -o $@ $(OBJ) $(FULL_LIBCOM_PATH)
	@echo "\033[1;32;m[Compilation Successful]\033[0m"
	@echo "\033[1;36;m$(NAME)\033[1;32;m ready to go !\033[0m"

clean:
	@echo "\033[0;33;m[Clean]\033[0m              : " | tr -d '\n'
	rm -f $(OBJ)

fclean:		clean
	@echo "\033[0;31;m[Deleting $(NAME)]\033[0m : " | tr -d '\n'
	rm -f $(NAME)
	@rm -rf $(OBJ_PATH)

re:			fclean all

.PHONY:		all clean fclean re libcom

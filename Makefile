# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/05 13:37:20 by fdexheim          #+#    #+#              #
#    Updated: 2019/09/24 16:54:01 by fdexheim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_COM = libcom.a
PATH_COM = ./com/
FULL_COM_PATH = $(addprefix $(PATH_COM), $(NAME_COM))

NAME_SERVER = server
PATH_SERVER = ./server/
FULL_SERVER_PATH = $(addprefix $(PATH_SERVER), $(NAME_SERVER))

NAME_CLIENT = client
PATH_CLIENT = ./client/
FULL_CLIENT_PATH = $(addprefix $(PATH_CLIENT), $(NAME_CLIENT))

all: libcom server client 

libcom:
	@make -C $(PATH_COM)

server:
	@make -C $(PATH_SERVER)

client:
	@make -C $(PATH_CLIENT)

clean:
	@make clean -C $(PATH_COM)
	@make clean -C $(PATH_SERVER)
	@make clean -C $(PATH_CLIENT)

fclean:
	@make fclean -C $(PATH_COM)
	@make fclean -C $(PATH_SERVER)
	@make fclean -C $(PATH_CLIENT)

re:		fclean all

.PHONY: all clean fclean libcom server client re

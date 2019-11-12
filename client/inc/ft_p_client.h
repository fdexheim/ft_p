/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_client.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 09:24:37 by fdexheim          #+#    #+#             */
/*   Updated: 2019/09/25 11:25:34 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_CLIENT_H
# define FT_P_CLIENT_H

# include "../../com/inc/ft_p_com.h"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <strings.h>
# include <stdbool.h>
# include <netdb.h>
# include <netinet/in.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <sys/stat.h>
# include <sys/param.h>
# include <fcntl.h>

typedef struct			s_flags
{
	bool				d;
}						t_flags;

typedef struct			s_client_info
{
	int					client_socket;
	char				*client_home_path;
	struct protoent		*proto;
	struct sockaddr_in	sin;
	int					port;
	t_ftp_package		in;
	t_ftp_package		out;
}						t_client_info;

typedef struct			s_env
{
	t_flags				flags;
	t_client_info		cinfo;
	int					argc;
	char				**argv;
	char				*addr;
	char				*port;
}						t_env;

t_env					*g_env;

int32_t					ft_p_client_send_com(t_client_info *cinfo);
int32_t					ft_p_client_receive_com(t_client_info *cinfo);
void					ft_p_add_buffer(t_client_info *cinfo, char *message);
void					ft_p_client_remote_close_signal(t_client_info *cinfo);
void					ft_p_client_close_client(t_env *env);

void					ft_p_client_warn(t_env *env, const char *message);
void					ft_p_client_create_client(t_env *env, char *addr,
		int port);

void					ft_p_client_get_file(t_env *env, char **argv_command);

int32_t					ft_p_client_com_get_input(t_ftp_package *com);

char					**ft_p_get_command(t_env *env);

bool					ft_p_client_local_commands(t_env *env, char **argv);

void					ft_p_client_ls(t_env *env, char **argv_command);

void					ft_p_client_put_file(t_env *env, char **argv_command);

void					ft_p_client_parsing(t_env *env);

void					ft_p_client_get_hand_back(t_env *env);
void					ft_p_client_run(t_env *env);

bool					ft_p_client_special_command(t_env *envc,
		char **argv_command);

void					ft_p_client_simple_command(t_env *env);

#endif

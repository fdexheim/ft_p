/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_server.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 09:37:42 by fdexheim          #+#    #+#             */
/*   Updated: 2019/11/19 08:49:36 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_SERVER_H
# define FT_P_SERVER_H

# include "../../com/inc/ft_p_com.h"

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <strings.h>
# include <stdbool.h>
# include <netdb.h>
# include <netinet/in.h>
# include <sys/param.h>
# include <sys/socket.h>
# include <sys/stat.h>
# include <arpa/inet.h>
# include <dirent.h>
# include <signal.h>
# include <uuid/uuid.h>
# include <pwd.h>
# include <grp.h>

typedef struct			s_flags
{
	bool				d;
}						t_flags;

typedef struct			s_client_info
{
	int					client_socket;
	int					client_secondary_socket;
	struct sockaddr_in	sin;
	socklen_t			client_socket_len;
	t_ftp_package		in;
	t_ftp_package		out;
	int					cwd_level;
}						t_client_info;

typedef struct			s_server_info
{
	int					server_control_socket;
	char				*server_exec_path;
	char				*server_files_root;
	struct protoent		*proto;
	struct sockaddr_in	sin;
}						t_server_info;

typedef struct			s_env
{
	t_flags				flags;
	t_server_info		sinfo;
	int					argc;
	char				**argv;
}						t_env;

static int				g_ssock;
t_client_info			*g_cinfo;

bool					ft_p_server_access_check_dir(t_client_info *cinfo,
		char *path);
bool					ft_p_server_access_check_file(t_client_info *cinfo,
		char *path);

bool			ft_p_server_check_dir_sanity(t_env *env);
void					ft_p_server_client_loop(t_env *env,
		t_client_info *cinfo);

int32_t					ft_p_server_send_com(t_client_info *cinfo);
int32_t					ft_p_server_receive_com(t_client_info *cinfo);
void					ft_p_server_add_buffer(t_client_info *cinfo,
		char *message);
void					ft_p_server_remote_close_signal(t_client_info *cinfo);
void					ft_p_server_close_client(t_client_info *cinfo);

void					ft_p_server_command_cd(t_env *env,
		t_client_info *cinfo);
void					ft_p_server_command_get(t_env *env,
		t_client_info *cinfo);
void					ft_p_server_command_ls(t_env *env,
		t_client_info *cinfo);
void					ft_p_server_command_put(t_env *env,
		t_client_info *cinfo);
void					ft_p_server_command_pwd(t_env *env,
		t_client_info *cinfo);
void					ft_p_server_command_quit(t_env *env,
		t_client_info *cinfo);
void					ft_p_server_command_unknown(t_env *env,
		t_client_info *cinfo);

void					ft_p_server_warn(t_env *env, const char *message);
void					ft_p_server_create_server(t_env *env, int port);

int32_t					ft_p_error_handle(t_client_info *cinfo,
		int32_t err_code);

bool					check_empty_ls_case(int argc, char **argv);

void					ft_p_server_parse_commands(t_env *env,
		t_client_info *cinfo);
void					ft_p_server_parsing(t_env *env);
void					clean_exit(t_env *env);

void					ft_p_server_run(t_env *env);

void					accept_loop_signal();
void					client_loop_signal();

#endif

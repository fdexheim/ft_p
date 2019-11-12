/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_server_create_server.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 11:07:28 by fdexheim          #+#    #+#             */
/*   Updated: 2019/09/19 17:39:38 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p_server.h"

void					ft_p_server_warn(t_env *env, const char *message)
{
	if (env->flags.d == true)
	{
		ft_putstr(message);
		write(1, "\n", 1);
	}
}

static bool				ft_p_server_setup_path(t_env *env)
{
	env->sinfo.server_exec_path = NULL;
	if ((env->sinfo.server_exec_path = getcwd(env->sinfo.server_exec_path,
			MAXPATHLEN + 1)) == NULL)
	{
		ft_putstr("getcwd returned bad string\n");
	}
	env->sinfo.server_files_root = ft_strjoin(env->sinfo.server_exec_path,
			"/files");
	if (!ft_directory_exists("files") && (mkdir("files",
					S_IRUSR | S_IWUSR | S_IXUSR)) < 0)
	{
		ft_putstr("Cannot create root files directory, exitin\n");
		return (false);
	}
	if ((chdir("files")) < 0)
	{
		ft_putstr("Cannot access root files directory, exiting\n");
		return (false);
	}
	return (true);
}

static int				create_socket(t_env *env)
{
	int					on;

	env->sinfo.proto = getprotobyname("tcp");
	if (env->sinfo.proto == 0)
	{
		ft_p_server_warn(env, "[ERROR] getprotobyname() returned nullptr");
		return (-1);
	}
	env->sinfo.server_control_socket = socket(PF_INET,
			SOCK_STREAM, env->sinfo.proto->p_proto);
	if (setsockopt(env->sinfo.server_control_socket, SOL_SOCKET,
			SO_REUSEADDR, &on, sizeof(on)) < 0)
	{
		ft_putstr("[ERROR] setsockopt() error\n");
		return (-1);
	}
	g_ssock = env->sinfo.server_control_socket;
	return (env->sinfo.server_control_socket);
}

void					ft_p_server_create_server(t_env *env, int port)
{
	if (ft_p_server_setup_path(env) == false)
		return ;
	if (create_socket(env) < 0)
	{
		ft_putstr("[ERROR] socket() error");
		return ;
	}
	env->sinfo.sin.sin_family = AF_INET;
	env->sinfo.sin.sin_port = htons(port);
	env->sinfo.sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(env->sinfo.server_control_socket,
				(const struct sockaddr *)&env->sinfo.sin,
				sizeof(env->sinfo.sin)) == -1)
	{
		ft_putstr("[ERROR] bind() error\n");
		close(env->sinfo.server_control_socket);
		return ;
	}
	listen(env->sinfo.server_control_socket, 42);
	ft_p_server_run(env);
	close(env->sinfo.server_control_socket);
}

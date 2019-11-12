/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_server_run.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 13:44:48 by fdexheim          #+#    #+#             */
/*   Updated: 2019/09/19 15:04:09 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p_server.h"

static t_client_info	*setup_client_info(void)
{
	t_client_info		*ret;

	ret = malloc(sizeof(t_client_info));
	if (ret == NULL)
	{
		ft_putstr("Memory allocation error\n");
		return (NULL);
	}
	ft_p_com_clear_buffer(&ret->in);
	ft_p_com_clear_buffer(&ret->out);
	ret->in.id = 0;
	ret->out.id = 0;
	ret->out.give_hand = 1;
	ret->out.code = 1;
	ret->out.data_size = 0;
	ret->in.give_hand = 1;
	ret->in.code = 1;
	ret->in.data_size = 0;
	ret->client_socket_len = sizeof(ret->sin);
	return (ret);
}

static void				fork_client(t_env *env, t_client_info *cinfo)
{
	pid_t				pid;

	pid = fork();
	if (pid < 0)
		ft_p_server_warn(env, "[ERROR] fork() returned bad pid");
	else if (pid > 0)
	{
		close(cinfo->client_socket);
		signal(SIGCHLD, SIG_IGN);
	}
	else if (pid == 0)
	{
		close(env->sinfo.server_control_socket);
		ft_p_server_client_loop(env, cinfo);
		ft_p_server_close_client(cinfo);
	}
}

void					ft_p_server_run(t_env *env)
{
	t_client_info		*cinfo;

	while (1)
	{
		signal(SIGQUIT, accept_loop_signal);
		signal(SIGINT, accept_loop_signal);
		cinfo = setup_client_info();
		if (cinfo == NULL)
			return ;
		cinfo->client_socket = accept(env->sinfo.server_control_socket,
				(struct sockaddr*)&cinfo->sin,
				&cinfo->client_socket_len);
		if (cinfo->client_socket < 0)
		{
			ft_p_server_warn(env, "[ERROR] accept() returned bad socket");
			return ;
		}
		fork_client(env, cinfo);
	}
}

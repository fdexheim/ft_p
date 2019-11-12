/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_server_parse_commands.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 13:56:59 by fdexheim          #+#    #+#             */
/*   Updated: 2019/09/06 11:13:48 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p_server.h"

void				ft_p_server_clean_command(char *buff)
{
	size_t			i;

	i = 0;
	while (i < BUFF_SIZE)
	{
		if (buff[i] == '\n' || buff[i] == '\0')
		{
			buff[i] = '\0';
			break ;
		}
		i++;
	}
	while (i > 0 && (buff[i] == '\0' || buff[i] == ' ' || buff[i] == '\t'))
	{
		buff[i] = '\0';
		i--;
	}
}

void				command_list(t_env *env, t_client_info *cinfo,
		int command_argc, char **command_argv)
{
	(void)command_argc;
	if (!ft_strcmp(command_argv[0], "quit"))
		ft_p_server_command_quit(env, cinfo);
	else if (!ft_strcmp(command_argv[0], "ls"))
		ft_p_server_command_ls(env, cinfo);
	else if (!ft_strcmp(command_argv[0], "cd"))
		ft_p_server_command_cd(env, cinfo);
	else if (!ft_strcmp(command_argv[0], "get"))
		ft_p_server_command_get(env, cinfo);
	else if (!ft_strcmp(command_argv[0], "put"))
		ft_p_server_command_put(env, cinfo);
	else if (!ft_strcmp(command_argv[0], "pwd"))
		ft_p_server_command_pwd(env, cinfo);
	else
		ft_p_server_command_unknown(env, cinfo);
}

void				detec(t_env *env, t_client_info *cinfo, int command_argc,
		char **command_argv)
{
	if (command_argc == 0)
	{
		ft_p_server_command_unknown(env, cinfo);
		return ;
	}
	else
		command_list(env, cinfo, command_argc, command_argv);
}

void				ft_p_server_parse_commands(t_env *env, t_client_info *cinfo)
{
	char			**command_argv;
	int				command_argc;

	ft_p_server_clean_command(cinfo->in.data);
	command_argv = build_argv(cinfo->in.data);
	command_argc = ft_get_string_table_size(command_argv);
	detec(env, cinfo, command_argc, command_argv);
	ft_free_string_tab(command_argv);
}

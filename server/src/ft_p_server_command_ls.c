/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_server_command_ls.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 11:01:19 by fdexheim          #+#    #+#             */
/*   Updated: 2019/09/18 15:28:45 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p_server.h"

static void			ft_p_server_command_ls_exec(t_client_info *cinfo,
		char **argv)
{
	int				duped;
	pid_t			pid;
	int				status;

	pid = fork();
	if (pid < 0)
	{
		ft_putstr("Failed fork\n");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if ((duped = dup2(cinfo->client_socket, 1)) < 0)
			exit(0);
		execv("/bin/ls", argv);
		exit(EXIT_FAILURE);
	}
	else
	{
		wait4(pid, &status, 0, 0);
		return ;
	}
}

static bool			ft_p_server_command_ls_check_args_access(int argc,
		char **argv, t_client_info *cinfo)
{
	int				i;
	int64_t			keep;

	i = 1;
	if (argc > 1 && ft_is_flag(argv[1]))
		i = 2;
	while (i < argc)
	{
		keep = cinfo->out.err_code;
		if (ft_p_server_access_check_file(cinfo, argv[i]) == false
				&& ft_p_server_access_check_dir(cinfo, argv[i]) == false)
		{
			return (false);
		}
		else
			cinfo->out.err_code = keep;
		i++;
	}
	return (true);
}

void				ft_p_empty_ls(t_client_info *cinfo)
{
	cinfo->out.err_code = ERR_EMPTY_LS;
	ft_p_server_send_com(cinfo);
}

void				ft_p_server_command_ls(t_env *env, t_client_info *cinfo)
{
	char			**sstr;
	int				argc;

	(void)env;
	sstr = build_argv(cinfo->in.data);
	argc = ft_get_string_table_size(sstr);
	if (ft_p_server_command_ls_check_args_access(argc, sstr, cinfo) == true
			&& cinfo->out.err_code == ERR_NO_ERR)
	{
		if (check_empty_ls_case(argc, sstr) == true)
		{
			ft_p_empty_ls(cinfo);
			cinfo->out.err_code = ERR_NO_ERR;
		}
		else
		{
			ft_p_server_send_com(cinfo);
			ft_p_server_command_ls_exec(cinfo, sstr);
		}
	}
	else
	{
		ft_p_server_send_com(cinfo);
	}
	ft_free_string_tab(sstr);
}

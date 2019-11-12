/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_server_command_get.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 14:01:24 by fdexheim          #+#    #+#             */
/*   Updated: 2019/09/18 15:20:53 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p_server.h"

void			ftp_server_send_file(t_env *env, t_client_info *cinfo,
		char *path)
{
	int			fd;

	(void)env;
	if ((fd = open(path, O_RDONLY | O_NOFOLLOW)) < 0)
	{
		cinfo->out.err_code = ERR_OPEN_FILE;
		cinfo->out.code = CODE_OK;
		return ;
	}
	ft_p_com_clear_buffer(&cinfo->out);
	cinfo->out.code = CODE_TRANSFER;
	while ((cinfo->out.data_size = read(fd, cinfo->out.data, BUFF_SIZE)) > 0)
	{
		ft_p_server_send_com(cinfo);
		ft_p_com_clear_buffer(&cinfo->out);
	}
	close(fd);
	cinfo->out.code = CODE_OK;
}

void			ft_p_server_command_get(t_env *env, t_client_info *cinfo)
{
	char		**argvs;
	int			argc;

	argvs = build_argv(cinfo->in.data);
	argc = ft_get_string_table_size(argvs);
	if (argc >= 2)
	{
		ft_p_com_clear_buffer(&cinfo->out);
		if (ft_p_server_access_check_file(cinfo, argvs[1]) == true)
			ftp_server_send_file(env, cinfo, argvs[1]);
		else
		{
			if (cinfo->out.err_code == ERR_NO_ERR)
				cinfo->out.err_code = ERR_NO_SF;
			ft_free_string_tab(argvs);
			return ;
		}
	}
	else
		cinfo->out.err_code = ERR_BAD_SYNTAX;
	ft_free_string_tab(argvs);
}

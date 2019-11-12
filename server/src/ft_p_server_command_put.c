/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_server_command_put.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 14:00:54 by fdexheim          #+#    #+#             */
/*   Updated: 2019/09/19 15:36:53 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p_server.h"

static void		do_put_transfer(t_env *env, t_client_info *cinfo,
		char *filename)
{
	int			fd;

	(void)env;
	ft_p_server_send_com(cinfo);
	ft_p_server_receive_com(cinfo);
	cinfo->in.code = CODE_TRANSFER;
	fd = open(filename, O_RDWR | O_CREAT, 0644);
	if (fd < 0)
	{
		cinfo->out.code = CODE_OK;
		cinfo->out.err_code = ERR_OPEN_FILE;
		return ;
	}
	while (cinfo->in.code == CODE_TRANSFER && cinfo->in.data_size > 0)
	{
		write(fd, cinfo->in.data, cinfo->in.data_size);
		if (ft_p_server_receive_com(cinfo) < 0)
			return ;
	}
	close(fd);
}

static bool		pingpong_yesno(t_env *env, t_client_info *cinfo,
		char *message)
{
	(void)env;
	while (1)
	{
		ft_p_com_clear_buffer(&cinfo->in);
		ft_p_com_clear_buffer(&cinfo->out);
		ft_p_server_add_buffer(cinfo, message);
		if (ft_p_server_send_com(cinfo) < 0)
			return (false);
		if (ft_p_server_receive_com(cinfo) < 0
				|| cinfo->in.code == CODE_CLOSE_CONNECTION)
			return (false);
		ft_p_com_clean_command(&cinfo->in);
		if (!ft_strcmp(cinfo->in.data, "y\n") || !ft_strcmp(cinfo->in.data,
					"yes\n"))
			return (true);
		else if (!ft_strcmp(cinfo->in.data, "no\n")
				|| !ft_strcmp(cinfo->in.data, "n\n"))
			return (false);
	}
}

void			ft_p_server_put_verification_step(t_env *env,
		t_client_info *cinfo, char **argv)
{
	char		*truncated_filename;

	truncated_filename = ft_truncated_filename(argv[1]);
	cinfo->out.code = CODE_AWAIT_CONFIRMATION;
	while (cinfo->out.code == CODE_AWAIT_CONFIRMATION)
	{
		ft_p_com_clear_buffer(&cinfo->out);
		if (ft_file_exists(truncated_filename) == true)
		{
			if (pingpong_yesno(env, cinfo,
						"File exists on server, overwrite ? [y/n] ") == true)
				cinfo->out.code = CODE_TRANSFER;
			else
			{
				ft_p_server_add_buffer(cinfo, "Aborted...");
				cinfo->out.code = CODE_OK;
				ft_p_server_send_com(cinfo);
			}
		}
		else
			cinfo->out.code = CODE_TRANSFER;
	}
	if (cinfo->out.code == CODE_TRANSFER)
		do_put_transfer(env, cinfo, truncated_filename);
	cinfo->out.code = CODE_OK;
}

void			ft_p_server_command_put(t_env *env, t_client_info *cinfo)
{
	char		**argvs;

	argvs = build_argv(cinfo->in.data);
	if (argvs == NULL)
	{
		cinfo->out.err_code = ERR_SERVERSIDE_MALLOC;
		return ;
	}
	ft_p_server_put_verification_step(env, cinfo, argvs);
	ft_free_string_tab(argvs);
}

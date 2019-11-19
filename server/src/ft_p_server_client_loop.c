/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_server_client_loop.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 15:51:02 by fdexheim          #+#    #+#             */
/*   Updated: 2019/11/19 09:18:37 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p_server.h"

bool			ft_p_server_check_dir_sanity(t_env *env)
{
	if (!ft_directory_exists(env->sinfo.server_files_root))
	{
		return (false);
	}
	return (true);
}

static void		ft_p_server_give_hand_back(t_client_info *cinfo)
{
	cinfo->out.give_hand = HAND_AVIABLE;
	ft_p_server_send_com(cinfo);
}

static void		ft_p_server_check_completion(t_client_info *cinfo)
{
	if (cinfo->out.err_code != ERR_NO_ERR)
		ft_p_error_handle(cinfo, cinfo->out.err_code);
	else
		ft_p_server_add_buffer(cinfo, "[SUCCESS]\n");
}

static bool		ft_p_server_exchange(t_env *env, t_client_info *cinfo)
{
	ft_p_com_reset_package(&cinfo->out);
	ft_p_com_reset_package(&cinfo->in);
	if (ft_p_server_receive_com(cinfo) < 0)
		return (false);
	cinfo->out.give_hand = HAND_WAIT;
	if (ft_p_server_check_dir_sanity(env) == true)
		ft_p_server_parse_commands(env, cinfo);
	else
	{
		cinfo->out.code = CODE_CLOSE_CONNECTION;
		cinfo->out.err_code = ERR_MAINDIR_TAMPER;
	}
	ft_p_server_check_completion(cinfo);
	ft_p_server_give_hand_back(cinfo);
	if (cinfo->out.code == CODE_CLOSE_CONNECTION)
		return (false);
	return (true);
}

void			ft_p_server_client_loop(t_env *env,
		t_client_info *cinfo)
{
	ft_putstr("Client connected\n");
	g_cinfo = cinfo;
	signal(SIGQUIT, client_loop_signal);
	signal(SIGINT, client_loop_signal);
	while (1)
	{
		if (ft_p_server_exchange(env, cinfo) == false)
			break;
	}
}

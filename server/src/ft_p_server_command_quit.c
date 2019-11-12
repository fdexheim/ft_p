/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_server_command_quit.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 14:24:57 by fdexheim          #+#    #+#             */
/*   Updated: 2019/08/16 14:34:34 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p_server.h"

void			ft_p_server_command_quit(t_env *env, t_client_info *cinfo)
{
	(void)env;
	ft_p_com_clear_buffer(&cinfo->out);
	cinfo->out.code = CODE_CLOSE_CONNECTION;
	cinfo->out.err_code = ERR_NO_ERR;
	ft_p_server_send_com(cinfo);
}

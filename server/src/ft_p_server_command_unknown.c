/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_server_command_unknown.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 14:29:14 by fdexheim          #+#    #+#             */
/*   Updated: 2019/09/18 15:31:24 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p_server.h"

void				ft_p_server_command_unknown(t_env *env,
		t_client_info *cinfo)
{
	(void)env;
	cinfo->out.err_code = ERR_UNKNOWN_COMMAND;
}

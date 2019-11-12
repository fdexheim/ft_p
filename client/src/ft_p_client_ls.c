/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_client_ls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 14:45:52 by fdexheim          #+#    #+#             */
/*   Updated: 2019/09/18 15:10:20 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p_client.h"

static void		get_ls_result(t_env *env)
{
	int			i;
	char		bufferino[BUFF_SIZE];

	while ((i = read(env->cinfo.client_socket, bufferino,
					BUFF_SIZE)) == BUFF_SIZE)
	{
		write(1, &bufferino, BUFF_SIZE);
	}
	if (i > 0)
	{
		write(1, &bufferino, i);
	}
}

void			ft_p_client_ls(t_env *env, char **argv_command)
{
	(void)argv_command;
	ft_p_client_send_com(&env->cinfo);
	ft_p_client_receive_com(&env->cinfo);
	if (env->cinfo.in.err_code == ERR_NO_ERR)
	{
		get_ls_result(env);
	}
	else if (env->cinfo.in.err_code == ERR_EMPTY_LS)
	{
		env->cinfo.in.err_code = ERR_NO_ERR;
		return ;
	}
}

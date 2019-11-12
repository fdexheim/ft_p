/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_client_simple_command.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 10:38:10 by fdexheim          #+#    #+#             */
/*   Updated: 2019/09/06 10:49:30 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p_client.h"

void					ft_p_client_simple_command(t_env *env)
{
	int					ret;

	ret = ft_p_client_send_com(&env->cinfo);
	env->cinfo.in.give_hand = HAND_WAIT;
	if (ret == 0)
	{
		env->cinfo.in.give_hand = HAND_AVIABLE;
		env->cinfo.in.err_code = ERR_WRITE_FAIL;
	}
}

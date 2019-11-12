/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_client_special_command.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 10:41:08 by fdexheim          #+#    #+#             */
/*   Updated: 2019/09/18 15:13:26 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p_client.h"

bool				ft_p_client_special_command(t_env *env, char **argv_command)
{
	bool			ret;

	ret = false;
	if (!ft_strcmp(argv_command[0], "get"))
	{
		ft_p_client_get_file(env, argv_command);
		ret = true;
	}
	else if (!ft_strcmp(argv_command[0], "put"))
	{
		ft_p_client_put_file(env, argv_command);
		ret = true;
	}
	else if (!ft_strcmp(argv_command[0], "ls"))
	{
		ft_p_client_ls(env, argv_command);
		ret = true;
	}
	return (ret);
}

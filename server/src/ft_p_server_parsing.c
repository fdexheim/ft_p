/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_server_parsing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 10:14:09 by fdexheim          #+#    #+#             */
/*   Updated: 2019/09/19 11:36:27 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p_server.h"

static void			proces_arg_flags(const char *arg, t_env *env)
{
	size_t		j;

	j = 1;
	if (ft_strlen(arg) <= 1)
		return ;
	while (j < ft_strlen(arg))
	{
		env->flags.d = arg[j] == 'd' ? true : env->flags.d;
		j++;
	}
}

void				ft_p_server_parsing(t_env *env)
{
	int				i;

	i = 1;
	if (ft_is_flag(env->argv[1]) == true)
	{
		i = 2;
		proces_arg_flags(env->argv[1], env);
		if (env->argc < 3)
		{
			ft_putstr("Missing [port] argument\n");
			return ;
		}
	}
	ft_p_server_create_server(env, ft_atoi(env->argv[i]));
}

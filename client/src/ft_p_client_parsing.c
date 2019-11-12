/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_client_parsing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 10:16:29 by fdexheim          #+#    #+#             */
/*   Updated: 2019/09/19 13:50:30 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p_client.h"

static void			process_arg_flags(const char *arg, t_env *env)
{
	size_t		j;

	j = 1;
	if (strlen(arg) <= 1)
		return ;
	while (j < strlen(arg))
	{
		env->flags.d = arg[j] == 'd' ? true : env->flags.d;
		j++;
	}
}

void				ft_p_client_parsing(t_env *env)
{
	int				i;

	i = 1;
	if (ft_is_flag(env->argv[1]))
	{
		i = 2;
		if (env->argc < 4)
		{
			ft_putstr("[ERROR] Missing arguments\n");
			ft_putstr(env->argv[0]);
			ft_putstr(" -[flags] [server ip] [port]\n");
			return ;
		}
		process_arg_flags(env->argv[1], env);
	}
	if (i + 2 < env->argc)
	{
		ft_putstr("[ERROR] Missing arguments\n");
		ft_putstr(env->argv[0]);
		ft_putstr(" -[flags] [server ip] [port]\n");
		return ;
	}
	ft_p_client_create_client(env, env->argv[i],
					ft_atoi(env->argv[i + 1]));
}

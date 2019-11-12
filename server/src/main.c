/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 09:41:52 by fdexheim          #+#    #+#             */
/*   Updated: 2019/09/19 11:21:24 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p_server.h"

void			clean_exit(t_env *env)
{
	ft_p_server_warn(env, "[WARNING] Exiting");
	free(env);
	exit(2);
}

static void		setup_env(t_env *env, int argc, char **argv)
{
	char		*tmp;
	uint32_t	i;

	tmp = (char *)env;
	i = 0;
	while (i < sizeof(t_env))
	{
		*tmp = 0;
		tmp++;
		i++;
	}
	env->argc = argc;
	env->argv = argv;
}

static void		help(const char *arg)
{
	ft_putstr(arg);
	ft_putstr("-[flag] [port]\n");
}

int				main(int argc, char **argv)
{
	t_env		env;

	if (argc == 1 || (argc == 2 && !ft_strcmp("-help", argv[1])))
	{
		help(argv[0]);
		return (-1);
	}
	setup_env(&env, argc, argv);
	ft_p_server_parsing(&env);
	return (0);
}

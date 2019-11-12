/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 09:23:11 by fdexheim          #+#    #+#             */
/*   Updated: 2019/09/19 13:18:33 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p_client.h"

static void		close_env(t_env *env)
{
	if (env->cinfo.client_home_path != NULL)
	{
		free(env->cinfo.client_home_path);
		env->cinfo.client_home_path = NULL;
	}
	free(env);
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
	env->cinfo.client_socket = 0;
	env->cinfo.client_home_path = NULL;
}

static void		help(const char *s)
{
	ft_putstr(s);
	ft_putstr(" -[flags] [server ip] [port]\n");
	ft_putstr("-d : debug mod - lists most of the warnings\n");
}

int				main(int argc, char **argv)
{
	t_env		*env;

	if (argc < 3 || (argc < 4 && ft_is_flag(argv[1])))
	{
		help(argv[0]);
		return (0);
	}
	if ((env = malloc(sizeof(t_env))) == NULL)
	{
		ft_putstr("Bad memory allocation\n");
		exit(EXIT_FAILURE);
	}
	setup_env(env, argc, argv);
	ft_p_client_parsing(env);
	close_env(env);
	return (0);
}

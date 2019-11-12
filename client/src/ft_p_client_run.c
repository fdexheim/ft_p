/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_client_run.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 10:38:06 by fdexheim          #+#    #+#             */
/*   Updated: 2019/09/19 15:24:57 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p_client.h"

void				ft_p_client_get_hand_back(t_env *env)
{
	int32_t			i;

	while (env->cinfo.in.give_hand == HAND_WAIT)
	{
		i = ft_p_client_receive_com(&env->cinfo);
		ft_p_com_display_message(&env->cinfo.in);
		ft_p_com_clear_buffer(&env->cinfo.in);
		if (i < 0)
		{
			env->cinfo.in.give_hand = HAND_AVIABLE;
		}
	}
	ft_p_com_display_message(&env->cinfo.in);
	ft_p_com_clear_buffer(&env->cinfo.in);
}

static void			ft_p_client_prompt(t_env *env)
{
	ft_putstr("-------------------------\n");
	if (env->cinfo.in.err_code > 0 || env->cinfo.out.err_code > 0)
		ft_putstr("< x.x > ");
	else
		ft_putstr("< OwO > ");
}

static void			ft_p_client_exchange(t_env *env,
		char **argv_command)
{
	bool			local_command;

	if (env->cinfo.out.data_size <= 0)
	{
		ft_putstr("bad size of command, retreat !\n");
		return ;
	}
	local_command = ft_p_client_local_commands(env, argv_command);
	if (local_command == false)
	{
		env->cinfo.in.give_hand = HAND_WAIT;
		if (ft_p_client_special_command(env, argv_command) == false)
			ft_p_client_simple_command(env);
		ft_p_client_get_hand_back(env);
	}
}

void				client_loop_signal(int sig)
{
	if (sig == SIGINT)
		ft_putstr("Caught an interrupt signal\n");
	else if (sig == SIGQUIT)
		ft_putstr("Caught a quit signal\n");
	else
		ft_putstr("Caught a signal\n");
	ft_p_client_remote_close_signal(&g_env->cinfo);
	ft_p_client_close_client(g_env);
	exit(EXIT_SUCCESS);
}

void				ft_p_client_run(t_env *env)
{
	char			**argv_command;

	env->cinfo.out.id = 0;
	g_env = env;
	signal(SIGINT, client_loop_signal);
	signal(SIGQUIT, client_loop_signal);
	while (1)
	{
		ft_p_client_prompt(env);
		ft_p_com_reset_package(&env->cinfo.out);
		ft_p_com_reset_package(&env->cinfo.in);
		argv_command = ft_p_get_command(env);
		if (env->cinfo.out.err_code == ERR_NO_ERR && argv_command != NULL
				&& argv_command[0] != NULL)
		{
			ft_p_client_exchange(env, argv_command);
		}
		if (argv_command != NULL)
		{
			ft_free_string_tab(argv_command);
			argv_command = NULL;
		}
		if (env->cinfo.in.code == CODE_CLOSE_CONNECTION)
			break ;
	}
}

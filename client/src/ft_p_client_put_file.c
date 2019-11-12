/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_client_put_file.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 16:32:30 by fdexheim          #+#    #+#             */
/*   Updated: 2019/09/18 15:11:02 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p_client.h"

static void		ft_p_do_put_transfer(t_env *env, char *path)
{
	int			fd;

	fd = open(path, O_RDONLY | O_CREAT, 0644);
	env->cinfo.out.code = CODE_TRANSFER;
	if (fd < 0)
	{
		ft_putstr("Failed to open local file");
		env->cinfo.out.code = CODE_OK;
		return ;
	}
	while ((env->cinfo.out.data_size = read(fd,
					&env->cinfo.out.data, BUFF_SIZE)) > 0)
	{
		if (ft_p_client_send_com(&env->cinfo) < 0)
		{
			ft_putstr("Lost connection during transfer\n");
			return ;
		}
	}
	env->cinfo.out.code = CODE_OK;
	ft_p_client_send_com(&env->cinfo);
	close(fd);
}

static void		ft_p_client_server_verification_step(t_env *env,
		char **argv_command)
{
	env->cinfo.in.code = CODE_AWAIT_CONFIRMATION;
	while (env->cinfo.in.code == CODE_AWAIT_CONFIRMATION
			&& env->cinfo.in.err_code == ERR_NO_ERR)
	{
		ft_p_client_send_com(&env->cinfo);
		ft_p_client_receive_com(&env->cinfo);
		if (env->cinfo.in.code == CODE_AWAIT_CONFIRMATION)
		{
			ft_p_com_display_message(&env->cinfo.in);
			ft_p_com_clear_buffer(&env->cinfo.out);
			ft_p_client_com_get_input(&env->cinfo.out);
		}
	}
	if (env->cinfo.in.code == CODE_TRANSFER)
		ft_p_do_put_transfer(env, argv_command[1]);
}

void			ft_p_client_put_file(t_env *env, char **argv_command)
{
	if (argv_command[1] == NULL)
	{
		ft_putstr("Syntax error : Missing file in put command\n");
		env->cinfo.in.give_hand = HAND_AVIABLE;
		return ;
	}
	if (ft_file_exists(argv_command[1]) == false)
	{
		ft_putstr("Specified file does not exist localy\n");
		env->cinfo.in.give_hand = HAND_AVIABLE;
		return ;
	}
	else
		ft_p_client_server_verification_step(env, argv_command);
}

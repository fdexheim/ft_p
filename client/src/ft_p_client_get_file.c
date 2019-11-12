/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_client_get_file.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 16:25:32 by fdexheim          #+#    #+#             */
/*   Updated: 2019/09/18 15:07:15 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p_client.h"

static bool			file_is_writable(t_env *env, char *access)
{
	int				fd;
	int				wr_ret;
	char			*truncat;

	(void)env;
	truncat = ft_truncated_filename(access);
	fd = open(truncat, O_WRONLY | O_CREAT, 0644);
	if ((wr_ret = (write(fd, "", 0))) < 0)
	{
		printf("wr_ret = %d\n", wr_ret);
		close(fd);
		return (false);
	}
	close(fd);
	return (true);
}

static void			do_transfer(t_env *env, char *path)
{
	int				fd;

	fd = open(path, O_WRONLY | O_CREAT);
	if (fd < 0)
	{
		env->cinfo.in.err_code = ERR_OPEN_FILE;
		return ;
	}
	while (env->cinfo.in.code == CODE_TRANSFER)
	{
		if (env->cinfo.in.data_size > 0)
		{
			if (write(fd, &env->cinfo.in.data, env->cinfo.in.data_size) < 0)
				env->cinfo.out.err_code = ERR_LOCAL_WRITE_FAIL;
		}
		if (ft_p_client_receive_com(&env->cinfo) < 0)
		{
			close(fd);
			return ;
		}
	}
	close(fd);
}

static void			ft_p_client_get_file_check_serv(t_env *env,
		char **argv_command)
{
	env->cinfo.in.code = CODE_AWAIT_CONFIRMATION;
	env->cinfo.out.code = CODE_OK;
	ft_p_client_send_com(&env->cinfo);
	ft_p_client_receive_com(&env->cinfo);
	while (env->cinfo.in.code == CODE_AWAIT_CONFIRMATION)
	{
		if (env->cinfo.in.err_code != ERR_NO_ERR)
			return ;
		if (env->cinfo.in.code == CODE_AWAIT_CONFIRMATION)
		{
			ft_p_com_display_message(&env->cinfo.in);
			ft_p_client_com_get_input(&env->cinfo.out);
			if (env->cinfo.out.err_code != ERR_NO_ERR)
				return ;
			ft_p_client_send_com(&env->cinfo);
			ft_p_client_receive_com(&env->cinfo);
		}
	}
	if (env->cinfo.in.code == CODE_TRANSFER
			&& env->cinfo.in.err_code == ERR_NO_ERR)
		do_transfer(env, ft_truncated_filename(argv_command[1]));
}

bool				local_get_confirmation(char **argv_command)
{
	char			*filename;
	bool			valid;

	filename = ft_truncated_filename(argv_command[1]);
	valid = true;
	if (ft_file_exists(filename))
	{
		valid = yes_no_confirm(
				"A local file with the same name exists. Overwrite [y/n] ? ");
	}
	else if (ft_directory_exists(filename))
	{
		ft_putstr("A directory with the specified name exists");
		valid = false;
	}
	return (valid);
}

void				ft_p_client_get_file(t_env *env, char **argv_command)
{
	if (argv_command[1] == NULL)
	{
		ft_putstr("Syntax error : Expecting file name after get command\n");
		env->cinfo.in.give_hand = HAND_AVIABLE;
		return ;
	}
	if (local_get_confirmation(argv_command) == true)
	{
		if (file_is_writable(env, argv_command[1]) == true)
			ft_p_client_get_file_check_serv(env, argv_command);
		else
		{
			ft_putstr("Specified file does not have write rights\n");
			env->cinfo.in.give_hand = HAND_AVIABLE;
		}
	}
	else
		env->cinfo.in.give_hand = HAND_AVIABLE;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_client_get_input.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 10:20:16 by fdexheim          #+#    #+#             */
/*   Updated: 2019/11/14 10:46:33 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p_client.h"

static void			ft_p_client_add_input(t_ftp_package *com, char *input)
{
	int				len;
	int				i;

	i = 0;
	len = ft_strlen(input);
	if (len >= BUFF_SIZE - 1)
	{
		input[BUFF_SIZE - 1] = '\0';
		len = BUFF_SIZE - 1;
	}
	com->data_size = len;
	com->data[len] = '\0';
	while (i < len)
	{
		com->data[i] = input[i];
		i++;
	}
}

int32_t				ft_p_client_com_get_input(t_ftp_package *com)
{
	char			*got;

	ft_p_com_clear_buffer(com);
	got = ft_get_full_input();
	if (got == NULL)
	{
		ft_putstr("[input error]\n");
		return (-1);
	}
	ft_p_client_add_input(com, got);
	free(got);
	return (1);
}

static void			ft_p_clean_command(char *buff)
{
	int				i;

	i = 0;
	while (i < BUFF_SIZE)
	{
		if (buff[i] == '\n' || buff[i] == '\0')
		{
			buff[i] = '\0';
			break ;
		}
		i++;
	}
	while (i > 0 && (buff[i] == '\0' || buff[i] == ' ' || buff[i] == '\t'))
	{
		buff[i] = '\0';
		i--;
	}
}

char				**ft_p_get_command(t_env *env)
{
	char			**argv_command;

	argv_command = NULL;
	ft_p_client_com_get_input(&env->cinfo.out);
	ft_p_clean_command(env->cinfo.out.data);
	if (env->cinfo.out.err_code != ERR_NO_ERR)
	{
		return (NULL);
	}
	argv_command = build_argv(env->cinfo.out.data);
	return (argv_command);
}

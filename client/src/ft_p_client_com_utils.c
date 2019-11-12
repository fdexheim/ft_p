/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_client_com_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 11:25:06 by fdexheim          #+#    #+#             */
/*   Updated: 2019/09/25 15:40:07 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p_client.h"

int32_t					ft_p_client_receive_com(t_client_info *cinfo)
{
	ssize_t				read_ret;

	ft_p_com_clear_buffer(&cinfo->in);
	read_ret = ft_p_com_read_fd(&cinfo->in, cinfo->client_socket);
	if (read_ret <= 0)
	{
		ft_putstr("Connection lost with server\n");
		ft_p_client_close_client(g_env);
	}
	if (read_ret != COM_SIZE)
	{
		ft_putstr("[WARNING] size reveived does not match\n");
	}
	return (read_ret);
}

int32_t					ft_p_client_send_com(t_client_info *cinfo)
{
	ssize_t				send_ret;

	send_ret = ft_p_com_write_fd(&cinfo->out, cinfo->client_socket);
	if (send_ret < 0)
	{
		ft_putstr("[ERROR] - Connection lost with server\n");
		ft_p_client_close_client(g_env);
	}
	if (send_ret != COM_SIZE)
	{
		ft_putstr("[WARNING] size sent does not match\n");
	}
	ft_p_com_clear_buffer(&cinfo->out);
	cinfo->out.id++;
	return (send_ret);
}

void					ft_p_add_buffer(t_client_info *cinfo,
		char *message)
{
	int					i;

	i = 0;
	while (message[i] != '\0')
	{
		if (cinfo->out.data_size >= BUFF_SIZE - 1)
			break ;
		cinfo->out.data[cinfo->out.data_size] = message[i];
		cinfo->out.data_size++;
		i++;
	}
	cinfo->out.data[cinfo->out.data_size] = '\0';
}

void					ft_p_client_remote_close_signal(t_client_info *cinfo)
{
	cinfo->out.code = CODE_CLOSE_CONNECTION;
	ft_p_client_send_com(cinfo);
}

void					ft_p_client_close_client(t_env *env)
{
	ft_putstr("Disconnecting...\n");
	close(env->cinfo.client_socket);
	free(env);
	exit(EXIT_SUCCESS);
}

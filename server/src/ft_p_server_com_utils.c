/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_server_com_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 13:49:52 by fdexheim          #+#    #+#             */
/*   Updated: 2019/09/25 15:39:07 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p_server.h"

int32_t					ft_p_server_receive_com(t_client_info *cinfo)
{
	ssize_t				read_ret;

	ft_p_com_clear_buffer(&cinfo->in);
	read_ret = ft_p_com_read_fd(&cinfo->in, cinfo->client_socket);
	if (read_ret < 0)
	{
		cinfo->in.err_code = ERR_READ_FAIL;
		return (-1);
	}
	else if (read_ret == 0)
	{
		ft_p_server_close_client(cinfo);
	}
	return (read_ret);
}

int32_t					ft_p_server_send_com(t_client_info *cinfo)
{
	ssize_t				send_ret;

	send_ret = ft_p_com_write_fd(&cinfo->out, cinfo->client_socket);
	if (send_ret < 0)
	{
		cinfo->in.err_code = ERR_WRITE_FAIL;
		return (-1);
	}
	else if (send_ret != COM_SIZE)
	{
		ft_putstr("[WARNING] size sent does not match\n");
	}
	ft_p_com_clear_buffer(&cinfo->out);
	cinfo->out.id++;
	return (send_ret);
}

void					ft_p_server_add_buffer(t_client_info *cinfo,
		char *message)
{
	while (*message != '\0')
	{
		if (cinfo->out.data_size >= BUFF_SIZE)
		{
			ft_p_server_send_com(cinfo);
		}
		cinfo->out.data[cinfo->out.data_size] = *message;
		cinfo->out.data_size++;
		message++;
	}
}

void					ft_p_server_remote_close_signal(t_client_info *cinfo)
{
	cinfo->out.code = CODE_CLOSE_CONNECTION;
	ft_p_server_send_com(cinfo);
}

void					ft_p_server_close_client(t_client_info *cinfo)
{
	ft_putstr("Client disconnected\n");
	close(cinfo->client_socket);
	free(cinfo);
	exit(EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_com_read_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 13:14:40 by fdexheim          #+#    #+#             */
/*   Updated: 2019/09/25 15:38:27 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p_com.h"

ssize_t			ft_p_com_read_fd(t_ftp_package *com, int fd)
{
	ssize_t		rd_ret;
	ssize_t		rd_add;

	rd_ret = 0;
	while (rd_ret < COM_SIZE)
	{
		rd_add = read(fd, com + rd_ret, COM_SIZE - rd_ret);
		rd_ret += rd_add;
		if (rd_add < 0)
			return (rd_add);
		else if (rd_add == 0)
			return (rd_ret);
	}
	return (rd_ret);
}

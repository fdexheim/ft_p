/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_com_write_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 13:24:42 by fdexheim          #+#    #+#             */
/*   Updated: 2019/09/12 13:26:52 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p_com.h"

ssize_t			ft_p_com_write_fd(t_ftp_package *com, int fd)
{
	ssize_t		wr_ret;

	wr_ret = write(fd, com, COM_SIZE);
	return (wr_ret);
}

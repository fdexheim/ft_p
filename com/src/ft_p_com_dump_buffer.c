/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_com_dump_buffer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 14:02:25 by fdexheim          #+#    #+#             */
/*   Updated: 2019/09/12 14:38:43 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p_com.h"

void					ft_p_com_dump_full_com(t_ftp_package *com)
{
	write(1, com, COM_SIZE);
}

void					ft_p_com_dump_buffer(t_ftp_package *com)
{
	ft_putstr("[BUFFER] : |");
	if (com->data_size > BUFF_SIZE)
	{
		write(1, &com->data, BUFF_SIZE);
	}
	else if (com->data_size > 0)
	{
		write(1, &com->data, com->data_size);
	}
	ft_putstr("| [END]\n");
}

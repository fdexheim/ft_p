/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_com_clear_buffer.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 14:01:11 by fdexheim          #+#    #+#             */
/*   Updated: 2019/08/16 12:53:32 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p_com.h"

void					ft_p_com_clear_buffer(t_ftp_package *com)
{
	int					i;

	i = 0;
	com->data_size = 0;
	while (i < BUFF_SIZE)
	{
		com->data[i] = 0;
		i++;
	}
}

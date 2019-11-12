/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_com_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 14:03:06 by fdexheim          #+#    #+#             */
/*   Updated: 2019/08/28 16:14:10 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p_com.h"

void					ft_p_com_status(t_ftp_package *com)
{
	ft_putstr("-------START--------\n");
	ft_putstr("give_hand : ");
	ft_put_size_t(com->give_hand);
	ft_putstr("\ncode      : ");
	ft_put_size_t(com->code);
	ft_putstr("\nerr_code  : ");
	ft_put_size_t(com->err_code);
	ft_putstr("\ndata_size : ");
	ft_put_size_t(com->data_size);
	ft_putstr("\nBUFFER    :\n");
	ft_p_com_dump_buffer(com);
	ft_putstr("\n--------END---------\n");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_com_display_message.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 10:42:29 by fdexheim          #+#    #+#             */
/*   Updated: 2019/08/21 10:14:26 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p_com.h"

void				ft_p_com_display_message(t_ftp_package *com)
{
	if (com->data_size > 0)
		write(1, &com->data, com->data_size);
}

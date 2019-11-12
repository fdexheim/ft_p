/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_com_debug_exchange.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 16:01:09 by fdexheim          #+#    #+#             */
/*   Updated: 2019/09/18 12:37:02 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p_com.h"
#include <stdio.h>

void				ft_p_com_debug_exchange(t_ftp_package *com,
		ssize_t rwvalue)
{
	printf("rwvalue = %ld | id = %d | give_hand = %d | code = %d"
			" | err_code = %d | data_size = %d\n",
			rwvalue, com->id, com->give_hand, com->code,
			com->err_code, com->data_size);
}

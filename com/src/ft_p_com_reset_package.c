/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_com_reset_package.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 14:04:23 by fdexheim          #+#    #+#             */
/*   Updated: 2019/08/16 09:46:24 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p_com.h"

void					ft_p_com_reset_package(t_ftp_package *package)
{
	package->give_hand = HAND_AVIABLE;
	package->code = CODE_OK;
	package->err_code = ERR_NO_ERR;
	ft_p_com_clear_buffer(package);
}

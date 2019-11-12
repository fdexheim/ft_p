/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_size_t.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 11:02:14 by fdexheim          #+#    #+#             */
/*   Updated: 2019/08/14 12:29:24 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libutils.h"

void				ft_put_size_t(const size_t src)
{
	if (src >= 10)
		ft_put_size_t(src / 10);
	ft_putchar(src % 10 + '0');
}

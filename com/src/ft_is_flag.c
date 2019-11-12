/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 12:45:16 by fdexheim          #+#    #+#             */
/*   Updated: 2019/08/16 10:31:33 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libutils.h"

bool			ft_is_flag(char *arg)
{
	if (arg[0] == '-')
		return (true);
	return (false);
}

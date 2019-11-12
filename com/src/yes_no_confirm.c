/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yes_no_confirm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 12:29:26 by fdexheim          #+#    #+#             */
/*   Updated: 2019/09/11 13:28:40 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libutils.h"

bool			yes_no_confirm(char *question)
{
	char			*smol_buffer;

	while (1)
	{
		ft_putstr(question);
		if ((smol_buffer = ft_get_full_input()) == NULL)
			return (false);
		if (!ft_strcmp(smol_buffer, "yes\n")
				|| !ft_strcmp(smol_buffer, "y\n"))
		{
			free(smol_buffer);
			return (true);
		}
		if (!ft_strcmp(smol_buffer, "no\n")
				|| !ft_strcmp(smol_buffer, "n\n"))
		{
			free(smol_buffer);
			return (false);
		}
		free(smol_buffer);
	}
	return (false);
}

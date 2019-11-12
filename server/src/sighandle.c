/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 15:45:07 by fdexheim          #+#    #+#             */
/*   Updated: 2019/09/19 17:45:32 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p_server.h"

void			accept_loop_signal(int sig)
{
	if (sig == SIGINT)
		ft_putstr("Caught an interrupt signal (accept loop)\n");
	else if (sig == SIGQUIT)
		ft_putstr("Caught a quit signal (accept loop)\n");
	else
		ft_putstr("Caught an unspecified signal (accept loop)\n");
	close(g_ssock);
	exit(EXIT_SUCCESS);
}

void			client_loop_signal(int sig)
{
	if (sig == SIGINT)
		ft_putstr("Caught an interrupt signal (client loop)\n");
	else if (sig == SIGQUIT)
		ft_putstr("Caught a quit signal (client loop)\n");
	else
		ft_putstr("Caught an unspecified signal (client loop)\n");
	ft_p_server_remote_close_signal(g_cinfo);
	ft_p_server_close_client(g_cinfo);
}

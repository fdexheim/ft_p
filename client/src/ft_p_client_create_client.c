/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_client_create_client.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 10:08:08 by fdexheim          #+#    #+#             */
/*   Updated: 2019/11/12 17:08:51 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p_client.h"

void					ft_p_client_warn(t_env *env, const char *message)
{
	if (env->flags.d == true)
		ft_putstr(message);
}

void					ft_p_close_client(t_env *env, t_client_info *cinfo)
{
	close(cinfo->client_socket);
	free(env);
	exit(EXIT_SUCCESS);
}


static void				set_addr(t_env *env, char *addr)
{
	struct hostent		*hent;
	char				**addrlist;
	in_addr_t			inaddr;

	if ((inaddr = inet_addr(addr)) != INADDR_NONE)
	{
		env->cinfo.sin.sin_addr.s_addr = inaddr;
		return ;
	}
	if ((hent = gethostbyname(addr)) != NULL)
	{
		addrlist = hent->h_addr_list;
		while (addrlist != NULL)
		{
			inaddr = *((in_addr_t *)*addrlist);
			env->cinfo.sin.sin_addr.s_addr = inaddr;
			if (env->cinfo.sin.sin_addr.s_addr >= 0)
				break;
			addrlist++;
		}
	}
}

static int				create_csocket(t_env *env, char *addr, int port)
{
	int on;

	env->cinfo.client_home_path = getcwd(env->cinfo.client_home_path,
			MAXPATHLEN);
	env->cinfo.proto = getprotobyname("tcp");
	if (env->cinfo.proto == NULL)
	{
		ft_p_client_warn(env, "[ERROR] getprotobyname() returned NULLPTR");
		return (-1);
	}
	env->cinfo.client_socket = socket(PF_INET, SOCK_STREAM,
			env->cinfo.proto->p_proto);
	if (setsockopt(env->cinfo.client_socket, SOL_SOCKET,
				SO_REUSEADDR, &on, sizeof(on)) < 0)
	{
		ft_putstr("setsockopt() error\n");
		close(env->cinfo.client_socket);
		return (-1);
	}
	env->cinfo.sin.sin_family = AF_INET;
	env->cinfo.sin.sin_port = htons(port);
	set_addr(env, addr);
	return (0);
}

void					ft_p_client_create_client(t_env *env, char *addr,
		int port)
{
	ft_putstr("Setting up client...\n");
	if (create_csocket(env, addr, port) == -1)
	{
		ft_putstr("[ERROR] - Failed to setup client\n");
		return ;
	}
	ft_putstr("Connecting to server...\n");
	if (connect(env->cinfo.client_socket,
				(const struct sockaddr *)&env->cinfo.sin,
				sizeof(env->cinfo.sin)) == -1)
	{
		ft_putstr("[ERROR] cannot connect to server\n");
		close(env->cinfo.client_socket);
		return ;
	}
	ft_p_com_reset_package(&env->cinfo.in);
	ft_p_com_reset_package(&env->cinfo.out);
	ft_p_client_run(env);
	close(env->cinfo.client_socket);
	ft_putstr("Connection with server closed...\n");
}

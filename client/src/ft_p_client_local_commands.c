/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_client_local_commands.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 10:43:56 by fdexheim          #+#    #+#             */
/*   Updated: 2019/09/18 15:09:57 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p_client.h"

static void			ft_p_client_lls(char **argv)
{
	pid_t			pid;
	int				status;

	argv[0][0] = ' ';
	pid = fork();
	if (pid < 0)
	{
		ft_putstr("Fork failed\n");
		return ;
	}
	else if (pid == 0)
	{
		execv("/bin/ls", argv);
		exit(EXIT_FAILURE);
	}
	else
	{
		wait4(pid, &status, 0, 0);
		return ;
	}
}

static void			ft_p_client_lpwd(void)
{
	char		*path;

	path = NULL;
	path = getcwd(path, MAXPATHLEN + 1);
	ft_putstr(path);
	write(1, "\n", 1);
	if (path != NULL)
		free(path);
}

static void			ft_p_client_lmkdir(char **argv)
{
	pid_t			pid;
	int				status;

	argv[0][0] = ' ';
	pid = fork();
	if (pid < 0)
	{
		ft_putstr("Fork failed - Exiting\n");
		return ;
	}
	else if (pid == 0)
	{
		execv("/bin/mkdir", argv);
		exit(EXIT_FAILURE);
	}
	else
	{
		wait4(pid, &status, 0, 0);
		return ;
	}
}

static void			ft_p_client_lcd(t_env *env, char **argv)
{
	if (argv[1] == NULL)
		chdir(env->cinfo.client_home_path);
	else
	{
		if (chdir(argv[1]) < 0)
			ft_putstr("Failed to change directory\n");
	}
}

bool				ft_p_client_local_commands(t_env *env, char **argv)
{
	bool			ret;

	ret = true;
	if (argv == NULL)
		return (false);
	if (!ft_strcmp(argv[0], "lls"))
		ft_p_client_lls(argv);
	else if (!ft_strcmp(argv[0], "lpwd"))
		ft_p_client_lpwd();
	else if (!ft_strcmp(argv[0], "lmkdir"))
		ft_p_client_lmkdir(argv);
	else if (!ft_strcmp(argv[0], "lcd"))
		ft_p_client_lcd(env, argv);
	else
		ret = false;
	return (ret);
}

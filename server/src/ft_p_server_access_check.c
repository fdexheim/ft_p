/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_server_access_check.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 13:06:05 by fdexheim          #+#    #+#             */
/*   Updated: 2019/09/19 18:30:01 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p_server.h"

static int		ft_p_server_access_check(char *tmp, int level_tmp)
{
	while (*tmp != '\0')
	{
		if (!ft_strncmp(tmp, "..", 2)
				&& (*(tmp + 2) == '\0' || *(tmp + 2) == '/'))
		{
			level_tmp -= 1;
			tmp += 2;
		}
		else if (!ft_strncmp(tmp, "./", 2))
			tmp += 2;
		else
		{
			while (*tmp != '\0' && *tmp != '/')
				tmp++;
			level_tmp += 1;
		}
		if (level_tmp < 0)
			break ;
		while (*tmp == '/' && *tmp != '\0')
			tmp++;
	}
	return (level_tmp);
}

bool			ft_p_server_access_check_dir(t_client_info *cinfo, char *path)
{
	if (ft_p_server_access_check(path, cinfo->cwd_level) < 0)
	{
		cinfo->out.err_code = ERR_OUT_OF_BOUNDS;
		return (false);
	}
	if (!ft_directory_exists(path))
	{
		if (cinfo->out.err_code == ERR_NO_ERR)
			cinfo->out.err_code = ERR_NO_SDIR;
		return (false);
	}
	return (true);
}

static void		cleanup_path(char *path)
{
	int			len;

	len = ft_strlen(path);
	if (len == 0)
		return ;
	if (path[len - 1] == '/')
		path[len - 1] = '\0';
}

bool			ft_p_server_access_check_file(t_client_info *cinfo, char *path)
{
	cleanup_path(path);
	if (ft_p_server_access_check(path, cinfo->cwd_level) < 0)
	{
		cinfo->out.err_code = ERR_OUT_OF_BOUNDS;
		return (false);
	}
	if (!ft_file_exists(path))
	{
		if (cinfo->out.err_code == ERR_NO_ERR)
			cinfo->out.err_code = ERR_NO_SF;
		return (false);
	}
	return (true);
}

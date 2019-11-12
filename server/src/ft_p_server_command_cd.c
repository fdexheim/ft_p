/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_server_command_cd.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 10:50:39 by fdexheim          #+#    #+#             */
/*   Updated: 2019/09/18 15:19:24 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p_server.h"

static void		ft_p_change_directory(t_client_info *cinfo, char *path)
{
	int			ret;

	cinfo->cwd_level = ft_p_server_access_check_dir(cinfo, path);
	ret = chdir(path);
	if (ret == -1)
		ft_putstr("[ERROR] - cd command failed\n");
}

void			ft_p_server_command_cd(t_env *env, t_client_info *cinfo)
{
	size_t		argc;
	char		**sstr;

	sstr = build_argv(cinfo->in.data);
	argc = ft_get_string_table_size(sstr);
	if (argc == 1)
	{
		ft_p_change_directory(cinfo, env->sinfo.server_files_root);
	}
	else
	{
		if (ft_p_server_access_check_dir(cinfo, sstr[1]) == true)
		{
			ft_p_change_directory(cinfo, sstr[1]);
		}
	}
	ft_free_string_tab(sstr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_server_command_pwd.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 13:58:19 by fdexheim          #+#    #+#             */
/*   Updated: 2019/09/06 10:57:35 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p_server.h"

void				ft_p_server_command_pwd(t_env *env, t_client_info *cinfo)
{
	char			*buff;
	char			*truncated;

	buff = NULL;
	if ((buff = getcwd(buff, MAXPATHLEN + 1)) == NULL)
		cinfo->out.err_code = ERR_SERVERSIDE_MALLOC;
	if (!ft_strcmp(buff, env->sinfo.server_files_root))
	{
		ft_p_server_add_buffer(cinfo, "/\n");
		free(buff);
		return ;
	}
	else
	{
		truncated = buff + ft_strlen(env->sinfo.server_files_root);
		ft_p_server_add_buffer(cinfo, truncated);
		ft_p_server_add_buffer(cinfo, "\n");
		free(buff);
	}
}

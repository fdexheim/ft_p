/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_server_err_handle.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:28:45 by fdexheim          #+#    #+#             */
/*   Updated: 2019/11/19 09:25:35 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p_server.h"

static int32_t			ft_p_error_handle_extra(t_client_info *cinfo,
		int32_t err_code)
{
	if (err_code == ERR_BAD_SYNTAX)
		ft_p_server_add_buffer(cinfo,
				"Command is known but arguments are either missing or wrong\n");
	else if (err_code == ERR_WRITE_FAIL)
		ft_p_server_add_buffer(cinfo, "Socket write failed\n");
	else if (err_code == ERR_READ_FAIL)
		ft_p_server_add_buffer(cinfo, "Socket read failed\n");
	else if (err_code == ERR_DIR_EXISTS)
		ft_p_server_add_buffer(cinfo,
				"A directory with specified name already exists\n");
	else if (err_code == ERR_LOCAL_READ_FAIL)
		ft_p_server_add_buffer(cinfo, "Generic read failed\n");
	else if (err_code == ERR_LOCAL_WRITE_FAIL)
		ft_p_server_add_buffer(cinfo, "Generic write failed\n");
	else if (err_code == ERR_UNKNOWN_COMMAND)
		ft_p_server_add_buffer(cinfo, "Unknown command\n");
	else if (err_code == ERR_MAINDIR_TAMPER)
		ft_p_server_add_buffer(cinfo, "Main directory has been "
				"tampered with\n");
	else
		ft_p_server_add_buffer(cinfo, "Unknown error\n");
	return (1);
}

int32_t					ft_p_error_handle(t_client_info *cinfo,
		int32_t err_code)
{
	cinfo->out.err_code = err_code;
	ft_p_server_add_buffer(cinfo, "[FAILURE] - ");
	if (err_code == ERR_NO_SFDIR)
		ft_p_server_add_buffer(cinfo, "No such file or directory\n");
	else if (err_code == ERR_NO_SF)
		ft_p_server_add_buffer(cinfo, "File does not exists\n");
	else if (err_code == ERR_NO_SDIR)
		ft_p_server_add_buffer(cinfo, "Directory does not exist\n");
	else if (err_code == ERR_OPEN_FILE)
		ft_p_server_add_buffer(cinfo,
				"Opening of an existing file unsucessful\n");
	else if (err_code == ERR_OUT_OF_BOUNDS)
		ft_p_server_add_buffer(cinfo,
				"Attempted to access outside of dedicated area\n");
	else if (err_code == ERR_SERVERSIDE_MALLOC)
		ft_p_server_add_buffer(cinfo,
				"Server encountered an error allocating memory\n");
	else
		return (ft_p_error_handle_extra(cinfo, err_code));
	return (1);
}

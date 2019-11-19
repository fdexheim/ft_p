/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_com.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 15:26:49 by fdexheim          #+#    #+#             */
/*   Updated: 2019/11/19 09:13:44 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_COM_H
# define FT_P_COM_H

# include <stdint.h>
# include "libutils.h"

# define BUFF_SIZE 2028
# define COM_SIZE 2048
# define HEADER_OVERHEAD 20

# define HAND_WAIT 0
# define HAND_AVIABLE 1

# define CODE_TRANSFER 3
# define CODE_AWAIT_CONFIRMATION 2
# define CODE_OK 1
# define CODE_CLOSE_CONNECTION 0

# define ERR_NO_ERR 0
# define ERR_UNKNOWN_COMMAND 1
# define ERR_NO_SFDIR 2
# define ERR_NO_SF 3
# define ERR_NO_SDIR 4
# define ERR_OPEN_FILE 6
# define ERR_OUT_OF_BOUNDS 7
# define ERR_SERVERSIDE_MALLOC 8
# define ERR_BAD_SYNTAX 10
# define ERR_WRITE_FAIL 11
# define ERR_READ_FAIL 12
# define ERR_DIR_EXISTS 13
# define ERR_LOCAL_READ_FAIL 14
# define ERR_LOCAL_WRITE_FAIL 15
# define ERR_EMPTY_LS 16
# define ERR_MAINDIR_TAMPER 17

typedef struct			s_ftp_package
{
	int32_t				id;
	int32_t				give_hand;
	int32_t				code;
	int32_t				err_code;
	int32_t				data_size;
	char				data[BUFF_SIZE];
}						t_ftp_package;

void					ft_p_com_clear_buffer(t_ftp_package *com);
void					ft_p_com_debug_exchange(t_ftp_package *com,
		ssize_t rwvalue);
void					ft_p_com_display_message(t_ftp_package *com);
void					ft_p_com_dump_full_com(t_ftp_package *com);
void					ft_p_com_dump_buffer(t_ftp_package *com);
ssize_t					ft_p_com_read_fd(t_ftp_package *com, int fd);
void					ft_p_com_reset_package(t_ftp_package *com);
void					ft_p_com_status(t_ftp_package *com);
void					ft_p_com_clean_command(t_ftp_package *com);
ssize_t					ft_p_com_write_fd(t_ftp_package *com, int fd);

#endif

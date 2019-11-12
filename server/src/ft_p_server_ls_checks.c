/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_server_ls_checks.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 15:24:11 by fdexheim          #+#    #+#             */
/*   Updated: 2019/09/18 15:34:41 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p_server.h"

static bool			check_flag_a(char *arg)
{
	int				i;

	i = 1;
	while (arg[i] != '\0')
	{
		if (arg[i] == 'a')
			return (true);
		i++;
	}
	return (false);
}

static bool			check_is_directory_empty(char *path)
{
	DIR				*diredoo;
	struct dirent	*entry;

	diredoo = opendir(path);
	while ((entry = readdir(diredoo)) != NULL)
	{
		if (ft_strcmp(entry->d_name, "..") != 0
				&& ft_strcmp(entry->d_name, ".") != 0)
		{
			closedir(diredoo);
			return (false);
		}
	}
	closedir(diredoo);
	return (true);
}

static bool			only_flags_no_a(int argc, char **argv)
{
	int				i;

	i = 1;
	while (i < argc)
	{
		if (ft_is_flag(argv[i]) == false)
			return (false);
		if (ft_is_flag(argv[i]) == true
				&& check_flag_a(argv[i]) == true)
			return (false);
		i++;
	}
	return (true);
}

bool				check_empty_ls_case(int argc, char **argv)
{
	int				i;
	int				nb_empties;

	nb_empties = 0;
	if (argc == 1 || only_flags_no_a(argc, argv) == true)
		return (check_is_directory_empty("./"));
	else if (argc == 2 && ft_is_flag(argv[1]) == false)
		return (check_is_directory_empty(argv[1]));
	else if (argc > 1)
	{
		i = 1;
		while (i < argc)
		{
			if (ft_is_flag(argv[i]) == false)
				return (false);
			else if (ft_is_flag(argv[i]) == true
					&& check_flag_a(argv[i]) == true)
				return (false);
			i++;
		}
	}
	return (true);
}

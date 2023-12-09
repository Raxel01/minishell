/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:14:35 by abait-ta          #+#    #+#             */
/*   Updated: 2023/11/11 06:35:26 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/Parsing.h"

int	run_pwd(char **cmd_table)
{
	char	*working_dir;

	(void)cmd_table;
	working_dir = getcwd(NULL, PATH_MAX);
	if (!working_dir)
	{
		error_announcer(strerror(errno), 0);
		return (EXIT_FAILURE);
	}
	write(1, working_dir, ft_strlen(working_dir));
	write(1, "\n", 1);
	free(working_dir);
	return (SUCCES_PROC);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:14:35 by abait-ta          #+#    #+#             */
/*   Updated: 2023/10/24 11:43:02 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/Parsing.h"

/*USE PATH_MAX instead of 1024*/
int	run_pwd(char **cmd_table)
{
	char	*working_dir;

	(void)cmd_table;
	working_dir = getcwd(NULL, 1024);
	if (!working_dir)
	{
		write(STDERR_FILENO, "Buffer is not large Enough\n", 28);
		return (EXIT_FAILURE);
	}
	write(1, working_dir, ft_strlen(working_dir));
	write(1, "\n", 2);
	free(working_dir);
	return (SUCCES_PROC);
}

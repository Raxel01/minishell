/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_displayer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 12:57:21 by abait-ta          #+#    #+#             */
/*   Updated: 2023/10/28 21:40:34 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/Parsing.h"

int	run_env(char **cmd_tabl, t_my_env **env)
{
	t_my_env	*curs;

	if (cmd_tabl[1])
	{
		error_announcer("env:no option/argument required", 0);
		return (EXIT_FAILURE);
	}
	curs = (*env)->next;
	while (curs)
	{
		if (curs->var_content)
		{
			write(1, curs->var, ft_strlen(curs->var));
			write(1, "=", 1);
			write(1, curs->var_content, ft_strlen(curs->var_content));
			write(1, "\n", 1);
		}
		curs = curs->next;
	}
	return (SUCCES_PROC);
}

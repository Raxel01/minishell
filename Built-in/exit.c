/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:14:28 by abait-ta          #+#    #+#             */
/*   Updated: 2023/11/03 18:49:25 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/Parsing.h"

unsigned char	to_uns(unsigned char c)
{
	status_setter(c, 1);
	return (c);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	lichara;
	int	natija;

	i = 0;
	lichara = 1;
	natija = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			lichara *= -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		natija = natija * 10 + str[i] - 48;
		i++;
	}
	return (natija * lichara);
}

int	integer(char *integer)
{
	int	i;

	i = 0;
	if (integer[i] == '-' || integer[i] == '+')
		i++;
	while (integer[i])
	{
		if (integer[i] < '0' || integer[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

/*Grammer exit ![[+][-]exit[Number]]*/
// recheck status when go to school
/*DANGER ZONE USING ATOI*/
void	clean_area(t_cmd_table **head, t_my_env **env, int status)
{
	free_env(env);
	free_cmd_table(head);
	status_setter(status, 1);
	exit(status);
}

int	run_exit(t_cmd_table **head, char **cmd_table, t_my_env **env)
{
	write(1, "exit\n", 5);
	if (!cmd_table[1])
		clean_area(head, env, 0);
	if (cmd_table[1] && cmd_table[2])
	{
		error_announcer("exit: too many arguments", 0);
		free_env(env);
		free_cmd_table(head);
		return (1);
	}
	else if (cmd_table[1] && integer(cmd_table[1]))
		clean_area(head, env, \
			to_uns(ft_atoi(cmd_table[1])));
	else
	{
		write(1, cmd_table[1], ft_strlen(cmd_table[1]));
		error_announcer(": numeric argument required", 0);
		clean_area(head, env, 255);
	}
	return (1);
}

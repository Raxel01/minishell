/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_recognizer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:49:29 by abait-ta          #+#    #+#             */
/*   Updated: 2023/11/05 12:56:43 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/Parsing.h"

/*****************THERE IS ISSUE HERE IN FREING AND . .. HANDLE ERROR */
int	builtin_recognizer(t_cmd_table **head, char **cmd_table, t_my_env **env)
{
	if (cmd_table[0] && ft_strcmp(cmd_table[0], "pwd") == 0)
		return (status_setter(run_pwd(cmd_table), 1), 1);
	else if (cmd_table[0] && ft_strcmp(cmd_table[0], "echo") == 0)
		return (status_setter(run_echo(cmd_table), 1), 1);
	else if (cmd_table[0] && ft_strcmp(cmd_table[0], "cd") == 0)
		return (status_setter(run_cd(cmd_table, env), 1), 1);
	else if (cmd_table[0] && ft_strcmp(cmd_table[0], "export") == 0)
		return (status_setter(run_export(cmd_table, env), 1), 1);
	else if (cmd_table[0] && ft_strcmp(cmd_table[0], "unset") == 0)
		return (status_setter(run_unset(cmd_table, env), 1), 1);
	else if (cmd_table[0] && ft_strcmp(cmd_table[0], "env") == 0)
		return (status_setter(run_env(cmd_table, env), 1), 1);
	else if (cmd_table[0] && ft_strcmp(cmd_table[0], "exit") == 0)
		return (status_setter(run_exit(head, cmd_table, env), 1), 1);
	return (0);
}

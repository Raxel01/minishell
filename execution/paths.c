/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:20:08 by mboukaiz          #+#    #+#             */
/*   Updated: 2023/11/11 06:05:31 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/execution.h"

int	check_if_path(char	*cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (0);
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	exec_path(t_cmd_table *cmd, char **execenv, char *path, char *env_path)
{
	if (cmd->cmd_table[0] && check_if_path(cmd->cmd_table[0]))
	{
		if (execve(path, cmd->cmd_table, execenv) == -1)
		{
			perror (cmd->cmd_table[0]);
			exit(127);
		}
	}
	else
	{
		if (check_if_path(cmd->cmd_table[0]))
			path = ft_strdup(cmd->cmd_table[0]);
		else
		{
			path = ft_strjoin(env_path, "/");
			path = ft_strjoin(path, cmd->cmd_table[0]);
		}
		if (!access(path, X_OK))
			execve(path, cmd->cmd_table, execenv);
		free(path);
	}
}

void	display_error(t_cmd_table *cmd)
{
	write(STDERR_FILENO, cmd->cmd_table[0], ft_strlen(cmd->cmd_table[0]));
	write(STDERR_FILENO, ": command not found\n", 20);
}

void	find_cmd(t_my_env *env, t_cmd_table *cmd)
{
	int		i;
	char	**paths;
	char	*path;
	char	**execenv;

	i = 0;
	if (builtin_recognizer(&cmd, cmd->cmd_table, &env))
		exit (status_setter(0, 0));
	env = env->next;
	paths = dup_func(env);
	path = ft_strdup(cmd->cmd_table[0]);
	while (cmd->cmd_table[0] && paths && paths[i])
	{
		execenv = listconvertion(env);
		exec_path(cmd, execenv, path, paths[i]);
		free_execenv(execenv);
		i++;
	}
	if (cmd->cmd_table[0] && !check_if_path(cmd->cmd_table[0]))
		display_error(cmd);
	if (cmd->cmd_table[0] == NULL)
		exit (0);
	exit (127);
}

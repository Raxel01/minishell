/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 03:05:09 by mboukaiz          #+#    #+#             */
/*   Updated: 2023/11/11 06:56:16 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/execution.h"

/*mode is to see if dot ('.') have arguments*/
void	dir(char *cmd)
{
	DIR	*direct;

	if (!cmd)
		return ;
	direct = opendir(cmd);
	if (direct)
	{
		ft_putstr_fd("minishell:", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": is a directory\n", 2);
		exit(126);
	}
	free(direct);
}

void	child_exec(t_cmd_table *cmd, t_my_env *new_env, int pipe[2])
{
	if (cmd->in_fd == -1 || cmd->out_fd == -1)
		exit (1);
	signal(SIGQUIT, SIG_DFL);
	if (cmd->out_fd > 2)
		dup2(cmd->out_fd, STDOUT_FILENO);
	else if (cmd && cmd->next != NULL)
		dup2(pipe[1], STDOUT_FILENO);
	close(pipe[0]);
	close(pipe[1]);
	dir(cmd->cmd_table[0]);
	find_cmd(new_env, cmd);
}

void	p_exec(int pid, t_cmd_table *cmd, t_my_env *new_env, int pipe[2])
{
	if (pid)
	{
		close(pipe[1]);
		if (cmd->next)
		{
			if (cmd->next->in_fd > 2)
				dup2(cmd->next->in_fd, STDIN_FILENO);
			else
				dup2(pipe[0], STDIN_FILENO);
		}
		close(pipe[0]);
	}
	else
		child_exec(cmd, new_env, pipe);
}

int	my_pipes(t_cmd_table *cmd, t_my_env *new_env)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		return (perror("Pipe "), -1);
	pid = fork();
	if (pid == -1)
		return (-1);
	dup2(cmd->in_fd, STDIN_FILENO);
	p_exec(pid, cmd, new_env, pipefd);
	close(pipefd[1]);
	close(pipefd[0]);
	return (pid);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:20:08 by mboukaiz          #+#    #+#             */
/*   Updated: 2023/11/11 05:31:47 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/execution.h"

void	ft_putstr_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}

void	update_and_wait(int status, int pid)
{
	waitpid(pid, &status, 0);
	while (wait(NULL) != -1)
		;
	if (WIFEXITED(status))
		status_setter(WEXITSTATUS(status), 1);
}

void	close_all_fd(void)
{
	int			i;
	struct stat	fd_stat;

	i = 3;
	while (fstat(i, &fd_stat) == 0 || i < 256)
	{
		close(i);
		i++;
	}
}

void	first_builtin(t_cmd_table	*cmd, int *condition, t_my_env	*env)
{
	if (cmd && !cmd->next)
	{
		if (cmd->in_fd > 2)
			if (dup2(cmd->in_fd, STDIN_FILENO) == -1)
				error_announcer(strerror(errno), 0);
		if (cmd->out_fd > 2)
			if (dup2(cmd->out_fd, STDOUT_FILENO) == -1)
				error_announcer(strerror(errno), 0);
		*condition = builtin_recognizer (&cmd, cmd->cmd_table, &env);
	}
}

void	execution(t_cmd_table	*cmd, t_my_env	*env)
{
	t_execvar	elem;

	if (analyse_cmd(cmd))
		return ;
	init_vars(&elem);
	first_builtin(cmd, &elem.condition, env);
	while (cmd && elem.condition == 0)
	{
		elem.pid = my_pipes(cmd, env);
		if (elem.pid == -1)
			break ;
		cmd = cmd->next;
	}
	dup2(elem.out, STDOUT_FILENO);
	dup2(elem.in, STDIN_FILENO);
	if (elem.in > 2)
		close (elem.in);
	if (elem.out > 2)
		close (elem.out);
	elem.status = 0;
	if (elem.condition == 0)
		update_and_wait(elem.status, elem.pid);
	return (close_all_fd());
}

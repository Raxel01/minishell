/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_generator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 23:20:49 by abait-ta          #+#    #+#             */
/*   Updated: 2023/10/28 14:36:23 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Header/Parsing.h"

void	init_fd(t_in_out *fd)
{
	fd->in_fd = STDIN_FILENO;
	fd->out_fd = STDOUT_FILENO;
}

void	elem_expansion(t_here_doc **head, t_my_env **env)
{
	t_here_doc	*current;

	current = (*head);
	while (current)
	{
		if (current->type == VAR)
			current->data = replaceby_content(current->data, env);
		current = current->next;
	}
}

char	*concatenate_data(t_here_doc **head)
{
	t_here_doc	*cursur;
	char		*joiner;

	cursur = *head;
	joiner = ft_strndup(cursur->data, (int)ft_strlen(cursur->data));
	cursur = cursur->next;
	while (cursur)
	{
		joiner = ft_strjoin(joiner, cursur->data);
		cursur = cursur->next;
	}
	return (joiner);
}

int	open_fd(t_cmd *curs)
{
	int	fd;

	fd = 1;
	if (curs->file == OUTFILE)
		fd = open(curs->content, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (curs->file == APPEND)
		fd = open(curs->content, O_CREAT | O_WRONLY | O_APPEND, 0666);
	return (fd);
}

t_in_out	process_fd(t_cmd **head, t_my_env **env)
{
	t_cmd		*curs;
	t_in_out	fd;

	(void)env;
	init_fd(&fd);
	curs = (*head);
	while (curs && curs->type != PIPE)
	{
		if (curs->file == OUTFILE || curs->file == APPEND
			|| curs->file == INFILE)
		{
			if (curs->file == OUTFILE || curs->file == APPEND)
				fd.out_fd = open_fd(curs);
			else
				fd.in_fd = open(curs->content, O_RDONLY, 0666);
			if (fd.out_fd == -1 || fd.in_fd == -1)
			{
				error_announcer(strerror(errno), 0);
				break ;
			}
		}
		curs = curs->next;
	}
	return (fd);
}

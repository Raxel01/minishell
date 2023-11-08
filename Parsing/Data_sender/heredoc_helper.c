/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:03:14 by abait-ta          #+#    #+#             */
/*   Updated: 2023/11/08 17:45:34 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Header/Parsing.h"

char	*pushcontent_clean(int heredoc, char *readed_data)
{
	write(heredoc, readed_data, ft_strlen(readed_data));
	write(heredoc, "\n", 1);
	free(readed_data);
	return (NULL);
}

void	free_elem(char *eof, char *index)
{
	free(eof);
	free(index);
}

void	here_signal(int heredoc)
{
	if (heredoc == SIGINT)
	{
		status_setter(1, 1);
		if (dup2(STDERR_FILENO, 0) == -1)
			error_announcer(strerror(errno), 0);
		write(1, "\n", 1);
		close(STDIN_FILENO);
	}
}

int	manage_heredoc(t_cmd **head, t_my_env **env)
{
	t_cmd	*curs;
	int		i;

	i = 1;
	curs = (*head);
	while (curs)
	{
		if (curs->file == HEREDOC_LIM)
		{
			curs->content = here_doc_(curs->content, \
				curs->state, env, ft_itoa(i));
			if (!(ttyname(STDIN_FILENO)))
				return (1337);
			i++;
		}
		curs = curs->next;
	}
	return (1);
}

void	close_oldout(int fd)
{
	if (fd != 1)
		close(fd);
}

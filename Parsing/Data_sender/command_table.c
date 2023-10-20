/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 18:55:48 by abait-ta          #+#    #+#             */
/*   Updated: 2023/10/20 15:49:57 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Header/Parsing.h"

int	arg_count(t_cmd **head)
{
	t_cmd	*curs;
	int		args_number;

	args_number = 0;
	curs = *head;
	while (curs && curs->type != PIPE)
	{
		if (curs->category == CMD || curs->category == OPTION)
			args_number++;
		curs = curs->next;
	}
	return (args_number);
}

char	**cmd_table_remplisseur(t_cmd **head)
{
	char	**cmd_table;
	int		i;
	t_cmd	*cursur;

	i = 0;
	cmd_table = malloc(sizeof(char *) * (arg_count(head) + 1));
	if (!cmd_table)
		return (error_announcer(strerror(errno), 0), NULL);
	cursur = (*head);
	while (cursur && cursur->type != PIPE)
	{
		if (cursur->category == CMD || cursur->category == OPTION)
		{
			if (cursur->type == EXIT_STATUS)
				cmd_table[i] = ft_itoa(status_setter(255, 0));
			else
				cmd_table[i] = ft_strndup(cursur->content, \
						ft_strlen(cursur->content));
			i++;
		}
		cursur = cursur->next;
	}
	cmd_table[i] = NULL;
	return (cmd_table);
}

t_cmd_table	*build_commandtable_node(t_cmd **head)
{
	t_cmd_table	*node;
	t_in_out	fd;

	fd = process_fd(head);
	node = (t_cmd_table *)malloc(sizeof(t_cmd_table));
	if (!node)
		return (NULL);
	node->cmd_table = cmd_table_remplisseur(head);
	node->in_fd = fd.in_fd;
	node->out_fd = fd.out_fd;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	addto_listt(t_cmd_table **cmd, t_cmd_table *next_data)
{
	t_cmd_table	*cursur;

	if (!(*cmd))
		(*cmd) = next_data;
	else
	{
		cursur = *cmd;
		while (cursur->next)
			cursur = cursur->next;
		cursur->next = next_data;
		next_data->prev = cursur;
	}
}

void	cmd_table_builder(t_cmd_table **cmd_table, t_cmd **head)
{
	t_cmd	*curs;

	curs = (*head);
	while (curs)
	{
		addto_listt(cmd_table, build_commandtable_node(&curs));
		curs = head_cursur(curs);
	}
}

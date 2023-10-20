/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:39:37 by abait-ta          #+#    #+#             */
/*   Updated: 2023/10/20 16:39:39 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Header/Parsing.h"

t_cmd	*build_node(char *data, enum e_token_type intype,
		enum e_token_state in_state)
{
	t_cmd	*node;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->content = data;
	node->state = in_state;
	node->type = intype;
	node->file = NONEF;
	node->category = NONE;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	addto_list(t_cmd **cmd, t_cmd *next_data)
{
	t_cmd	*cursur;

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

t_here_doc	*creatnodes(char *content, enum e_heredoc h_type)
{
	t_here_doc	*node;

	node = malloc(sizeof(t_here_doc));
	if (!node)
		return (NULL);
	node->data = content;
	node->type = h_type;
	node->next = NULL;
	return (node);
}

void	list_builder(t_here_doc **head, t_here_doc *new_node)
{
	t_here_doc	*start;

	if (!(*head))
		(*head) = new_node;
	else
	{
		start = *head;
		while (start->next)
			start = start->next;
		start->next = new_node;
	}
}

void	free_herelist(t_here_doc **head)
{
	t_here_doc	*tmp;

	while (*head)
	{
		tmp = (*head);
		*head = (*head)->next;
		free(tmp->data);
		free(tmp);
	}
	*head = NULL;
}

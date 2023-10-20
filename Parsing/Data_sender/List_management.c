/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 19:57:08 by abait-ta          #+#    #+#             */
/*   Updated: 2023/10/20 16:36:52 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Header/Parsing.h"

void	free_cmd(t_cmd **cmd)
{
	t_cmd	*cursur;

	while (*cmd)
	{
		cursur = *cmd;
		(*cmd) = (*cmd)->next;
		free(cursur);
	}
}

/*delete '|' in this case cmd >| outf*/
void	syntax_reformer(t_cmd **cmd)
{
	t_cmd	*cursur;
	t_cmd	*tmp;

	cursur = *cmd;
	while (cursur)
	{
		if (cursur->type == OUT_REDIR && cursur->next->type == PIPE)
		{
			tmp = cursur->next;
			cursur->next->next->prev = cursur;
			cursur->next = cursur->next->next;
			free(tmp);
			cursur = (*cmd);
		}
		cursur = cursur->next;
	}
	redirect_recognizer(cmd);
	grammar_adapter(cmd);
}

/*Begin in while and make function 25*/
void	grammar_adapter(t_cmd **cmd)
{
	t_cmd	*tmp;
	t_cmd	*cursur;
	t_cmd	*garder;

	tmp = NULL;
	cursur = *cmd;
	while (cursur)
	{
		if (cursur->category == FD_FILE && cursur->next
			&& cursur->next->type == WORD)
		{
			cursur->next->prev = cursur->prev;
			cursur->prev->next = cursur->next;
			tmp = cursur;
			while (cursur->next && cursur->next->type == WORD)
				cursur = cursur->next;
			if (cursur->next)
				garder = cursur->next;
			else
				garder = NULL;
			cursur->next = tmp;
			tmp->prev = cursur;
			tmp->next = NULL;
			if (garder)
			{
				tmp->next = garder;
				garder->prev = tmp;
			}
		}
		cursur = cursur->next;
	}
}

t_cmd	*head_cursur(t_cmd *head)
{
	while (head && head->type != PIPE)
	{
		head = head->next;
	}
	if (head && head->type == PIPE)
		head = head->next;
	return (head);
}

t_cmd_table	*parsing(t_token_list **tokens)
{
	t_token_list	*cursus;
	t_cmd			*head;
	t_cmd_table		*cmd_table;

	head = NULL;
	cmd_table = NULL;
	cursus = (*tokens);
	while (cursus)
	{
		if (cursus->type != A_SPACE)
			addto_list(&head, build_node(cursus->token, cursus->type, \
					cursus->state));
		cursus = cursus->next;
	}
	syntax_reformer(&head);
	commande_recognizer(&head);
	options_recognizer(&head);
	cmd_table_builder(&cmd_table, &head);
	free_token_list(tokens);
	free_cmd(&head);
	return (cmd_table);
}

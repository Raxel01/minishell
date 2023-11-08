/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 19:57:08 by abait-ta          #+#    #+#             */
/*   Updated: 2023/11/08 17:44:46 by abait-ta         ###   ########.fr       */
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
		free(cursur->content);
		free(cursur);
	}
}

/*delete '|' in this case cmd >| outf*/
/*grammar_adapter(cmd);*/
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
			free(tmp->content);
			free(tmp);
			cursur = (*cmd);
		}
		cursur = cursur->next;
	}
	redirect_recognizer(cmd);
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

void	build_cmdlist(t_cmd **head, t_token_list **tokens)
{
	t_token_list	*cursus;

	cursus = (*tokens);
	while (cursus)
	{
		if (cursus->type != A_SPACE)
			addto_list(head, build_node(cursus->token, cursus->type, \
					cursus->state));
		cursus = cursus->next;
	}
}

t_cmd_table	*parsing(t_token_list **tokens, t_my_env **henv)
{
	t_cmd			*head;
	t_cmd_table		*cmd_table;

	head = NULL;
	cmd_table = NULL;
	build_cmdlist(&head, tokens);
	syntax_reformer(&head);
	commande_recognizer(&head);
	options_recognizer(&head);
	if (manage_heredoc(&head, henv) == 1337)
		return (NULL);
	signal(SIGINT, seg_handler_c);
	cmd_table_builder(&cmd_table, &head);
	free_token_list(tokens);
	free_cmd(&head);
	return (cmd_table);
}

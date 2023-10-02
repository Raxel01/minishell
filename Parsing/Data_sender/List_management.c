/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 19:57:08 by abait-ta          #+#    #+#             */
/*   Updated: 2023/10/02 20:08:09 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Header/Parsing.h"

t_cmd  *build_node(char *data, enum e_token_type intype, enum e_token_state in_state)
{
    t_cmd   *node;

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

void    addto_list(t_cmd **cmd, t_cmd *next_data)
{
    t_cmd *cursur;

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

void    free_cmd(t_cmd **cmd)
{
    t_cmd	*cursur;

	while (*cmd)
	{
		cursur = *cmd;
		(*cmd) = (*cmd)->next;
		free(cursur);
	}

}

t_cmd  *parsing(t_token_list **tokens)
 {
    t_token_list    *cursus;
    t_cmd           *head;

    head = NULL;
    cursus = (*tokens);
    while (cursus)
    {
        if (cursus->type != A_SPACE)
            addto_list(&head, build_node(cursus->token, cursus->type, cursus->state));
        cursus = cursus->next;
    }
    redirect_recognizer(&head);
    commande_recognizer(&head);
    options_recognizer(&head);
    return (head);
 }
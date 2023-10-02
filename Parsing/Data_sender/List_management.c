/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 19:57:08 by abait-ta          #+#    #+#             */
/*   Updated: 2023/10/01 22:26:33 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Header/Parsing.h"

t_cmd  *build_node(char *data, enum e_token_type intype, enum e_token_state in_state)
{
    t_cmd *node;

    node = (t_cmd *)malloc(sizeof(t_cmd));
    if (!node)
        return (NULL);
    node->content = data;
    node->state = in_state;
    node->type = intype;
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

t_cmd  *build_list(t_token_list **tokens)
 {
    t_token_list *cursus;
    t_cmd *head;

    head = NULL;
    cursus = (*tokens);
    while (cursus)
    {
        if (cursus->type != A_SPACE)
            addto_list(&head, build_node(cursus->token, cursus->type, cursus->state));
        cursus = cursus->next;
    }
    printcmd_list(&head);
    return (head);
 }
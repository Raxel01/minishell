/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 19:57:08 by abait-ta          #+#    #+#             */
/*   Updated: 2023/10/13 12:51:43 by abait-ta         ###   ########.fr       */
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

/*delete '|' in this case cmd >| outf*/
void    syntax_reformer(t_cmd **cmd)
{
    t_cmd   *cursur;
    t_cmd   *tmp;
    
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
/*Begin in while and make function*/
void    grammar_adapter(t_cmd ** cmd)
{
    //before changes
    t_cmd   *tmp;
    t_cmd   *cursur;
    t_cmd   *garder;
    
    tmp = NULL;
    cursur = *cmd;
    while (cursur)
    {
        if (cursur->category == FD_FILE \
            && cursur->next && cursur->next->type == WORD)
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

t_cmd   *head_cursur(t_cmd *head)
{
    while (head && head->type != PIPE)
    {
        head = head->next;
    }
    if (head && head->type == PIPE)
        head = head->next;
    return (head);
}

void    cmd_table_builder(t_cmd_table **cmd_table, t_cmd **head)
{
    t_cmd *curs;

    curs = (*head);
    while (curs)
    {
        addto_listt(cmd_table, build_commandtable_node(&curs));
        curs = head_cursur(curs);
    }
}

t_cmd_table *parsing(t_token_list **tokens)
 {
    t_token_list    *cursus;
    t_cmd           *head;
    t_cmd_table     *cmd_table;
    
    head = NULL;
    cmd_table = NULL;
    cursus = (*tokens);
    while (cursus)
    {
        if (cursus->type != A_SPACE)
            addto_list(&head, build_node(cursus->token, cursus->type, cursus->state));
        cursus = cursus->next;
    }
    syntax_reformer(&head);
    commande_recognizer(&head);
    options_recognizer(&head);
    cmd_table_builder(&cmd_table, &head);
    free_cmd(&head);
    return (cmd_table);
 }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 19:57:08 by abait-ta          #+#    #+#             */
/*   Updated: 2023/10/06 22:58:57 by abait-ta         ###   ########.fr       */
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
    t_cmd   *garder;
    
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

t_cmd  *parsing(t_token_list **tokens)
 {
    t_token_list    *cursus;
    t_cmd           *head;
    t_cmd_table     *cmd_tabl;
    
    head = NULL;
    cmd_tabl = NULL;
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
    // printf ("arg_count : %d\n", arg_count(&head));
    // printf ("inf : %d\n", infile_size(&head));
    // printf ("outf : %d\n", outfile_size(&head));
    // printf ("append : %d\n", append_size(&head));
    // printf ("heredoc : %d\n", heredoc_size(&head));
    cmd_tabl = build_commandtable_node(&head);
    int i;
    i = 0;
    while (cmd_tabl->cmd_table[i])
    {
        if (i == 0)
            printf ("cmd[%d] := %s \n", i, cmd_tabl->cmd_table[i]);
        else
            printf ("option[%d] := %s \n", i, cmd_tabl->cmd_table[i]);
    i++;
    }
    
    printf ("====================\n");
    i = 0;
    while (cmd_tabl->infile[i])
    {
        printf ("infile[%d] := %s\n", i, cmd_tabl->infile[i]);
        i++;
    }
    i = 0;
    printf ("====================\n");
    while (cmd_tabl->outfile[i])
    {
        printf ("outfile[%d] := %s\n", i, cmd_tabl->outfile[i]);
        i++;
    }
    i = 0;
    printf ("====================\n");
    while (cmd_tabl->append[i])
    {
        printf ("append[%d] := %s\n", i, cmd_tabl->append[i]);
        i++;
    }
    i = 0;
    printf ("====================\n");
    while (cmd_tabl->here_doc[i])
    {
        printf ("here_doc[%d] := %s\n", i, cmd_tabl->here_doc[i]);
        i++;
    }
    // command_table_former(&cmd_tabl, &head);
    return (head);
 }
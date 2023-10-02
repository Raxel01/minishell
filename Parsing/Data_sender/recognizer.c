/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 20:06:00 by abait-ta          #+#    #+#             */
/*   Updated: 2023/10/02 20:08:02 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Header/Parsing.h"

void    redirect_recognizer(t_cmd **cmd)
{
    t_cmd *cursur;

    cursur = *cmd;
    while(cursur)
    {
        if (redir_case(cursur->type)) 
            cursur->next->category = FD_FILE;
        if (cursur->type == OUT_REDIR)
            cursur->next->file = OUTFILE;
        else if (cursur->type == IN_REDIR)
            cursur->next->file = INFILE;
        else if (cursur->type == APPEND_SYM)
            cursur->next->file = APPEND;
        else if (cursur->type == HERE_DOC)
            cursur->next->file = HEREDOC_LIM;
        cursur = cursur->next;
    }
}

void    commande_recognizer(t_cmd **cmd)
{
    t_cmd *cursur;

    cursur = *cmd;
    while (cursur)
    {
        if (!cursur->prev && (!redir_case(cursur->type)))
                cursur->category = CMD;
        if (cursur->file == HEREDOC_LIM && cursur->next && cursur->next->type == WORD)
                cursur->next->category = CMD;
        else if (cursur->type == PIPE && (!redir_case(cursur->next->type)))
                cursur->next->category = CMD;
        cursur = cursur->next;
    }
    redir_cleaner(cmd);
}

void    options_recognizer(t_cmd **cmd)
{
    t_cmd *cursur;

    cursur = *cmd;
    while(cursur)
    {
        if (cursur->category == NONE && (cursur->type == WORD || cursur->type == EXIT_STATUS))
            cursur->category = OPTION;
        cursur = cursur->next;
    }
}

void    redir_cleaner(t_cmd** head)
{
    t_cmd   *current;
    t_cmd   * temp;
    
    current = *head;

    while (current != NULL)
    {
        if (current->type == IN_REDIR || current->type == OUT_REDIR \
            || current->type == HERE_DOC || current->type == APPEND_SYM )
        {
            if (current->prev != NULL)
                current->prev->next = current->next;
            else 
                *head = current->next;
            if (current->next != NULL)
                current->next->prev = current->prev;
            temp = current;
            current = current->next;
            free(temp);
        }
        else
            current = current->next;
    }
}

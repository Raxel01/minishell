/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 18:55:48 by abait-ta          #+#    #+#             */
/*   Updated: 2023/10/13 12:38:44 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Header/Parsing.h"

int arg_count(t_cmd **head)
{
    t_cmd *curs;
    int args_number;
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

char **cmd_table_remplisseur(t_cmd **head)
{
    char **cmd_table;
    int i;
    t_cmd *cursur;

    i = 0;
    cmd_table = malloc(sizeof(char *)* (arg_count (head) + 1));
    cursur = (*head);
    while (cursur && cursur->type != PIPE)
    {
        if (cursur->category == CMD || cursur->category == OPTION)
        {
            cmd_table[i] = cursur->content;
            i++;
        }
        cursur = cursur->next;
    }
    cmd_table[i] = NULL;
    return (cmd_table);
}

int outfile_getter(t_cmd **head)
{
    t_cmd   *curs;
    int     out_fd;

    out_fd = OUT_DEF;
    curs = (*head);
    while (curs && curs->type != PIPE)
    {
        if (curs->file == OUTFILE || curs->file == APPEND)
        {
            if (curs->file == OUTFILE)
                out_fd = open(curs->content, O_CREAT | O_WRONLY | O_TRUNC, 0666);
            else
                out_fd = open (curs->content, O_CREAT | O_WRONLY | O_APPEND, 0666);
            if (out_fd == -1)
            {
                error_announcer("FILE : Error when opening file\n", 0);
                break;
            }       
        }
        curs = curs->next;
    }
    return (out_fd);
}

int infile_getter(t_cmd **head)
{
    t_cmd   *curs;
    int     in_fd;

    in_fd = IN_DEF;
    curs = (*head);
    while (curs && curs->type != PIPE)
    {
        if (curs->file == INFILE)
        {
            in_fd = open (curs->content, O_RDONLY);
            if (in_fd == -1)
            {
                error_announcer("FILE : Error when opening file\n", 0);
                break;
            }       
        }
        curs = curs->next;
    }
    return (in_fd);
}

t_cmd_table *build_commandtable_node(t_cmd **head)
{
    t_cmd_table *node;

    node = (t_cmd_table *)malloc(sizeof(t_cmd_table));
    if (!node)
        return (NULL);
    node->cmd_table =  cmd_table_remplisseur(head);
    node->in_fd = infile_getter(head);
    node->out_fd = outfile_getter(head);
    node->next = NULL;
    node->prev = NULL;
    return(node);
}

void    addto_listt(t_cmd_table **cmd, t_cmd_table *next_data)
{
    t_cmd_table *cursur;

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

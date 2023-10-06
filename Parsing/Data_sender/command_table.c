/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 18:55:48 by abait-ta          #+#    #+#             */
/*   Updated: 2023/10/06 22:09:10 by abait-ta         ###   ########.fr       */
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

int infile_size(t_cmd **head)
{
    t_cmd *curs;
    int infiles;

    infiles = 0;
    curs = *head;
    while (curs && curs->type != PIPE)
    {
        if (curs->file == INFILE)
            infiles++;
        curs = curs->next;
    }
    return (infiles);
}

int outfile_size(t_cmd **head)
{
    t_cmd *curs;
    int outfil;

    outfil = 0;
    curs = *head;
    while (curs && curs->type != PIPE)
    {
        if (curs->file == OUTFILE)
            outfil++;
        curs = curs->next;
    }
    return (outfil);
}

int append_size(t_cmd **head)
{
    t_cmd *curs;
    int append;

    append = 0;
    curs = *head;
    while (curs && curs->type != PIPE)
    {
        if (curs->file == APPEND)
            append++;
        curs = curs->next;
    }
    return (append);
}

int heredoc_size(t_cmd **head)
{
    t_cmd *curs;
    int herdoc;

    herdoc = 0;
    curs = *head;
    while (curs && curs->type != PIPE)
    {
        if (curs->file == HEREDOC_LIM)
            herdoc++;
        curs = curs->next;
    }
    return (herdoc);
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

char **infile_getter(t_cmd **head)
{
    char    **infile;
    t_cmd   *curs;
    int i;

    i = 0;
    infile = malloc(sizeof(char *)* (infile_size(head) + 1));
    curs = (*head);
     while (curs && curs->type != PIPE)
    {
        if (curs->file == INFILE)
        {
            infile[i] = curs->content;
            i++;
        }
        curs = curs->next;
    }
    infile[i] = NULL;
    return (infile);
}

char **outfile_getter(t_cmd **head)
{
    char    **outfile;
    t_cmd   *curs;
    int i;

    i = 0;
    outfile = malloc(sizeof(char *)* (outfile_size(head) + 1));
    curs = (*head);
    while (curs && curs->type != PIPE)
    {
        if (curs->file == OUTFILE)
        {
            outfile[i] = curs->content;
            i++;
        }
        curs = curs->next;
    }
    outfile[i] = NULL;
    return (outfile);
}

char **append_getter(t_cmd **head)
{
    char    **append;
    t_cmd   *curs;
    int i;

    i = 0;
    append = malloc(sizeof(char *)* (append_size(head) + 1));
    curs = (*head);
    while (curs && curs->type != PIPE)
    {
        if (curs->file == APPEND)
        {
            append[i] = curs->content;
            i++;
        }
        curs = curs->next;
    }
    append[i] = NULL;
    return (append);
}

char **herdoc_getter(t_cmd **head)
{
    char    **heredoc;
    t_cmd   *curs;
    int i;

    i = 0;
    heredoc = malloc(sizeof(char *)* (heredoc_size(head) + 1));
    curs = (*head);
     while (curs && curs->type != PIPE)
    {
        if (curs->file == HEREDOC_LIM)
        {
            heredoc[i] = curs->content;
            i++;
        }
        curs = curs->next;
    }
    heredoc[i] = NULL;
    return (heredoc);
}
/*Hadchi kaykhleeeee3*/
t_cmd_table *build_commandtable_node(t_cmd **head)
{
    t_cmd_table *node;

    node = (t_cmd_table *)malloc(sizeof(t_cmd_table));
    if (!node)
        return (NULL);
    node->mode = DEFAULT;
    node->cmd_table =  cmd_table_remplisseur(head);
    node->infile = infile_getter(head);
    node->outfile = outfile_getter(head);
    node->append =  append_getter(head);
    node->here_doc = herdoc_getter(head);
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

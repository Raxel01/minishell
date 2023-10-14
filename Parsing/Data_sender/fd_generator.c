/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_generator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 23:20:49 by abait-ta          #+#    #+#             */
/*   Updated: 2023/10/14 23:21:13 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Header/Parsing.h"

void    init_fd(t_in_out *fd)
{
    fd->in_fd = dup(STDIN_FILENO);
    fd->out_fd = dup(STDOUT_FILENO);
    if (fd->in_fd == -1 || fd->out_fd == -1)
        error_announcer(strerror(errno), 0);
}

t_in_out process_fd(t_cmd **head)
{
    t_cmd       *curs;
    t_in_out    fd;
    
    init_fd(&fd);
    curs = (*head);
    while (curs && curs->type != PIPE)
    {
        if (curs->file == OUTFILE || curs->file == APPEND || curs->file == INFILE)
        {
            if (curs->file == OUTFILE)
                fd.out_fd = open(curs->content, O_CREAT | O_WRONLY | O_TRUNC, 0666);
            else if (curs->file == APPEND)
                fd.out_fd = open (curs->content, O_CREAT | O_WRONLY | O_APPEND, 0666);
            else
                fd.in_fd = open (curs->content, O_RDONLY);
            if (fd.out_fd == -1 || fd.in_fd == -1)
            {
                error_announcer(strerror(errno), 0);
                break;
            }       
        }
        curs = curs->next;
    }
    return (fd);
}
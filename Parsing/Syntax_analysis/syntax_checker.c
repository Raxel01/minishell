/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:53:06 by abait-ta          #+#    #+#             */
/*   Updated: 2023/09/24 22:09:26 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Header/Parsing.h"

void    error_announcer(int fd, char *error)
{
        write(fd, error, ft_strlen(error));
}

int syntax_error(t_token_list *head)
{
    t_token_list *cursur;
    
    
    cursur = head;
    while (cursur)
    {
        if (cursur->type == SYNTAX_ERROR)
        {
            if (cursur->state == Q_UNCLOSE)
                error_announcer(STDERR_FILENO, "bash : syntax error unclosed `' OR \"'\n");
            else if (cursur->state == RED_ERR)
                error_announcer(STDERR_FILENO, "bash : syntax error false redirection `< > << >>'\n");
            else
                error_announcer(STDERR_FILENO, "dick\n");
            return (ERROR_EXIT);
        }
        cursur = cursur->next;
    }
    return (SUCCES_PROC);
}
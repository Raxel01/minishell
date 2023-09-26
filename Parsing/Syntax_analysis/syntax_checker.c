/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:53:06 by abait-ta          #+#    #+#             */
/*   Updated: 2023/09/26 20:43:21 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Header/Parsing.h"

/******************************/
// case checked :
//*****QUOTES***
// unclose quote (single double) TRUE
//*****REDIRECTION***
// false redirection >>>> <<<<<
// Redirection Logic changed 
/**********PIPES*************/
//Pipe in ladt noeud [| => next == NULL]
/*******************************/
void    error_announcer(int fd, char *error)
{
        write(fd, error, ft_strlen(error));
}

void error_type(t_token_list *cursur)
{
    if (cursur->state == Q_UNCLOSE)
                error_announcer(STDERR_FILENO, "bash : syntax error unclosed `' OR \"'\n");
    else if (cursur->state == RED_ERR)
            error_announcer(STDERR_FILENO, "bash : syntax error false redirection `< > << >>'\n");
}

int    redir_check(t_token_list *cursur)
{
    t_token_list *tokens;
    
    if (cursur->type == OUT_REDIR && cursur->next->type == PIPE)
        return (SUCCES_PROC);
    tokens = cursur->next;
    while (tokens && tokens->type == A_SPACE)
        tokens = tokens->next;
    if (!tokens ||  tokens->type != WORD || !ft_strcmp(tokens->token, ""))
        return (ERROR_EXIT);
    return (SUCCES_PROC);
}

int    redir_case(enum e_token_type	type)
{
    return(type ==IN_REDIR || type ==OUT_REDIR \
        || type ==APPEND_SYM || type ==HERE_DOC);
}

int syntax_error(t_token_list *head)
{
    t_token_list *cursur;
    
    cursur = head;
    while (cursur)
    {
        if (cursur->type == SYNTAX_ERROR)
        {
            error_type(cursur);  
            return (ERROR_EXIT);
        }
        if (redir_case(cursur->type))
        {
            if (redir_check(cursur) == ERROR_EXIT)
            {
                error_announcer(STDERR_FILENO, "syntax error bad use of redir OR ambiguous redir `< > << >>'\n");
                return (ERROR_EXIT);
            } 
        }
        cursur = cursur->next;
    }
    return (SUCCES_PROC);
}
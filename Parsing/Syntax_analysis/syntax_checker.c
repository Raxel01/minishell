/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:53:06 by abait-ta          #+#    #+#             */
/*   Updated: 2023/09/27 21:30:03 by abait-ta         ###   ########.fr       */
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
// change the Logic of pipe too 
/*******************************/

void error_type(t_token_list *cursur)
{
    if (cursur->state == Q_UNCLOSE)
                error_announcer(STDERR_FILENO, "bash : syntax error unclosed `' OR \"'\n");
    else if (cursur->state == RED_ERR)
            error_announcer(STDERR_FILENO, "bash : syntax error false redirection `< > << >>'\n");
}

int    redir_analyser(t_token_list *cursur)
{
    t_token_list *tokens;
    
    if (cursur->next)
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

int pipe_analyser (t_token_list *cursus)
{
    t_token_list *behind;
    t_token_list *forward;
    
    behind = behind_getter(cursus);
    forward = forward_getter(cursus);
    if (!behind || !forward || ((behind->type != WORD && behind->next->type != PIPE)) \
        || (forward->type != WORD && !redir_case(forward->type)))
        return (ERROR_EXIT);
    return (SUCCES_PROC);
}

int syntax_error(t_token_list *head)
{
    t_token_list *cursur;
    
    cursur = head;
    while (cursur)
    {
        if (cursur->type == SYNTAX_ERROR) 
            return (error_type(cursur), ERROR_EXIT);
        if (redir_case(cursur->type))
            if (redir_analyser(cursur) == ERROR_EXIT)
                return (error_announcer(STDERR_FILENO, \
                    "syntax error bad use of redir OR ambiguous redir `< > << >>'\n"), ERROR_EXIT);
        if (cursur->type == PIPE)
            if (pipe_analyser(cursur) == ERROR_EXIT)
                return(error_announcer(STDERR_FILENO, \
                    "syntax error : illegal use of pipe `|\'\n"), ERROR_EXIT);
        cursur = cursur->next;
    }
    return (SUCCES_PROC);
}
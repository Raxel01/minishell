/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:53:06 by abait-ta          #+#    #+#             */
/*   Updated: 2023/10/27 22:25:16 by abait-ta         ###   ########.fr       */
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

void	error_type(t_token_list *cursur)
{
	if (cursur->state == Q_UNCLOSE)
		error_announcer("unclosed `' OR \"'", 1);
	else if (cursur->state == RED_ERR)
		error_announcer("error redirection `< > << >>'", 1);
}

/*Here for case ls > $NOT_FOUND_VAR considered*/
/*as ambigious but id the enter in "" error in it */
int	redir_analyser(t_token_list *cursur)
{
	t_token_list	*tokens;

	if (cursur->next)
		if (cursur->type == OUT_REDIR && cursur->next->type == PIPE)
			return (SUCCES_PROC);
	tokens = cursur->next;
	while (tokens && tokens->type == A_SPACE)
		tokens = tokens->next;
	if (!tokens || (tokens->type != WORD && tokens->type != EXIT_STATUS)
		|| (!ft_strcmp(tokens->token, "") && tokens->state == NORMAL))
		return (ERROR_EXIT);
	return (SUCCES_PROC);
}

int	redir_case(enum e_token_type type)
{
	return (type == IN_REDIR || type == OUT_REDIR || type == APPEND_SYM
		|| type == HERE_DOC);
}

int	pipe_analyser(t_token_list *cursus)
{
	t_token_list	*behind;
	t_token_list	*forward;

	behind = behind_getter(cursus);
	forward = forward_getter(cursus);
	if (!behind || !forward || (behind->type != WORD
			&& behind->type != EXIT_STATUS && !is_outred(behind, forward))
		|| (forward->type != WORD && forward->type != EXIT_STATUS
			&& !redir_case(forward->type)))
		return (ERROR_EXIT);
	return (SUCCES_PROC);
}

int	syntax_analysis(t_token_list *head)
{
	t_token_list	*cursur;

	cursur = head;
	while (cursur)
	{
		if (cursur->type == SYNTAX_ERROR)
			return (error_type(cursur), ERROR_EXIT);
		if (redir_case(cursur->type))
			if (redir_analyser(cursur) == ERROR_EXIT)
				return (error_announcer("redir-ambiguous redir", 1),
					ERROR_EXIT);
		if (cursur->type == PIPE)
			if (pipe_analyser(cursur) == ERROR_EXIT)
				return (error_announcer("illegal pipe `|'", 1), ERROR_EXIT);
		cursur = cursur->next;
	}
	return (SUCCES_PROC);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_outfunction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 21:28:17 by abait-ta          #+#    #+#             */
/*   Updated: 2023/10/09 19:38:49 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Header/Parsing.h"

void	error_announcer(char *error, int syntax)
{
	char *syntaxe;
	
	syntaxe = "syntax error : ";
	if (syntax)
    	write (STDERR_FILENO, syntaxe, ft_strlen(syntaxe));
	write(STDERR_FILENO, error, ft_strlen(error));
}

t_token_list	*behind_getter(t_token_list *cursus)
{
	t_token_list	*behind;

	behind = cursus->prev;
	while (behind && behind->type == A_SPACE)
		behind = behind->prev;
	return (behind);
}

t_token_list	*forward_getter(t_token_list *cursus)
{
	t_token_list	*forward;

	forward = cursus->next;
	while (forward && forward->type == A_SPACE)
		forward = forward->next;
	return (forward);
}

int	is_outred(t_token_list *behind, t_token_list *forward)
{
	if (behind->type == OUT_REDIR)
	{
		if (behind->next->type == PIPE && !redir_case(forward->type))
			return (1);
		else
			return (0);
	}
	return (0);
}

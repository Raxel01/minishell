/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_outfunction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 21:28:17 by abait-ta          #+#    #+#             */
/*   Updated: 2023/11/11 17:24:02 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Header/Parsing.h"

void	error_announcer(char *error, int syntax)
{
	char	*syntaxe;

	if (syntax == 666)
	{
		write(STDERR_FILENO, "unset : ", 8);
		write(STDERR_FILENO, "bad variable name : \n", 21);
		write(2, "\"https://www.linkedin.com/pulse/", 32);
		write(2, "bash-scripting-conventions-engin-polat\"\n", 40);
		return ;
	}
	syntaxe = "syntax error : ";
	if (syntax)
		write (STDERR_FILENO, syntaxe, ft_strlen(syntaxe));
	write(STDERR_FILENO, error, ft_strlen(error));
	write(1, "\n", 1);
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

void	catche_signal(void)
{
	signal(SIGINT, seg_handler_c);
	signal(SIGQUIT, SIG_IGN);
}

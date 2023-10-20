/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 19:14:40 by abait-ta          #+#    #+#             */
/*   Updated: 2023/10/20 16:50:34 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Header/Parsing.h"

char	*home_geter(char *commande, t_token_list **token,
		enum e_token_type t_type, enum e_token_state s_token)
{
	add_tokens_to_list(token, build_new_token_node(ft_strndup("$HOME", \
		ft_strlen("$HOME")), t_type, s_token));
	return (commande + 1);
}

int	set_j(char *command, int j)
{
	if (command[j + 1] && command[j + 1] != '\"')
		j++;
	return (j);
}

int	var_extracter(char *commande, int j)
{
	while (commande[j + 1] && (is_alphanum(commande[j + 1]) \
		|| commande[j + 1] == '_'))
		j++;
	return (j);
}

enum e_token_type	type_is(char c)
{
	if (c == '?')
		return (EXIT_STATUS);
	else
		return (SPECIAL_VAR);
}

int	true_state(t_token_list *current)
{
	return (current->type != EXIT_STATUS && \
		(current->state == IN_SQUOT || \
		current->state == IN_DQUOT || current->type == WORD));
}

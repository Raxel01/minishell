/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner_sequel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:55:47 by abait-ta          #+#    #+#             */
/*   Updated: 2023/09/24 17:02:39 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Header/Parsing.h"

int	true_case_quote(char *to_search)
{
	int	i;

	i = 0;
	if (!to_search)
		return (0);
	while (to_search[i])
	{
		if (to_search[i] == '\'' || to_search[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

char	*extract_clean(char *token, int to_alloc, char c)
{
	char	*new_token;
	int		i;
	int		j;

	new_token = (char *)malloc((sizeof(char) * to_alloc));
	j = 0;
	i = 0;
	while (token[i])
	{
		if (token[i] != c)
		{
			new_token[j] = token[i];
			j++;
		}
		i++;
	}
	new_token[j] = '\0';
	return (new_token);
}

int	new_token_len(char *new_token, enum e_token_state state)
{
	int	i;
	int	len;

	len = 0;
	i = -1;
	if (state == IN_SQUOT)
	{
		while (new_token[++i])
		{
			if (new_token[i] != '\'')
				len++;
		}
	}
	else if (state == IN_DQUOT)
	{
		while (new_token[++i])
		{
			if (new_token[i] != '\"')
				len++;
		}
	}
	return (len);
}

int	affect_index(t_token_list **token)
{
	t_token_list	*cursur;
	int				node_member;

	node_member = 0;
	cursur = (*token);
	while (cursur)
	{
		cursur->index = node_member;
		node_member++;
		cursur = cursur->next;
	}
	return (node_member);
}

void	init_holder(t_pos_get **holder, t_token_list **tokens)
{
	(*holder)->start = 0;
	(*holder)->end = 0;
	(*holder)->flag = 0;
	(*holder)->node_member = affect_index(tokens);
}

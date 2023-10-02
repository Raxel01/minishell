/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner_end.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:09:59 by abait-ta          #+#    #+#             */
/*   Updated: 2023/09/30 13:52:25 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Header/Parsing.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join;
	int		i;
	int		j;
	int		len_s1;
	int		len_s2;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	join = (char *)malloc(len_s1 + len_s2 + 1);
	if (!join)
		return (NULL);
	i = -1;
	j = -1;
	while (++i < len_s1)
		join[i] = s1[i];
	while (++j < len_s2)
		join[i + j] = s2[j];
	join[i + j] = '\0';
	free(s1);
	return (join);
}

char	*assemble_data(t_token_list *begin, int end)
{
	char	*join;

	join = ft_strndup(begin->token, (int)ft_strlen(begin->token));
	while (begin->index < end)
	{
		join = ft_strjoin(join, begin->next->token);
		begin = begin->next;
	}
	return (join);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	free_region(t_token_list **start, t_token_list **end)
{
	t_token_list	*current;
	t_token_list	*next;

	current = *start;
	while (current != NULL)
	{
		next = current->next;
		free(current->token);
		free(current);
		current = next;
		if (current == (*end))
		{
			free(current->token);
			free(current);
			break;
		}
	}
}

/*I KNOW THIS IS A BAD NAME*/
void	specialcase_handler(t_token_list **tokens)
{
	t_token_list	*cursur;
	t_pos_get		*to_extract;

	cursur = (*tokens);
	while (cursur)
	{
		to_extract = index_range_getter(tokens);
		if (to_extract->start != to_extract->end)
		{
			addclean_token(tokens, to_extract->start, to_extract->end,
				data_assembler(tokens, to_extract));
			cursur = (*tokens);
		}
		cursur = cursur->next;
		free(to_extract);
	}
}

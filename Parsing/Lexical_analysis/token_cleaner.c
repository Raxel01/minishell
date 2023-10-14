/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_cleaner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:40:05 by abait-ta          #+#    #+#             */
/*   Updated: 2023/10/14 23:12:32 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Header/Parsing.h"

t_token_list	*data_assembler(t_token_list **tokens, t_pos_get *position)
{
	t_token_list	*cursur;
	t_token_list	*new_node;

	cursur = (*tokens);
	while (cursur)
	{
		if (cursur->index == position->start)
		{
			new_node = build_new_token_node(assemble_data(cursur,
						position->end), WORD, NORMAL);
			new_node->index = position->start;
			new_node->prev = cursur->prev;
		}
		if (cursur->index == position->end)
			new_node->next = cursur->next;
		cursur = cursur->next;
	}
	return (new_node);
}

void	addclean_token(t_token_list **head, int start_index, \
		int end_index, t_token_list *clean_node)
{
	t_token_list	*start;
	t_token_list	*end;
	int				i;

	start = *head;
	end = *head;
	i = -1;
	while (++i < start_index && start != NULL)
		start = start->next;
	i = -1;
	while (++i < end_index && end != NULL)
		end = end->next;
	if (start->prev == NULL)
		*head = clean_node;
	else
		start->prev->next = clean_node;
	if (end->next != NULL)
		end->next->prev = clean_node;
	clean_node->prev = start->prev;
	clean_node->next = end->next;
	free_region(&start, &end);
}

t_pos_get	*index_range_getter(t_token_list **tokens)
{
	t_pos_get		*holder;
	t_token_list	*current;

	current = (*tokens);
	holder = (t_pos_get *)malloc(sizeof(t_pos_get));
	init_holder(&holder, tokens);
	while (current && current->next)
	{
		while (current && current->next && current->index < holder->node_member \
			&& true_state(current) && true_state(current->next))
		{
			if (holder->flag == 0)
				holder->start = current->index;
			holder->flag = 1;
			current = current->next;
		}
		if (holder->flag)
		{
			holder->end = current->index;
			return (holder);
		}
		current = current->next;
	}
	return (holder);
}

char	*token_withoutquote(char *token, enum e_token_state state)
{
	char	*new_token;
	int		to_alloc;

	new_token = NULL;
	to_alloc = new_token_len(token, state) + 1;
	if (state == IN_SQUOT)
		new_token = extract_clean(token, to_alloc, '\'');
	else if (state == IN_DQUOT)
		new_token = extract_clean(token, to_alloc, '\"');
	free(token);
	return (new_token);
}

void	tokens_cleaner(t_token_list **tokens)
{
	t_token_list	*cursur;

	cursur = (*tokens);
	while (cursur)
	{
		if (true_case_quote(cursur->token) \
			&& (cursur->state == IN_DQUOT || cursur->state == IN_SQUOT))
		{
			cursur->token = token_withoutquote(cursur->token, cursur->state);
			cursur->state = NORMAL;
		}
		cursur = cursur->next;
	}
	specialcase_handler(tokens);
}

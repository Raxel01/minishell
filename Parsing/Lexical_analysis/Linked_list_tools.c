/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Linked_list_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 23:57:41 by abait-ta          #+#    #+#             */
/*   Updated: 2023/11/10 14:26:58 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Header/Parsing.h"

t_token_list	*build_new_token_node(char *token_data, enum e_token_type type,
		enum e_token_state state)
{
	t_token_list	*token;

	token = malloc(sizeof(t_token_list));
	if (!token)
		return (NULL);
	token->token = token_data;
	token->type = type;
	token->state = state;
	token->index = 0;
	token->node_member = 0;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	add_tokens_to_list(t_token_list **token, t_token_list *next_token)
{
	t_token_list	*cursur;

	if (!(*token))
		(*token) = next_token;
	else
	{
		cursur = *token;
		while (cursur->next)
			cursur = cursur->next;
		cursur->next = next_token;
		next_token->prev = cursur;
	}
}

void	free_token_list(t_token_list **head)
{
	t_token_list	*tmp;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->token);
		free(tmp);
	}
	*head = NULL;
}

void	setdefault_env(t_my_env **head_env)
{
	add_member(head_env, build_member("OLDPWD"));
	add_member(head_env, build_member \
		("PWD=/Users/abait-ta/Desktop/OURSHELL"));
	add_member(head_env, build_member("SHLVL=1"));
	add_member(head_env, build_member \
		("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 23:57:38 by abait-ta          #+#    #+#             */
/*   Updated: 2023/09/16 19:54:27 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/Parsing_Header.h"

const char *token_content[] = {
    "WORD",
    "A_SPACE",
    "PIPE",
    "OUT_REDIR",
    "IN_REDIR",
    "ENV_VAR",
    "SPECIAL_VAR",
    "HERE_DOC",
    "APPEND_SYM"
};

const char *token_state[] = {
    "NORMAL",
    "IN_SQUOT",
    "IN_DQUOT"
};

// int	syntaxe_quote_checker(char *commande)
// {
// 	int	s_quote;
// 	int	d_quote;
// 	s_quote = 0;
// 	d_quote = 0;
// 	while (commande && *commande)
// 	{
// 		if (*commande == '\'')
// 			s_quote++;
// 		else if (*commande == '\"')
// 			d_quote++;
// 		commande++;
// 	}
// 	if ((s_quote % 2 != 0) || (d_quote % 2 != 0))
// 		return (0);
// 	return (1);
// }

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

void    print_tokens(t_token_list **begin)
{
    t_token_list *cursur;
    cursur = (*begin);
    printf("*******************************************************************\n");
    printf("*        TOKENS         |       TOKEN TYPE      |   TOKEN STATE   *\n");
    printf("*******************************************************************\n");
	while (cursur)
    {
        printf ("*%-20s\t|\t%-10s\t|\t%-10s*\n", cursur->token, token_content[cursur->type], token_state[cursur->state]);
    	printf("*******************************************************************\n");
            cursur = cursur->next;
    }
}

void    print_tokensat(t_token_list **begin)
{
    t_token_list *cursur;
    cursur = (*begin);
	while (cursur)
    {
        printf ("%-10d ", cursur->index);
            cursur = cursur->next;
			if (cursur == NULL)
				printf("\n");
    }
}
// ============HERE======================================================================
int new_token_len(char *new_token, enum e_token_state state)
{
	int i;
	int len;
	
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
	else if(state == IN_DQUOT)
	{
		while (new_token[++i])
		{
			if (new_token[i] != '\"')
				len++;
		}
	}
	return (len);
}

char*	extract_clean(char *token, int to_alloc, char c)
{
	char *new_token;
	int i;
	int j;

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

char*	token_withoutquote(char *token, enum e_token_state state)
{
	char *new_token;
	int to_alloc;

	new_token = NULL;
	to_alloc = new_token_len(token, state) + 1;
	if (state == IN_SQUOT)
		new_token = extract_clean(token, to_alloc, '\'');
	else if (state == IN_DQUOT)
		new_token = extract_clean(token, to_alloc, '\"');
	free(token);
	return (new_token);
}

int true_case_quote(char *to_search)
{
	int i;

	i = 0;
	while (to_search[i])
	{
		if (to_search[i] == '\'' || to_search[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

int	affect_index(t_token_list **token)
{
	t_token_list *cursur;
	int node_member;
	
	node_member = 0;
	cursur = (*token);
	while (cursur)
	{
		cursur->index = node_member;
		node_member++;
		cursur = cursur->next;
	}
	return(node_member);
}

void	init_holder(t_pos_get ** holder,t_token_list **tokens)
{
	(*holder)->start	= 0;
	(*holder)->end		= 0;
	(*holder)->flag		= 0;
	(*holder)->node_member = affect_index(tokens);
}

//alloc a pointer to hold start, end; should be free when end operation
t_pos_get *index_range_getter(t_token_list **tokens)
{
    t_pos_get		*holder;
    t_token_list	*current;

    current = (*tokens);
    holder = (t_pos_get *)malloc(sizeof(t_pos_get));    
	init_holder(&holder, tokens);
	while (current && current->next){
        while (current && current->next && current->index < holder->node_member
		&& (current->state == IN_SQUOT || current->state == IN_DQUOT || current->type == WORD) &&
               (current->next->state == IN_SQUOT || current->next->state == IN_DQUOT || current->next->type == WORD))
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

//allot of leak;
char*	assemble_data(t_token_list *begin,int end)
{
	char *join;
	
	join = ft_strndup(begin->token, (int )ft_strlen(begin->token));
	while (begin->index < end)
	{
		join = ft_strjoin(join, begin->next->token);
		begin = begin->next;
	}
	return (join);
}
//ALLOC NEW_NODE SHOULD FREE_IT
t_token_list *data_assembler(t_token_list **tokens,t_pos_get *position)
{
	t_token_list *cursur;
	t_token_list *new_node;
	
	cursur = (*tokens);
	while (cursur)
	{
		if (cursur->index == position->start)
		{
			new_node = build_new_token_node(assemble_data(cursur, position->end) ,WORD,NORMAL);
			new_node->index = position->start;
			new_node->prev = cursur->prev;
		}
		if (cursur->index == position->end)
			new_node->next = cursur->next;
		cursur = cursur->next;
	}
	return(new_node);
}

/*visit all node : if a node contien a (' || ") the clean this token to be !quote*/
/*	// Special case: Removing nodes at the beginning*/
/*Special case: Removing nodes at the end*/
/*Insert the replacement node in place*/
void addclean_token(t_token_list **head, int start_index, int end_index, t_token_list *replacementNode) {

    t_token_list *start;
    t_token_list *end;
	int			 i;
	
	start = *head;
	end = *head;
	i = -1;
    while(++i < start_index && start != NULL){
        start = start->next;}
	i = -1;
	while (++i < end_index && end != NULL)
        end = end->next;
    if (start->prev == NULL)
        *head = replacementNode;
	else
        start->prev->next = replacementNode;
    if (end->next != NULL){
        end->next->prev = replacementNode;
	}
    replacementNode->prev = start->prev;
    replacementNode->next = end->next;
}

void	tokens_cleaner(t_token_list **tokens)
{
	t_token_list *cursur;
	t_pos_get *to_extract;

	cursur = (*tokens);
	while (cursur)
	{
		if (true_case_quote(cursur->token) )
		{
			cursur->token = token_withoutquote(cursur->token, cursur->state);
			cursur->state = NORMAL;
		}
		cursur = cursur->next;
	}
	cursur = (*tokens);
	while (cursur)
	{
		to_extract = index_range_getter(tokens);
		if (to_extract->start != to_extract->end)
			addclean_token(tokens, to_extract->start, to_extract->end, \
				data_assembler(tokens, to_extract));
		cursur = cursur->next;
		free(to_extract);
	}
}
/*should free the tokens selected to be joined*/
t_token_list	*lexical_analysis(char *commande)
{
	t_token_list	*token;

	token = NULL;
	while (commande && *commande)
		commande = lexems_finder(commande, &token);
	tokens_cleaner(&token);
	print_tokens(&token);
	return (token);
}

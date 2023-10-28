/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docbuilder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:43:26 by abait-ta          #+#    #+#             */
/*   Updated: 2023/10/28 21:43:11 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Header/Parsing.h"

int	here_doc_(char *eof, enum e_token_state state, t_my_env **env)
{
	int		tube[2];
	char	*readed_data;

	if (pipe(tube) == -1)
		return (error_announcer(strerror(errno), 0), -1);
	while (1)
	{
		readed_data = readline("> ");
		if (!readed_data || !ft_strcmp(readed_data, eof))
		{
			if (readed_data)
				free(readed_data);
			break ;
		}
		if (state == NORMAL && ft_strchr(readed_data, '$') != 404)
			readed_data = data_expander(readed_data, env);
		write(tube[1], readed_data, ft_strlen(readed_data));
		write(tube[1], "\n", 1);
		free(readed_data);
	}
	return (close(tube[1]), tube[0]);
}

char	*data_expander(char *readed_data, t_my_env **env)
{
	t_here_doc	*head;
	char		*begin;
	char		*new_line;

	head = NULL;
	begin = readed_data;
	while (readed_data && *readed_data)
		readed_data = extract_elems(readed_data, &head);
	elem_expansion(&head, env);
	free(begin);
	new_line = concatenate_data(&head);
	free_herelist(&head);
	return (new_line);
}

char	*get_var(char *readed_data, enum e_heredoc type, t_here_doc **head)
{
	int	len;

	if (digit_case(readed_data[1]) || readed_data[1] == '?' \
		|| readed_data[1] == '$')
	{
		list_builder(head, creatnodes(ft_strndup(readed_data, 2), type));
		return (readed_data + 2);
	}
	len = 0;
	while (readed_data[len + 1] && (is_alphanum(readed_data[len + 1]) \
			|| readed_data[len + 1] == '_'))
		len++;
	if (len)
		list_builder(head, creatnodes(ft_strndup(readed_data, len + 1), type));
	else
		list_builder(head, creatnodes(ft_strndup(readed_data, 1), STRING));
	return (readed_data + len + 1);
}

char	*get_string(char *readed_data, enum e_heredoc type, t_here_doc **head)
{
	int	i;

	i = 0;
	while (readed_data[i] && readed_data[i] != '$')
		i++;
	list_builder(head, creatnodes(ft_strndup(readed_data, i), type));
	return (readed_data + i);
}

char	*extract_elems(char *readed_data, t_here_doc **head)
{
	if (*readed_data != '$')
		readed_data = get_string(readed_data, STRING, head);
	else
		readed_data = get_var(readed_data, VAR, head);
	return (readed_data);
}

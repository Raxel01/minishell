/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docbuilder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:43:26 by abait-ta          #+#    #+#             */
/*   Updated: 2023/11/03 19:20:22 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Header/Parsing.h"

int g_signal = 0;

char	*here_doc_(char *eof, enum e_token_state state,	\
		t_my_env **env, char *index)
{
	int		heredoc;
	char	*readed_data;
	char	*filename;

	filename = ft_strjoin(ft_strdup("/tmp/.her_talb"), index);
	heredoc = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (heredoc == -1)
		return (error_announcer(strerror(errno), 0), \
			free_elem(eof, index), NULL);
	while (1)
	{
		g_signal = 1;
		signal(SIGINT, seg_handler_c);
		readed_data = readline("> ");
		if (!readed_data || !ft_strcmp(readed_data, eof))
		{
			free(readed_data);
			break ;
		}
		if (state == NORMAL && ft_strchr(readed_data, '$') != 404)
			readed_data = data_expander(readed_data, env);
		readed_data = pushcontent_clean(heredoc, readed_data);
	}
	free_elem(eof, index);
	return (filename);
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

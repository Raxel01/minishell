/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Global_outfunc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:55:20 by abait-ta          #+#    #+#             */
/*   Updated: 2023/11/11 20:03:28 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Header/Parsing.h"

void	white_space(char *str, size_t i, size_t len, int *state)
{
	*state = 0;
	if (i >= len || *state == 1)
		return ;
	if (str[i] == ' ' || str[i] == '\t')
		white_space(str, i + 1, len, state);
	else
	{
		*state = 1;
		return ;
	}
}

void	clean_memory(t_token_list **token)
{
	free_token_list(token);
}

/*mode = 1 mean we sett the value*/
int	status_setter(int code, int mode)
{
	static int	exit_status;

	if (mode)
		exit_status = code;
	return (exit_status);
}

void	free_cmd_table(t_cmd_table **cmd)
{
	t_cmd_table	*tmp;
	int			i;

	if (!cmd)
		return ;
	while (*cmd)
	{
		tmp = *cmd;
		*cmd = (*cmd)->next;
		i = 0;
		while (tmp->cmd_table[i])
		{
			free(tmp->cmd_table[i]);
			i++;
		}
		free(tmp->cmd_table);
		free(tmp);
	}
	*cmd = NULL;
}

void	unlink_heredoc(void)
{
	int		index;
	char	*filename;
	char	*forward;

	filename = NULL;
	index = 1;
	while (1)
	{
		forward = ft_itoa(index);
		filename = ft_strjoin(ft_strdup("/tmp/.her_talb"), forward);
		if (unlink(filename) == -1)
		{
			free(filename);
			free(forward);
			break ;
		}
		free(forward);
		free(filename);
		index++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Global_outfunc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:55:20 by abait-ta          #+#    #+#             */
/*   Updated: 2023/10/20 18:11:55 by abait-ta         ###   ########.fr       */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .show_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 13:21:53 by abait-ta          #+#    #+#             */
/*   Updated: 2023/10/27 12:02:32 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Header/Parsing.h"

const char	*token_content[] = {"WORD", "A_SPACE", "PIPE", "OUT_REDIR",
		"IN_REDIR", "ENV_VAR", "SPECIAL_VAR", "HERE_DOC", "APPEND_SYM",
		"SYNTAX_ERROR", "EXIT_STATUS"};

const char	*token_state[] = {"NORMAL", "IN_SQUOT", "IN_DQUOT", "Q_UNCLOSE",
		"RED_ERR"};

const char	*content_category[] = {"NONE", "CMD", "OPTION", "FD_FILE",
		"PIPELEFT", "PIPERIGHT"};

const char	*files[] = {
	"NONEF",
	"OUTFILE",
	"INFILE",
	"APPEND",
	"HEREDOC_LIM",
};

void	print_tokens(t_token_list **begin)
{
	t_token_list	*cursur;

	if (!(*begin))
		return ;
	cursur = (*begin);
	printf("*******************************************************************\n");
	printf("*        TOKENS         |       TOKEN TYPE      |   TOKEN STATE   *\n");
	printf("*******************************************************************\n");
	while (cursur)
	{
		printf("*%-20s\t|\t%-10s\t|\t%-10s*\n", cursur->token,
			token_content[cursur->type], token_state[cursur->state]);
		printf("*******************************************************************\n");
		cursur = cursur->next;
	}
}

void	printcmd_list(t_cmd **cmd)
{
	t_cmd	*cursur;

	cursur = (*cmd);
	printf("*********************************************************************\n");
	printf("*        CONTENT         |        CATEGORY       |       MODE       *\n");
	printf("*********************************************************************\n");
	while (cursur)
	{
		printf("*%-20s\t|\t%-10s\t|\t%-10s *\n", cursur->content,
			content_category[cursur->category], files[cursur->file]);
		printf("*********************************************************************\n");
		cursur = cursur->next;
	}
}

void	print_cmd_table(t_cmd_table **cmd_tab)
{
	t_cmd_table	*curs;
	int			i;
	int			j;
	int			count;

	j = 1;
	count = 1;
	i = 0;
	curs = *cmd_tab;
	if (!curs)
	{
		printf("EMPTY\n");
		return ;
	}
	while (curs)
	{
		i = 0;
		count = 1;
		printf("*********Node[%d]***************************\n", j);
		printf("*   CMD_OPTION     |         FD           *\n");
		while (curs->cmd_table[i])
		{
			printf("*[%d] : %-10s  |", i, curs->cmd_table[i]);
			if (count)
			{
				printf("\t IN_FD : %d \t  *\n* \t\t\t OUT_FD : %d       *\n",
					curs->in_fd, curs->out_fd);
				count--;
			}
			printf("\n");
			i++;
		}
		printf("\n*******************************************\n");
		if (curs->next)
			printf("\t           *\n\t           *\n\t           \\/\n");
		curs = curs->next;
		j++;
	}
}

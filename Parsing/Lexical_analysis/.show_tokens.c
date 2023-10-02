/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .show_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 13:21:53 by abait-ta          #+#    #+#             */
/*   Updated: 2023/10/02 17:51:04 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Header/Parsing.h"

const char *token_content[] = {"WORD", "A_SPACE", 
	"PIPE", "OUT_REDIR",
			"IN_REDIR", "ENV_VAR", 
"SPECIAL_VAR", "HERE_DOC", "APPEND_SYM",
			"SYNTAX_ERROR", "EXIT_STATUS"};

const char *token_state[] = {"NORMAL", "IN_SQUOT",
 "IN_DQUOT", "Q_UNCLOSE",
			"RED_ERR"};

const char *content_category[] = {"NONE","CMD", "OPTION", "FD_FILE", "PIPELEFT", "PIPERIGHT"
};

const char *files[] = {"NONE", "OUTFILE",
	"INFILE",
	"APPEND",
	"HEREDOC_LIM",};

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

void    printcmd_list(t_cmd **cmd)
{
    t_cmd *cursur;

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

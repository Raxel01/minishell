/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Global_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 23:58:04 by abait-ta          #+#    #+#             */
/*   Updated: 2023/09/14 20:43:40 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Header/Parsing_Header.h"

void	seg_handler_c(int sigstatus)
{
	(void)(sigstatus);
	printf("\n");
	rl_on_new_line();
	rl_replace_line("",0);
	rl_redisplay();
}

void white_space(char *str, size_t i, size_t len, int *state)
{
	*state = 0;
	if (i >= len || *state == 1)
        return;
	if (str[i] == ' ' || str[i] == '\t')
			white_space(str, i+ 1, len,state);
	else{
		*state = 1;
        return;
	}
}

void history_acces(char *commande)
{
	int		state;
	size_t	i;
	
	i = 0;
	white_space(commande, i, \
		ft_strlen(commande), &state);
    if (state)
	{
		// printf("AddTo_History\n");
        add_history(commande);
	}
}

int	Minishell(void)
{
	t_commande	commande;
	t_token_list *token;
	
	signal(SIGINT, seg_handler_c);
	while (1)
	{
		commande.commande = readline("MINISHELL[~] -> ");
		if (commande.commande == NULL)
			return (0);
		commande.commande = epur_string(commande.commande);
		history_acces(commande.commande);
		token = lexical_analysis(commande.commande);
		free_token_list(&token);
		free(commande.commande);
	}
	return (0);
}

/*تبدو وظيفة عادية لكن هيهاات هيهااات */
int main ()
{
	Minishell();
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Global_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 23:58:04 by abait-ta          #+#    #+#             */
/*   Updated: 2023/09/24 18:15:35 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Header/Parsing.h"

void	seg_handler_c(int sigstatus)
{
	(void)(sigstatus);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

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

void	history_acces(char *commande)
{
	int		state;
	size_t	i;

	i = 0;
	white_space(commande, i, ft_strlen(commande), &state);
	if (state)
		add_history(commande);
}

int	minishell(int ac, char **av, char **env)
{
	t_commande		commande;
	t_token_list	*token;
	my_env			*my_env;

	(void)ac;
	(void)av;
	(void)env;
	signal(SIGINT, seg_handler_c);
	while (1)
	{
		commande.commande = readline("MINISHELL[~] -> ");
		if (commande.commande == NULL)
			return (0);
		commande.commande = epur_string(commande.commande);
		history_acces(commande.commande);
		my_env = import_env(env);
		token = lexical_analysis(commande.commande,&my_env);
		print_tokens(&token);
		free_token_list(&token);
		free_env(&my_env);
		free(commande.commande);
	}
	return (0);
}

/*تبدو وظيفة عادية لكن هيهاات هيهااات */
int	main(int ac, char **av, char **env)
{
	minishell(ac, av, env);
	return (0);
}

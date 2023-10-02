/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Global_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 23:58:04 by abait-ta          #+#    #+#             */
/*   Updated: 2023/10/02 20:03:49 by abait-ta         ###   ########.fr       */
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

void	clean_memory(t_token_list **token, t_my_env **env, char *command)
{
	free_token_list(token);
	free_env(env);
	free(command);
}

void	printos_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '=') != 404)
			printf("%s\n", env[i]);
		i++;
	}
}

char	*get_input_line(char *commande)
{
	commande = readline("MINISHELL[~] -> ");
	if (commande == NULL)
	{
		write(1, "exit\n", 6);
		exit(EXIT_SUCCESS);
	}
	commande = epur_string(commande);
	history_acces(commande);
	return (commande);
}

int	minishell(int ac, char **av, char **env)
{
	t_commande		commande;
	t_token_list	*token;
	t_my_env		*my_env;
	t_cmd			*syntax;

	(void)ac;
	(void)av;
	signal(SIGINT, seg_handler_c);
	while (1)
	{
		commande.commande = get_input_line(commande.commande); 
		my_env = import_env(env);
		token = lexical_analysis(commande.commande, &my_env);
		if (syntax_error(token) == SUCCES_PROC)
		{
			/*HENNA MNIIIN ATBDA NTA LEE3B*/
			syntax= parsing(&token);
			printcmd_list(&syntax);
			free_cmd(&syntax);
			clean_memory(&token, &my_env, commande.commande);
		}
		else
			clean_memory(&token, &my_env, commande.commande);
		// print_tokens(&token);
	}
	return (SUCCES_PROC);
}

/*تبدو وظيفة عادية لكن هيهاات هيهااات */
int	main(int ac, char **av, char **env)
{
	minishell(ac, av, env);
	return (SUCCES_PROC);
}

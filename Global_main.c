/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Global_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 23:58:04 by abait-ta          #+#    #+#             */
/*   Updated: 2023/10/24 13:24:45 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Header/Parsing.h"

void	history_acces(char *commande)
{
	int		state;
	size_t	i;

	i = 0;
	white_space(commande, i, ft_strlen(commande), &state);
	if (state)
		add_history(commande);
}

void	get_input_line(char **commande, t_my_env **my_env)
{
	*commande = readline("└─$ MINISHELL[~] -> ");
	if (*commande == NULL)
	{
		status_setter(EXIT_SUCCESS, 1);
		rl_clear_history();
		free_env(my_env);
		write(1, "exit\n", 6);
		exit(EXIT_SUCCESS);
	}
	*commande = epur_string(*commande);
	history_acces(*commande);
}

/*CTRL\C RECHECK CODE*/
void	seg_handler_c(int status)
{
	(void)status;
	status_setter(130, 1);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	minishell(char **env)
{
	char			*readedline;
	t_token_list	*token;
	t_my_env		*my_env;
	t_cmd_table		*cmd_tabl;

	signal(SIGINT, seg_handler_c);
	my_env = import_env(env);
	readedline = NULL;
	while (1)
	{
		get_input_line(&readedline, &my_env);
		token = lexical_analysis(readedline, &my_env);
		if (syntax_error(token) == SUCCES_PROC)
		{
			cmd_tabl = parsing(&token);
			free_cmd_table(&cmd_tabl);
		}
		else
		{
			status_setter(SYNTAXE_ERR_STATUS, 1);
			clean_memory(&token);
		}
	}
	return (SUCCES_PROC);
}

/*تبدو وظيفة عادية لكن هيهاات هيهااات */
int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	status_setter(0, 1);
	minishell(env);
	return (SUCCES_PROC);
}

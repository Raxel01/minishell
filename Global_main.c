/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Global_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 23:58:04 by abait-ta          #+#    #+#             */
/*   Updated: 2023/10/18 20:21:37 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Header/Parsing.h"

/*********Exist_status_var****************/
int		g_exit_status = 0;
/*****************************************/

void	seg_handler_c(int sigstatus)
{
	(void)(sigstatus);
	status_setter(130);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
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

void	get_input_line(char **commande, t_my_env **my_env)
{
	*commande = readline("└─$ MINISHELL[~] -> ");
	if (*commande == NULL)
	{
		status_setter(EXIT_SUCCESS);
		rl_clear_history();
		free_env(my_env);
		write(1, "exit\n", 6);
		exit(EXIT_SUCCESS);
	}
	*commande = epur_string(*commande);
	history_acces(*commande);
}

void	free_cmd_table(t_cmd_table ** cmd)
{
	t_cmd_table	*tmp;
	int i;

	if (!cmd)
		return;
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
			status_setter(SYNTAXE_ERR_STATUS);
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
	minishell(env);
	return (SUCCES_PROC);
}


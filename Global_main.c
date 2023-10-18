/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Global_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 23:58:04 by abait-ta          #+#    #+#             */
/*   Updated: 2023/10/17 20:00:14 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Header/Parsing.h"

/*********Exist_status_var****************/
int		g_exit_status = 0;
/*****************************************/

void	seg_handler_c(int sigstatus)
{
	(void)(sigstatus);
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

char	*get_input_line(char *commande, t_my_env **my_env)
{
	commande = readline("└─$ MINISHELL[~] -> ");
	if (commande == NULL)
	{
		status_setter(EXIT_SUCCESS);
		rl_clear_history();
		write(1, "exit\n", 6);
		free_env(my_env);
		exit(EXIT_SUCCESS);
	}
	commande = epur_string(commande);
	history_acces(commande);
	return (commande);
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

int	minishell(int ac, char **av, char **env)
{
	t_commande		commande;
	t_token_list	*token;
	t_my_env		*my_env;
	t_cmd_table		*cmd_tabl;
	// int pid;

	(void)ac; (void)av;
	signal(SIGINT, seg_handler_c);
	my_env = import_env(env);
	while (1)
	{
		commande.commande = get_input_line(commande.commande, &my_env);
		token = lexical_analysis(commande.commande, &my_env);
		if (syntax_error(token) == SUCCES_PROC)
		{
			cmd_tabl = parsing(&token);
			print_cmd_table(&cmd_tabl);
			// pid = fork();
			// if (pid == 0)
			// {
			// 	int fd = here_doc_("ABDO", NORMAL, &my_env);
			// 	dup2(fd, 0);
			// 	execve("/usr/bin/cat", cmd_tabl->cmd_table, NULL);
			// }
			// wait(NULL);
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
	minishell(ac, av, env);
	return (SUCCES_PROC);
}


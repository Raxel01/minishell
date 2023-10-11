/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Global_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 23:58:04 by abait-ta          #+#    #+#             */
/*   Updated: 2023/10/11 21:00:07 by abait-ta         ###   ########.fr       */
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

char	*get_input_line(char *commande)
{
	commande = readline("MINISHELL[~] -> ");
	if (commande == NULL)
	{
		status_setter(EXIT_SUCCESS);
		rl_clear_history();
		write(1, "exit\n", 6);
		exit(EXIT_SUCCESS);
	}
	commande = epur_string(commande);
	history_acces(commande);
	return (commande);
}

/*
{
	t_cmd_table	*tmp;

	if (!cmd)
		return (0);
	while (*cmd)
	{
		tmp = *cmd;
		*cmd = (*cmd)->next;
		free(tmp->cmd_table);
		free(tmp->infile);
		free(tmp->outfile);
		free(tmp->append);
		free(tmp->here_doc);
		free(tmp);
	}
	*cmd = NULL;
	return (1);
}*/

void	print_flag(t_my_env **emv)
{
	t_my_env *curs;

	curs = (*emv)->next;
	while (curs)
	{
		if (!ft_strcmp(curs->var ,"PWD"))
			printf ("PWD = %s\n", curs->var_content);
		if (!ft_strcmp(curs->var, "OLDPWD"))
			printf ("OLDPWD = %s\n", curs->var_content);		
	curs = curs->next;
	}
}

int	minishell(int ac, char **av, char **env)
{
	t_commande		commande;
	t_token_list	*token;
	t_my_env		*my_env;
	t_cmd			*cmd_syntax;

	(void)ac; (void)av;
	signal(SIGINT, seg_handler_c);
	cmd_syntax = NULL;
	my_env = import_env(env);
	while (1)
	{
		commande.commande = get_input_line(commande.commande);
		token = lexical_analysis(commande.commande, &my_env);
		if (syntax_error(token) == SUCCES_PROC)
		{
			cmd_syntax = parsing(&token);
			// printcmd_list(&cmd_syntax);
			// print_flag(&my_env);
			// printf ("=================\n");
			char *cmd[]= {"exit", NULL};
			builtin_recognizer(cmd, &my_env);
			// printf ("=================\n");
			// print_flag(&my_env);
			// // printf ("\n=========stat :%d========\n", g_exit_status);
			free_cmd(&cmd_syntax);
			clean_memory(&token, commande.commande);
		}
		else
		{
			status_setter(SYNTAXE_ERR_STATUS);
			clean_memory(&token, commande.commande);
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


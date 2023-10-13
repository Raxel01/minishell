/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Global_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 23:58:04 by abait-ta          #+#    #+#             */
/*   Updated: 2023/10/13 16:44:01 by abait-ta         ###   ########.fr       */
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

void	print_cmd_table(t_cmd_table **cmd_tab)
{
	t_cmd_table *curs;
	int i;
	int j = 1;
	int count = 1;

	i = 0;
	curs = *cmd_tab;
	if (!curs)
		{
			printf("EMPTY\n");
			return;
		}
	while (curs)
	{
		i = 0;
		count = 1;                                    
		printf("*********Node[%d]***************************\n", j);
		printf("*   CMD_OPTION     |         FD           *\n");
		while (curs->cmd_table[i]){
		printf("*[%d] : %-10s  |",i, curs->cmd_table[i]);
		if (count)
			{
				printf ("\t IN_FD : %d \t  *\n* \t\t\t OUT_FD : %d       *\n", curs->in_fd, curs->out_fd);
				count--;
			}
		printf ("\n");
		i++;
		}
		printf("\n*******************************************\n");
		if (curs->next)
			printf("\t           *\n\t           *\n\t           \\/\n");
		curs = curs->next;
		j++;
	}
}

int	minishell(int ac, char **av, char **env)
{
	t_commande		commande;
	t_token_list	*token;
	t_my_env		*my_env;
	t_cmd_table			*cmd_tabl;

	(void)ac; (void)av;
	signal(SIGINT, seg_handler_c);
	my_env = import_env(env);
	while (1)
	{
		commande.commande = get_input_line(commande.commande);
		token = lexical_analysis(commande.commande, &my_env);
		if (syntax_error(token) == SUCCES_PROC)
		{
			cmd_tabl = parsing(&token);
			print_cmd_table(&cmd_tabl);
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


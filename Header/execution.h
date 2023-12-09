/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:19:07 by mboukaiz          #+#    #+#             */
/*   Updated: 2023/11/11 06:33:41 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "Parsing.h"
# include <dirent.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct l_cmd	t_cmd_table;
typedef struct v_envp	t_my_env;

typedef struct s_env
{
	char			*key_env;	
	char			*value_env;
	int				show_option;
	struct s_env	*next;
	char			**paths;
}		t_env;

void	dir(char *cmd);
char	*ft_strdup(char	*s1);
void	dupin(t_cmd_table *cmd);
int		check_if_path(char	*cmd);
char	**dup_func(t_my_env *env);
char	**free_execenv(char **execenv);
char	**ft_split(char	*s, char c);
char	**listconvertion(t_my_env *env);
void	ft_putstr_fd(char *str, int fd);
int		ft_strcmp(char	*s1, char	*s2);
void	find_cmd(t_my_env *env, t_cmd_table *cmd);
int		my_pipes(t_cmd_table *cmd, t_my_env *new_env);
int		ft_strncmp(char	*s1, char	*s2, size_t	n);
void	copy_str(char *s1, char **key, char **value);
void	execution(t_cmd_table	*cmd, t_my_env	*env);
void	str_length(char *s1, int *key_length, int *value_length);
void	child_exec(t_cmd_table *cmd, t_my_env *new_env, int pipe[2]);
void	p_exec(int pid, t_cmd_table *cmd, t_my_env *new_env, int pipe[2]);

#endif

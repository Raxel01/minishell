/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:14:32 by abait-ta          #+#    #+#             */
/*   Updated: 2023/10/22 22:53:16 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/Parsing.h"


// void	ft_swap(t_env_elem *a, t_env_elem *b)
// {
// 	char	*key_tmp;
// 	char	*val_tmp;
// 	key_tmp = a->key;
// 	val_tmp = a->value;
// 	a->key = b->key;
// 	a->value = b->value;
// 	b->key = key_tmp;
// 	b->value = val_tmp;
// }

void	regulateur(t_my_env *curs, t_my_env *next)
{
	char	*t_key;
	char	*t_value;

	t_key = curs->var;
	curs->var = next->var;
	next->var = t_key;
	/*========================*/
	t_value = curs->var_content;
	curs->var_content = next->var_content;
	next->var_content = t_value;
}

void	sorting(t_my_env *env)
{
	t_my_env	*circl;
	
	circl = env;
	while(circl->next)
	{
		if (ft_strcmp(circl->var, circl->next->var) > 0)
		{
			regulateur(circl, circl->next);
			circl = env;
		}
		else
			circl = circl->next;
	}
}

void view_exportedvar(t_my_env **env)
{
	t_my_env *curs;
	
	curs = (*env)->next;
	sorting(curs);
	while (curs)
	{
		write(1, "declare -x ", 12);
		write(1, curs->var, ft_strlen(curs->var));
		write(1, "=", 2);
		write(1, "\"", 2);
		write(1, curs->var_content, ft_strlen(curs->var_content));
		write(1, "\"", 2);
		write(1, "\n", 2);
		curs = curs->next;
	}
	
}

char	*standard_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char )c)
			return ((char *)(s + i + 1));
		i++;
	}
	return (NULL);
}

int	new_strchr(char *s, char c, int *mode)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			if (i != 0 && s[i -1] == '+')
			{
				*mode = M_APPEND;
				return(i - 1);
			}
			*mode = M_ECRASE;
			return (i);
		}
		i++;
	}
	return (ft_strlen(s));
}

int	id_verifier(char *var)
{
	int	i;

	i = 0;
	if (var[i] && (is_alpha(var[i]) || var[i] == '_'))
	{
		while (var[++i])
			if (!(is_alphanum(var[i]) || var[i] == '_'))
				return (0);
		return (1);
	}
	return (0);
}

/*syntaxe export variable[(+)=VALUE]*/
/*two things : Modify an existing var or add new one*/
/****ELEM_VALUE CASE : *************
 *** elem_value = NULL -> NO VALUE to assign; no '='skiip
 *** elem_value = "\0" -> assign "\0" to var;
 *** elem_value exist -> affect value;
*/
void	correct()
{
	char *correct = "correct";
	int j = -1;
	while (correct[++j])
			{
				write(1, &correct[j], 1);
				usleep(49300);
			}
			write(1, "\n", 2);
}

typedef struct export
{
	char	*elem_name;
	char	*elem_value;
	int		mode;
}	t_export;

void	init_elem(t_export *export)
{
	export->elem_name = NULL;
	export->elem_value = NULL;
	export->mode = 0;
}

int	run_export(char **cmd_table, t_my_env **env)
{
	// int			i;
	// t_export	e;
	char *cmd[] = {"env", NULL};
	
	if (!cmd_table[1])
		return (view_exportedvar(env), 0);
	(void)(cmd_table);
	run_env(cmd, env);
	// i = 1;
	// while (cmd_table[i])
	// {
	// 	init_elem(&e);
		// e.elem_name = ft_substr(cmd_table[i], 0, /*\*/
	// 		new_strchr(cmd_table[i], '=', &e.mode));
	// 	e.elem_value = standard_strchr(cmd_table[i], '=');
	// 	printf("var:%s*-->%s|-->mode:%d\n", e.elem_name, e.elem_value, e.mode);
	// 	if (bashvar_norm(e.elem_name))
	// 	{
	// 		correct();
	// 		free(e.elem_name);
	// 	}
	// 	else
	// 		return (free(e.elem_name), /*\*/
	// 			error_announcer("elem:not a valid identifier\n", 0), NOT_VALID);
	// 	i++;
	// }
	return (0);
}

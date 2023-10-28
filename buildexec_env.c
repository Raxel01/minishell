/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildexec_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 02:48:28 by abait-ta          #+#    #+#             */
/*   Updated: 2023/10/28 02:49:14 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Header/Parsing.h"

int	countmembers(t_my_env *env)
{
	t_my_env	*curs;
	int			list_size;

	list_size = 0;
	curs = env;
	while (curs)
	{
		list_size++;
		curs = curs->next;
	}
	return (list_size);
}

/*wtef eila code kidayr*/
char	*assembler(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*joined;
	int		total_len;

	if (!s1 && !s2)
		return (NULL);
	if (!s1 && s2)
		return (ft_strdup(s2));
	if (s1 && !s2)
		return (ft_strdup(s1));
	i = -1;
	j = -1;
	total_len = (ft_strlen(s1) + ft_strlen(s2)) + 1;
	joined = malloc(sizeof(char) * total_len);
	if (joined == NULL)
		return (NULL);
	while (s1[++i])
		joined[i] = s1[i];
	while (s2[++j])
		joined[i + j] = s2[j];
	joined[i + j] = '\0';
	return (joined);
}

/*ugly code for start end*/
char	**listconvertion(t_my_env *env)
{
	t_my_env	*curs;
	int			members;
	char		**exec_env;
	char		*tampon;
	int			i;

	curs = env;
	tampon = NULL;
	members = countmembers(env);
	i = 0;
	exec_env = malloc(sizeof(char *) * (members + 1));
	if (!exec_env)
		return (NULL);
	while (curs)
	{
		tampon = assembler(curs->var, "=");
		exec_env[i++] = assembler(tampon, curs->var_content);
		free(tampon);
		curs = curs->next;
	}
	exec_env[i] = NULL;
	return (exec_env);
}

char	**free_execenv(char **execenv)
{
	int	i;

	i = -1;
	while (execenv[++i])
		free(execenv[i]);
	free(execenv);
	execenv = NULL;
	return (execenv);
}

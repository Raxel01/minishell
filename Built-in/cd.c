/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:14:09 by abait-ta          #+#    #+#             */
/*   Updated: 2023/10/22 19:06:37 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/Parsing.h"

void	env_updater(t_my_env **env, char *to_update, char *update_by)
{
	t_my_env	*curs;

	curs = *env;
	while (curs)
	{
		if (!ft_strcmp(to_update, curs->var))
		{
			free(curs->var_content);
			curs->var_content = ft_strndup(update_by, ft_strlen(update_by));
			return ;
		}
		curs = curs->next;
	}
}

/*USE PATH MAX IN sted OF 1024*/
char	*get_cwd(void)
{
	char	*my_dir;

	my_dir = getcwd(NULL, 1024);
	if (!my_dir)
		status_setter(1, 1);
	return (my_dir);
}

// should free existing dir;
/*goto_path = get_cwd();*/
int	goto_new_dir(char *goto_path, t_my_env **env)
{
	char	*existin_dir;

	existin_dir = get_cwd();
	if (chdir(goto_path) == -1)
	{
		free(existin_dir);
		free(goto_path);
		return (error_announcer(strerror(errno), 0), 1);
	}
	else
	{
		env_updater(env, "OLDPWD", existin_dir);
		env_updater(env, "PWD", goto_path);
		free(existin_dir);
		free(goto_path);
		return (0);
	}
}

char	*getcontent(char *toget, t_my_env **env)
{
	t_my_env	*curs;

	curs = *env;
	while (curs)
	{
		if (ft_strcmp(toget, curs->var) == 0)
			return (ft_strndup(curs->var_content,
					ft_strlen(curs->var_content)));
		curs = curs->next;
	}
	return (NULL);
}

/*no_option alloced free it */
int	run_cd(char **cmd_table, t_my_env **env)
{
	char	*goto_dir;

	if (!cmd_table[1])
	{
		goto_dir = getcontent("HOME", env);
		if (!goto_dir)
			return (error_announcer("cd : HOME not set", 0), 1);
		return (goto_new_dir(goto_dir, env));
	}
	if (cmd_table[1][0] == '-')
	{
		if (cmd_table[1][1] == '\0')
		{
			goto_dir = getcontent("OLDPWD", env);
			if (!goto_dir)
				return (error_announcer("cd : OLDPWD not set", 0), 1);
			return (goto_new_dir(goto_dir, env));
		}
		else
			return (error_announcer("invalid option", 0), 2);
	}
	else
		return (goto_new_dir(ft_strndup(cmd_table[1], ft_strlen(cmd_table[1])),
				env));
}

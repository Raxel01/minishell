/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commande_reform.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 23:57:32 by abait-ta          #+#    #+#             */
/*   Updated: 2023/09/25 18:12:14 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Header/Parsing.h"

int	word_epur_helper(char *commande)
{
	int	word;
	int	i;

	i = 0;
	word = 0;
	while (commande && commande[i])
	{
		if (((commande[i] != ' ' && commande[i] != '\t') && (commande[i
					+ 1] == ' ' || commande[i + 1] == '\t'))
			|| ((commande[i] != ' ' && commande[i] != '\t') && commande[i
				+ 1] == '\0'))
			word++;
		i++;
	}
	return (word);
}

int	epur_len_helper(char *commande)
{
	int	i;
	int	not_whitspace;

	i = 0;
	not_whitspace = 0;
	while (commande && commande[i])
	{
		if (commande[i] != ' ' && commande[i] != '\t')
			not_whitspace++;
		i++;
	}
	return (not_whitspace);
}

void	data_init(t_var *vars, char *commande)
{
	vars->flg = 0;
	vars->epured_string = malloc(sizeof(char) * (epur_len_helper(commande)
				+ (word_epur_helper(commande) - 1) + 1));
	vars->begin = vars->epured_string;
	vars->i = 0;
}

void get_new_string(char *commande ,t_var var)
{
	while (commande[var.i])
	{
		if (commande[var.i] == ' ' || commande[var.i] == '\t')
			var.flg = 1;
		if (!(commande[var.i] == ' ' || commande[var.i] == '\t'))
		{
			if (var.flg)
			{
				*(var.epured_string) = ' ';
				var.epured_string++;
			}
			var.flg = 0;
			*var.epured_string = commande[var.i];
			var.epured_string++;
		}
		var.i += 1;
	}
	*(var.epured_string) = '\0';
}

char	*epur_string(char *commande)
{
	t_var	var;

	data_init(&var, commande);
	while (commande[var.i] && (commande[var.i] == ' ' || commande[var.i] == '\t'))
		++var.i;
	get_new_string(commande, var);
	free(commande);
	return (var.begin);
}

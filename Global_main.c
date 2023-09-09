/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Global_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 23:58:04 by abait-ta          #+#    #+#             */
/*   Updated: 2023/09/09 12:41:55 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Header/Parsing_Header.h"

int	main(void)
{
	t_commande	commande;

	while (1)
	{
		commande.commande = readline("MINISHELL[~] -> ");
		if (commande.commande == NULL)
			return (0);
		commande.commande = epur_string(commande.commande);
		lexical_analysis(commande.commande);
	}
	return (0);
}

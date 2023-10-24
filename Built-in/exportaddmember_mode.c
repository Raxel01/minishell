/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exportaddmember_mode.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 23:00:25 by abait-ta          #+#    #+#             */
/*   Updated: 2023/10/24 12:00:34 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/Parsing.h"

void	addenvmember(t_export e, t_my_env **env)
{
	if (e.elem_value)
		add_member(env, creatdup(e.elem_name, e.elem_value));
	else
		add_member(env, creatdup(e.elem_name, NULL));
}

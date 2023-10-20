/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:17:52 by abait-ta          #+#    #+#             */
/*   Updated: 2023/10/20 15:36:58 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Header/Parsing.h"

long	ft_abs(long n)
{
	if (n < 0)
		n = n * (-1);
	return (n);
}

char	*strrev(char *str)
{
	int		i;
	int		len;
	char	temp;

	len = ft_strlen(str) - 1;
	i = 0;
	while (len > i)
	{
		temp = str[i];
		str[i] = str[len];
		str[len] = temp;
		len--;
		i++;
	}
	return (str);
}

int	get_is_negative(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

int	nb_isdigit(int n)
{
	int	digit;

	digit = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		digit++;
		n = n / 10;
	}
	return (digit);
}

char	*ft_itoa(int n)
{
	int		size;
	int		sign;
	char	*target;

	sign = get_is_negative(n);
	target = ft_calloc((nb_isdigit(n) + sign + 1), sizeof(char));
	if (!target)
		return (NULL);
	if (n == 0)
		target[0] = 48;
	size = 0;
	while (n != 0)
	{
		target[size++] = ft_abs(n % 10) + '0';
		n = n / 10;
	}
	if (sign == 1)
		target[size] = '-';
	strrev(target);
	return (target);
}

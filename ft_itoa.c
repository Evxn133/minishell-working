/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheyer <rheyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 18:18:12 by evscheid          #+#    #+#             */
/*   Updated: 2023/07/06 22:08:42 by rheyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count(long int i)
{
	int	c;

	c = 0;
	if (i < 0)
	{
		i *= -1;
		c++;
	}
	while (i > 0)
	{
		i /= 10;
		c++;
	}
	return (c);
}

char	*ft_itoa(int n)
{
	char		*s;
	int			i;

	i = count(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	s = malloc(sizeof(char) * i + 1);
	if (!s)
		return (0);
	if (n < 0)
	{
		s[0] = '-';
		n *= -1;
	}
	s[i] = '\0';
	i--;
	while (n > 0)
	{
		s[i--] = (n % 10) + '0';
		n /= 10;
	}
	return (s);
}

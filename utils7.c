/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheyer <rheyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 21:58:11 by rheyer            #+#    #+#             */
/*   Updated: 2023/07/08 20:05:04 by rheyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

bool	ft_is_separator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	else
		return (0);
}

int	ft_contains_digit(const char *str)
{
	while (*str)
	{
		if (ft_isdigit(*str))
			return (1);
		str++;
	}
	return (0);
}

int	ft_isalnum(int c)
{
	return ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'));
}

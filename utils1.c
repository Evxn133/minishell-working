/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheyer <rheyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:50:06 by rheyer            #+#    #+#             */
/*   Updated: 2023/07/09 19:42:18 by rheyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr_fd(const char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}

size_t	ft_strlen(const char *str)
{
	int	a;

	a = 0;
	while (str[a])
		a++;
	return (a);
}

int	is_option_n(char *arg)
{
	if (!arg || arg[0] != '-')
		return (0);
	arg++;
	while (*arg)
	{
		if (*arg != 'n')
			return (0);
		arg++;
	}
	return (1);
}

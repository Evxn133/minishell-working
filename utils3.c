/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheyer <rheyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 21:20:42 by rheyer            #+#    #+#             */
/*   Updated: 2023/07/06 22:13:04 by rheyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = (char *) malloc(sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[j] = s1[i];
		j++;
		i++;
	}
	i = 0;
	while (s2[i])
	{
		str[j] = s2[i];
		j++;
		i++;
	}
	str[j] = '\0';
	return (str);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((((unsigned char *)s1)[i] || ((unsigned char *)s2)[i]) && i < n)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

char	*ft_remove_char(char *str, int pose)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	dest = malloc(sizeof(char) * ft_strlen(str));
	while (str[i])
	{
		if (i == pose)
			i++;
		dest[j] = str[i];
		j++;
		i++;
	}
	dest[j] = '\0';
	return (dest);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != (char)c)
	{
		if (s[i] == '\0')
			return (NULL);
		i++;
	}
	return ((char *)s + i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	return (0);
}

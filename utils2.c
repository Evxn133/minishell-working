/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheyer <rheyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:08:31 by rheyer            #+#    #+#             */
/*   Updated: 2023/07/06 21:43:41 by rheyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char const *src, unsigned int start, size_t len)
{
	char	*dest;
	size_t	i;

	i = 0;
	if (!src)
		return (NULL);
	if (start >= ft_strlen(src))
		return (ft_strdup(""));
	if (ft_strlen(src + start) < len)
		len = ft_strlen(src + start);
	src = src + start;
	dest = (char *)malloc(len + 1);
	if (!dest)
		return (NULL);
	while (src[i] && i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[len] = '\0';
	return (dest);
}

char	*ft_strdup(const char *src)
{
	char	*dest;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(src);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

size_t	ft_split_len(const char *s, char c)
{
	unsigned int	i;
	size_t			ln;

	i = 0;
	ln = 0;
	while (s[i] == c)
		i++;
	while (s[i] != c && s[i++])
		ln++;
	return (ln);
}

size_t	ft_number_word(const char *str, char c)
{
	unsigned int	i;
	size_t			t;

	i = 0;
	t = 0;
	while (str[i])
	{
		if (str[i] != c)
			t++;
		while (str[i] != c && str[i + 1])
			i++;
		i++;
	}
	return (t);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	t;
	char	**n;

	i = 0;
	t = 0;
	n = (char **)malloc(sizeof(char *) * (ft_number_word(s, c) + 1));
	if (!n)
		return (0);
	while (i < ft_number_word(s, c))
	{
		n[i] = (char *) malloc(sizeof(char) * (ft_split_len(&s[t], c) + 1));
		if (!n[i])
			return (0);
		j = 0;
		while (s[t] == c)
			t++;
		while (s[t] != c && s[t])
			n[i][j++] = s[t++];
		n[i][j] = '\0';
		i++;
	}
	n[i] = NULL;
	return (n);
}

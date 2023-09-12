/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheyer <rheyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 21:21:56 by rheyer            #+#    #+#             */
/*   Updated: 2023/07/09 19:00:10 by rheyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env_len(t_env *lst)
{
	int	count;

	count = 0;
	while (lst != NULL)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

t_env	*ft_lstnew(void *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->value = value;
	new->next = NULL;
	return (new);
}

t_env	*ft_lstlast(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_env **alst, t_env *new)
{
	t_env	*last;

	if (!alst || !new)
		return ;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	last = ft_lstlast(*alst);
	last->next = new;
}

int	token_list_size(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens)
	{
		count++;
		tokens = tokens->next;
	}
	return (count);
}

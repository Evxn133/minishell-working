/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheyer <rheyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 21:41:18 by rheyer            #+#    #+#             */
/*   Updated: 2023/07/09 19:07:41 by rheyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_envcpy(char **envi, t_env **env, int i)
{
	int		shlvl_value;
	char	*equal_ptr;
	char	*key;
	char	*value;
	t_env	*current;

	while (envi[i])
	{
		equal_ptr = strchr(envi[i], '=');
		if (!equal_ptr)
		{
			i++;
			continue ;
		}
		key = strndup(envi[i], equal_ptr - envi[i]);
		value = strdup(equal_ptr + 1);
		if (ft_strcmp(key, "SHLVL") == 0)
		{
			shlvl_value = atoi(value);
			shlvl_value++;
			free(value);
			value = ft_itoa(shlvl_value);
		}
		if (!*env)
		{
			*env = new_env_node(key, value);
			current = *env;
		}
		else
		{
			current->next = new_env_node(key, value);
			current = current->next;
		}
		free(key);
		free(value);
		i++;
	}
}

t_env	*new_env_node(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = strdup(key);
	if (value == NULL)
		new->value = NULL;
	else
		new->value = strdup(value);
	new->next = NULL;
	return (new);
}

char	*get_env_value(t_env *env, const char *key)
{
	while (env != NULL)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

t_env	*find_last_env_node(t_env *env)
{
	if (!env)
		return (0);
	while (env->next)
		env = env->next;
	return (env);
}

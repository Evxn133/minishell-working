/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evscheid <evscheid@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 02:21:02 by evscheid          #+#    #+#             */
/*   Updated: 2023/05/10 02:21:02 by evscheid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env_node(t_env *env, char *key, char *value)
{
	t_env	*last_node;

	last_node = find_last_env_node(env);
	if (last_node)
		last_node->next = new_env_node(key, value);
}

void	update_env_value(t_env *env, char *key, char *value)
{
	while (env)
	{
		if (strcmp(env->key, key) == 0)
		{
			free(env->value);
			env->value = strdup(value);
			return ;
		}
		env = env->next;
	}
}

void	test(char *equal_ptr, char *key, char *value, char *arg)
{
	equal_ptr = strchr(arg, '=');
	if (equal_ptr)
	{
		key = strndup(arg, equal_ptr - arg);
		value = strdup(equal_ptr + 1);
	}
	else
	{
		key = ft_strdup(arg);
		value = NULL;
	}
}

int	ft_export(char *arg, t_env *env)
{
	char	*equal_ptr;
	char	*key;
	char	*value;
	
	equal_ptr = NULL;
	key = NULL;
	value = NULL;
	if (!arg || !env)
		return (1);
	test(equal_ptr, key, value, arg);
	if (ft_contains_digit(key))
	{
		printf("Erreur : La clé contient un caractère numérique : %s\n", key);
		free(key);
		free(value);
		return (1);
	}
	if (get_env_value(env, key))
		update_env_value(env, key, value);
	else
		add_env_node(env, key, value);
	free(key);
	free(value);
	return (0);
}

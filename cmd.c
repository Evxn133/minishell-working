/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheyer <rheyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:36:37 by rheyer            #+#    #+#             */
/*   Updated: 2023/07/06 23:00:44 by rheyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_env(t_env *env)
{
	if (env)
	{
		while (env)
		{
			if (env->value)
				printf("%s=%s\n", env->key, env->value);
			env = env->next;
		}
	}
}

void	copy_keys_to_array(t_env *env, char **key_array)
{
	int	i;

	i = 0;
	while (env)
	{
		key_array[i] = env->key;
		env = env->next;
		i++;
	}
}

void	sort_key_array(char **key_array, int len)
{
	int		i;
	int		j;
	char	*temp;

	i = -1;
	while (++i < len - 1)
	{
		j = i;
		while (++j < len)
		{
			if (strcmp(key_array[i], key_array[j]) > 0)
			{
				temp = key_array[i];
				key_array[i] = key_array[j];
				key_array[j] = temp;
			}
		}
	}
}

void	ft_print_export(t_env *env)
{
	int		len;
	char	**key_array;
	t_env	*temp_env;
	int		i;

	if (!env)
		return ;
	len = ft_env_len(env);
	key_array = (char **)malloc(sizeof(char *) * len);
	copy_keys_to_array(env, key_array);
	sort_key_array(key_array, len);
	i = -1;
	while (++i < len)
	{
		temp_env = env;
		while (temp_env && strcmp(temp_env->key, key_array[i]) != 0)
			temp_env = temp_env->next;
		if (temp_env && temp_env->value)
			printf("declare -x %s=\"%s\"\n", temp_env->key, temp_env->value);
		else if (temp_env)
			printf("declare -x %s\n", temp_env->key);
	}
	free(key_array);
}

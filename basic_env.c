/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_basic_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evscheid <evscheid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 23:40:53 by evscheid          #+#    #+#             */
/*   Updated: 2023/05/21 19:38:30 by evscheid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env_add(t_env **env, char *key, char *value)
{
	t_env	*new_elem;
	t_env	*tmp;	

	new_elem = (t_env *)malloc(sizeof(t_env));
	new_elem->key = strdup(key);
	new_elem->value = strdup(value);
	new_elem->next = NULL;
	if (*env == NULL)
		*env = new_elem;
	else
	{
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_elem;
	}
}

void	ft_basic_env(t_env **env)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		exit(EXIT_FAILURE);
	}
	ft_env_add(env, "PWD", cwd);
	ft_env_add(env, "SHLVL", "1");
	ft_export("OLDPWD", *env);
}

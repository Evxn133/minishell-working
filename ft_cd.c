/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheyer <rheyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 23:05:19 by evscheid          #+#    #+#             */
/*   Updated: 2023/07/06 22:25:45 by rheyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	old_pwd(t_env *env)
{
	char	*old_pwd;

	old_pwd = get_env_value(env, "OLDPWD");
	if (old_pwd != NULL)
	{
		if (chdir(old_pwd) == -1)
			perror("error: chdir");
		old_pwd = getcwd(NULL, 0);
		if (old_pwd == NULL)
			perror("error: getcwd");
		update_env_value(env, "OLDPWD", old_pwd);
		free(old_pwd);
	}
}

void	new_pwd(t_env *env)
{
	char	*env_pwd;
	char	*new_pwd;

	env_pwd = get_env_value(env, "PWD");
	if (env_pwd != NULL)
	{
		new_pwd = ft_pwd();
		update_env_value(env, "PWD", new_pwd);
		free(new_pwd);
	}
}

void	check_and_update_oldpwd(t_env *env, char *old_pwd)
{
	char	*env_old_pwd;
	char	*arg;

	env_old_pwd = get_env_value(env, "OLDPWD");
	if (env_old_pwd == NULL)
	{
		arg = ft_strjoin("OLDPWD", "=");
		env_old_pwd = ft_strjoin(arg, old_pwd);
		ft_export(env_old_pwd, env);
		free(env_old_pwd);
		free(arg);
	}
	else
		update_env_value(env, "OLDPWD", old_pwd);
}

void	check_and_update_pwd(t_env *env, char *new_pwd)
{
	char	*env_pwd;
	char	*arg;

	env_pwd = get_env_value(env, "PWD");
	if (env_pwd == NULL)
	{
		arg = ft_strjoin("PWD", "=");
		env_pwd = ft_strjoin(arg, new_pwd);
		ft_export(env_pwd, env);
		free(env_pwd);
		free(arg);
	}
	else
		update_env_value(env, "PWD", new_pwd);
}

int	ft_cd(t_token *args, t_env *env)
{
	char	*path;
	char	*old_pwd;
	char	*new_pwd;

	path = (args->next == NULL || args->next->value == NULL) ? get_env_value(env, "HOME") : args->next->value;
	old_pwd = getcwd(NULL, 0);
	if (old_pwd == NULL)
	{
		perror("getcwd error");
		return (1);
	}
	if (chdir(path) != 0)
	{
		perror("cd error");
		free(old_pwd);
		return (1);
	}
	check_and_update_oldpwd(env, old_pwd);
	free(old_pwd);
	new_pwd = getcwd(NULL, 0);
	if (new_pwd == NULL)
	{
		perror("getcwd error");
		return (1);
	}
	check_and_update_pwd(env, new_pwd);
	free(new_pwd);
	return (0);
}

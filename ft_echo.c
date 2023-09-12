/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evscheid <evscheid@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 02:59:03 by evscheid          #+#    #+#             */
/*   Updated: 2023/05/10 02:59:03 by evscheid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_quotes(char *arg, int quote_type)
{
	if (*arg == '\'' && quote_type != 2)
	{
		if (quote_type == 1)
			quote_type = 0;
		else
			quote_type = 1;
	}
	else if (*arg == '\"' && quote_type != 1)
	{
		if (quote_type == 2)
			quote_type = 0;
		else
			quote_type = 2;
	}
	return (quote_type);
}

char	*get_var_name(char **arg)
{
	char	*start;
	char	*var_name;
	int		len;

	start = *arg;
	len = 0;
	while (ft_isalnum(**arg) || **arg == '_')
	{
		(*arg)++;
		len++;
	}
	var_name = malloc(len + 1);
	strncpy(var_name, start, len);
	var_name[len] = '\0';
	return (var_name);
}

void	handle_dollar(char **arg, t_env *env)
{
	char	*var_name;
	char	*var_value;

	(*arg)++;
	if (ft_isalnum(**arg) || **arg == '_')
	{
		var_name = get_var_name(arg);
		var_value = get_env_value(env, var_name);
		if (var_value)
			ft_putstr_fd(var_value, STDOUT_FILENO);
		free(var_name);
	}
	else
	{
		write(STDOUT_FILENO, "$", 1);
		(*arg)--;
	}
}

void	ft_echo_arg(char *arg, t_env *env)
{
	int	quote_type;

	quote_type = 0;
	while (*arg)
	{
		quote_type = handle_quotes(arg, quote_type);
		if (*arg == '\\' && (*(arg + 1) == '\"' || *(arg + 1) == '\''))
			arg++;
		else if (*arg == '$' && quote_type != 1)
			handle_dollar(&arg, env);
		else
			write(STDOUT_FILENO, arg, 1);
		arg++;
	}
}

void	ft_echo(t_token *args, t_env *env)
{
	int		option_n;
	t_token	*current;

	current = args->next;
	option_n = 0;
	while (current && is_option_n(current->value))
	{
		option_n = 1;
		current = current->next;
	}
	while (current)
	{
		ft_echo_arg(current->value, env);
		if (current->next)
			ft_putstr_fd(" ", STDOUT_FILENO);
		current = current->next;
	}
	if (!option_n)
		ft_putstr_fd("\n", STDOUT_FILENO);
	else
		ft_putstr_fd("", STDOUT_FILENO);
}

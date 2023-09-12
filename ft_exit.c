/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheyer <rheyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:31:23 by evscheid          #+#    #+#             */
/*   Updated: 2023/07/06 22:20:17 by rheyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_error(t_token *tokens, char *endptr)
{
	if (tokens->next->next)
	{
		printf("exit: too many arguments\n");
		exit(255);
	}
	else if (*endptr != '\0')
	{
		printf("exit: %s: numeric argument required\n", tokens->next->value);
		exit(255);
	}
}

void	ft_exit(t_token *tokens, t_env *env)
{
	int			exit_code;
	long int	tmp;
	char		*endptr;

	exit_code = 0;
	if (tokens->next)
	{
		tmp = strtol(tokens->next->value, &endptr, 10);
		if (tokens->next->next || *endptr != '\0'
			|| tmp < INT_MIN || tmp > INT_MAX)
		{
			ft_exit_error(tokens, endptr);
			return ;
		}
		exit_code = (int)tmp;
	}
	(void)env;
	exit(exit_code);
}

/*
	"ERANGE"
	Si l'une de ces conditions est vraie,
	on définit errno à ERANGE si la valeur est hors limites et on utilise perror
	pour afficher un message d'erreur. 
	Ensuite, on retourne sans quitter le programme.
*/

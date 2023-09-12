/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheyer <rheyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:53:30 by rheyer            #+#    #+#             */
/*   Updated: 2023/07/07 21:10:40 by rheyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	ft_new_line(void)
{
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("\033[1;32mminishell\033[0m", 1);
	ft_putstr_fd(" > ", 1);
}*/

void	ft_print_token(t_token *env)
{
	if (env)
	{
		while (env)
		{
			printf("TOKEN_TYPE = %u = %s\n", env->type, env->value);
			env = env->next;
		}
	}
}

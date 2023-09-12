/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheyer <rheyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:17:15 by rheyer            #+#    #+#             */
/*   Updated: 2023/07/09 19:26:00 by rheyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_list_clear(t_token **tokens)
{
	t_token	*tmp;

	while (*tokens)
	{
		tmp = (*tokens)->next;
		free((*tokens)->value);
		free(*tokens);
		*tokens = tmp;
	}
}

void	ft_minishell(t_token *tokens, t_env *env)
{
	char	*input;
	int		fd_in_saved;
	int		fd_out_saved;

	fd_in_saved = dup(STDIN_FILENO);
	fd_out_saved = dup(STDOUT_FILENO);
	while (42)
	{
		input = readline("$> ");
		if (!input)
		{
			printf("exit\n");
			exit (0);
		}
		tokens = lexer(input);
		if (tokens)
			ft_pipex(tokens, env, ft_is_pipe(tokens), dup(STDIN_FILENO));
		token_list_clear(&tokens);
		add_history(input);
		dup2(fd_in_saved, STDIN_FILENO);
		dup2(fd_out_saved, STDOUT_FILENO);
		free(input);
	}
}

int	main(int argc, char **argv, char **envi)
{
	t_token	*tokens;
	t_env	*env;

	tokens = NULL;
	env = NULL;
	(void)argc;
	(void)argv;
	handle_signal();
	if (!envi[0])
		ft_basic_env(&env);
	else if (envi)
		ft_envcpy(envi, &env, 0);
	printf("Bienvenue sur le mini_sel\n");
	ft_minishell(tokens, env);
	return (0);
}

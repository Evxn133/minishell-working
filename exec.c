/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheyer <rheyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 20:36:20 by rheyer            #+#    #+#             */
/*   Updated: 2023/07/09 20:23:37 by rheyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_bultin(t_token *tokens)
{
	if (!ft_strncmp(tokens->value, "pwd", 4))
		return (1);
	else if (!ft_strncmp(tokens->value, "env", 4))
		return (1);
	else if (!ft_strncmp(tokens->value, "cd", 3))
		return (1);
	else if (!ft_strncmp(tokens->value, "export", 7) && (!tokens->next
			|| (tokens->next && tokens->next->type != WORD)))
		return (1);
	else if (!ft_strncmp(tokens->value, "export", 7))
		return (1);
	else if (!ft_strncmp(tokens->value, "unset", 6))
		return (1);
	else if (!ft_strncmp(tokens->value, "echo", 5))
		return (1);
	else if (!ft_strncmp(tokens->value, "exit", 5))
		return (1);
	return (0);
}

void	ft_bultin(t_token *tokens, t_env *env)
{
	if (!ft_strncmp(tokens->value, "pwd", 4))
		ft_pwd();
	else if (!ft_strncmp(tokens->value, "env", 4))
		ft_print_env(env);
	else if (!ft_strncmp(tokens->value, "cd", 3))
		ft_cd(tokens, env);
	else if (!ft_strncmp(tokens->value, "export", 7) && (!tokens->next
			|| (tokens->next && tokens->next->type != WORD)))
		ft_print_export(env);
	else if (!ft_strncmp(tokens->value, "export", 7))
		ft_export(tokens->next ? tokens->next->value : NULL, env);
	else if (!ft_strncmp(tokens->value, "unset", 6))
		ft_unset(tokens->next ? tokens->next->value : NULL, env);
	else if (!ft_strncmp(tokens->value, "echo", 5))
		ft_echo(tokens, env);
	else if (!ft_strncmp(tokens->value, "exit", 5))
		ft_exit(tokens, env);
}

t_token	*ft_remove_tokens(t_token *tokens)
{
	t_token	*first;
	t_token	*tmp;

	first = tokens;
	while ((tokens->type == REDIRECTOR_OUT
			|| tokens->type == REDIRECTOR_IN
			|| tokens->type == REDIRECTOR_DOUBLE_IN
			|| tokens->type == REDIRECTOR_DOUBLE_OUT)
		&& tokens->next
		&& tokens->next->type != PIPE)
	{
		tmp = tokens->next->next;
		free(tokens->next->value);
		free(tokens->next);
		free(tokens->value);
		free(tokens);
		tokens = tmp;
		first = tokens;
	}
	while (tokens->next && tokens->type != PIPE)
	{
		if ((tokens->next->type == REDIRECTOR_OUT
				|| tokens->next->type == REDIRECTOR_IN
				|| tokens->next->type == REDIRECTOR_DOUBLE_IN
				|| tokens->next->type == REDIRECTOR_DOUBLE_OUT)
			&& tokens->next->next
			&& tokens->next->next->type != PIPE)
		{
			tmp = tokens->next->next->next;
			free(tokens->next->next->value);
			free(tokens->next->next);
			free(tokens->next->value);
			free(tokens->next);
			tokens->next = tmp;
		}
		else
			tokens = tokens->next;
	}
	return first;
}

void	child(t_token *tokens, t_env *env, int output, int input)
{
	char	**paths;
	char	*path_env;

	ft_redirect(tokens, output, input);
	tokens = ft_remove_tokens(tokens);
	//printf("exec\n");
	//ft_print_token(tokens);
	path_env = get_env_value(env, "PATH");
	if (!path_env)
	{
		ft_error(tokens->value, "command not found");
		return ;
	}
	path_env = ft_strdup(path_env);
	paths = ft_split(path_env, ':');
	if (ft_is_bultin(tokens))
		ft_bultin(tokens, env);
	else
		exec_child_process(tokens, env, paths);
	free(path_env);
	free_char_arr(paths);
	exit(0);
}

void	ft_pipex(t_token *tokens, t_env *env, int n, int input)
{ 
	int		pipefd[2];
	pid_t	pid;
	int		status;

	if (pipe(pipefd) == -1)
	{
		perror("pipe failed");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		close(pipefd[0]);
		if (n > 0)
			child(tokens, env, pipefd[1], input);
		else
			child(tokens, env, dup(STDOUT_FILENO), input);
	}
	else
	{
		close(pipefd[1]);
		if (n > 0)
		{
			while (tokens->type != PIPE && n > 0)
				tokens = tokens->next;
			tokens = tokens->next;
		}
		close(input);
		if (n > 0)
		{
			input = dup(pipefd[0]);
			close(pipefd[0]);
			ft_pipex(tokens, env, --n, input);
		}
		else
			close(pipefd[0]);
		waitpid(pid, &status, 0);
	}
}

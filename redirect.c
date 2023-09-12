/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheyer <rheyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 20:21:54 by rheyer            #+#    #+#             */
/*   Updated: 2023/07/09 20:31:27 by rheyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redirect(t_token *tokens, int output, int input)
{
	int	fd_out;
	int	fd_in;

	fd_out = 0;
	fd_in = 0;
	if (!ft_is_input(tokens) && dup2(input, STDIN_FILENO) == -1)
	{
		perror("dup2 failed");
		exit(EXIT_FAILURE);
	}
	if (!ft_is_output(tokens) && ft_is_pipe(tokens)
		&& dup2(output, STDOUT_FILENO) == -1)
	{
		perror("dup2 failed");
		exit(EXIT_FAILURE);
	}
	while (tokens->next && tokens->type != PIPE)
	{
		if (tokens->type == REDIRECTOR_OUT)
			fd_out = ft_redirect_out(tokens, fd_out);
		if (tokens->type == REDIRECTOR_DOUBLE_OUT)
			fd_out = ft_redirect_double_out(tokens, fd_out);
		if (tokens->type == REDIRECTOR_IN)
			fd_in = ft_redirect_in(tokens, fd_in);
		tokens = tokens->next;
	}
	ft_redirect_bis(input, output, fd_in, fd_out);
}

void	ft_redirect_bis(int input, int output, int fd_in, int fd_out)
{
	if (fd_out)
	{
		if (dup2(fd_out, STDOUT_FILENO) == -1)
		{
			perror("dup2 failed");
			exit(EXIT_FAILURE);
		}
		close(fd_out);
	}
	if (fd_in)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
		{
			perror("dup2 failed");
			exit(EXIT_FAILURE);
		}
		close(fd_in);
	}
	close(input);
	close(output);
}

int	ft_redirect_out(t_token *tokens, int fd_out)
{
	if (fd_out)
		close(fd_out);
	fd_out = open(tokens->next->value,
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		perror("open failed");
		exit(EXIT_FAILURE);
	}
	return (fd_out);
}

int	ft_redirect_in(t_token *tokens, int fd_in)
{
	if (fd_in)
		close(fd_in);
	fd_in = open(tokens->next->value, O_RDONLY);
	if (fd_in == -1)
	{
		perror("open failed");
		exit(EXIT_FAILURE);
	}
	return (fd_in);
}

int	ft_redirect_double_out(t_token *tokens, int fd_out)
{
	if (fd_out)
		close(fd_out);
	fd_out = open(tokens->next->value,
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_out == -1)
	{
		perror("open failed");
		exit(EXIT_FAILURE);
	}
	return (fd_out);
}

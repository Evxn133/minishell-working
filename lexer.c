/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheyer <rheyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 23:18:06 by evscheid          #+#    #+#             */
/*   Updated: 2023/07/09 18:51:08 by rheyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token(t_token **tokens, char *value, t_token_type type)
{
	t_token	*new_token;
	t_token	*tmp;

	new_token = (t_token *)malloc(sizeof(t_token));
	new_token->value = value;
	new_token->type = type;
	new_token->next = NULL;
	if (*tokens == NULL)
		*tokens = new_token;
	else
	{
		tmp = *tokens;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_token;
	}
}

void	add_separator_token(t_token **tokens, char *input, int *i)
{
	t_token_type	type;
	int				size;

	type = 0;
	size = 1;
	if (input[*i] == '|' && input[*i - 1] && input[*i - 1] != '>')
		type = PIPE;
	else if (input[*i] == '<' && input[*i + 1] && input[*i + 1] == '<')
	{
		type = REDIRECTOR_DOUBLE_IN;
		size = 2;
		*i = *i + 1;
	}
	else if (input[*i] == '<')
		type = REDIRECTOR_IN;
	else if (input[*i] == '>' && input[*i + 1] && input[*i + 1] == '>')
	{
		type = REDIRECTOR_DOUBLE_OUT;
		size = 2;
		*i = *i + 1;
	}
	else if (input[*i] == '>')
		type = REDIRECTOR_OUT;
	if (type)
		add_token(tokens, strndup(input + *i - (size - 1), size), type);
}

t_token	*lexer(char *input)
{
	bool		in_single_quote;
	bool		in_double_quote;
	int			i;
	int			start;
	t_token		*tokens;

	in_single_quote = false;
	in_double_quote = false;
	i = 0;
	start = 0;
	tokens = NULL;
	while (input[i])
	{
		if (input[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (input[i] == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		if (!in_single_quote && !in_double_quote
			&& (ft_is_separator(input[i]) || ft_isspace(input[i])))
		{
			if (i > start)
				add_token(&tokens,
					strndup(input + start, i - start), WORD);
			if (ft_is_separator(input[i]))
				add_separator_token(&tokens, input, &i);
			start = i + 1;
		}
		i++;
	}
	if (i > start)
		add_token(&tokens, strndup(input + start, i - start), WORD);
	return (tokens);
}

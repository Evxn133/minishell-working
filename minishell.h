/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheyer <rheyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:26:59 by rheyer            #+#    #+#             */
/*   Updated: 2023/07/09 20:30:35 by rheyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/stat.h>

/*   liste chainée env   */ 

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_command
{
	char				**args;
	char				*stdin_file;
	char				*stdout_file;
	char				*stderr_file;
	struct s_command	*next;
}	t_command;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIRECTOR_IN,
	REDIRECTOR_DOUBLE_IN,
	REDIRECTOR_OUT,
	REDIRECTOR_DOUBLE_OUT,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

/*   readline   */
int			rl_on_new_line(void);
void		rl_replace_line(const char *text, int clear_undo);
void		rl_redisplay(void);

//ft_itoa
int			count(long int i);
char		*ft_itoa(int n);

/*============================================================================*/

/*   ft_echo   */
int			handle_quotes(char *arg, int quote_type);
char		*get_var_name(char **arg);
void		handle_dollar(char **arg, t_env *env);
void		ft_echo_arg(char *arg, t_env *env);
void		ft_echo(t_token *args, t_env *env);

/*   ft_pwd   */
char		*ft_pwd(void);

/*   ft_cd   */
void		old_pwd(t_env *env);
void		new_pwd(t_env *env);
void		check_and_update_oldpwd(t_env *env, char *old_pwd);
void		check_and_update_pwd(t_env *env, char *new_pwd);
int			ft_cd(t_token *args, t_env *env);

/*   ft_export   */
t_env		*find_last_env_node(t_env *env);
void		add_env_node(t_env *env, char *key, char *value);
void		update_env_value(t_env *env, char *key, char *value);
int			ft_export(char *arg, t_env *env);

/*   ft_exit   */
void		ft_exit_error(t_token *tokens, char *endptr);
void		ft_exit(t_token *tokens, t_env *env);

/*   ft_unset   */
void		delete_env_node(t_env **env, t_env *prev, t_env *current);
void		ft_unset(char *arg, t_env *env);

/*   lexer   */
void		add_token(t_token **tokens, char *value, t_token_type type);
void		add_separator_token(t_token **tokens, char *input, int *i);
t_token		*lexer(char *input);

/*   signaux   */
void		reseption(int signal);
void		handle_signal(void);

/*   basic env   */
void		ft_env_add(t_env **env, char *key, char *value);
void		ft_basic_env(t_env **env);

/*   command   */
void		ft_print_token(t_token *env);

/*   cmd   */
void		ft_print_env(t_env *env_list);
void		copy_keys_to_array(t_env *env, char **key_array);
void		sort_key_array(char **key_array, int len);
void		ft_print_export(t_env *env);

/*   exec   */
int			ft_is_bultin(t_token *tokens);
void		ft_bultin(t_token *tokens, t_env *env);
t_token		*ft_remove_tokens(t_token *tokens);
void		child(t_token *tokens, t_env *env, int output, int input);
void		ft_pipex(t_token *tokens, t_env *env, int n, int input);

/*   redirect   */
void		ft_redirect(t_token *tokens, int output, int input);
void		ft_redirect_bis(int input, int output, int fd_in, int fd_out);
int			ft_redirect_out(t_token *tokens, int fd_out);
int			ft_redirect_in(t_token *tokens, int fd_in);
int			ft_redirect_double_out(t_token *tokens, int fd_out);

/*   execve   */
char		**ft_env_lst_to_char_arr(t_env *env);
void		free_char_arr(char **arr);
char		*get_command_path(char *path, char *token);
char		**token_list_to_char_arr(t_token *tokens);
void		exec_child_process(t_token *tokens, t_env *env, char **paths);
int			ft_exec(t_token *tokens, t_env *env);

/*   utils1   */
void		ft_putstr_fd(const char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
size_t		ft_strlen(const char *str);
int			is_option_n(char *arg);

/*   utils2   */
char		*ft_substr(char const *src, unsigned int start, size_t len);
char		*ft_strdup(const char *src);
size_t		ft_split_len(const char *s, char c);
size_t		ft_number_word(const char *str, char c);
char		**ft_split(const char *str, char c);

/*   utils3   */
char		*ft_strjoin(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_remove_char(char *str, int pose);
char		*ft_strchr(const char *s, int c);
int			ft_strcmp(const char *s1, const char *s2);

/*   utils4   */
int			ft_env_len(t_env *lst);
t_env		*ft_lstnew(void *value);
t_env		*ft_lstlast(t_env *lst);
void		ft_lstadd_back(t_env **alst, t_env *new);
int			token_list_size(t_token *tokens);

/*   utils5   */
void		ft_envcpy(char **envi, t_env **env, int i);
t_env		*new_env_node(char *key, char *value);
char		*get_env_value(t_env *env, const char *key);
t_env		*find_last_env_node(t_env *env);

/*   utils6   */
void		ft_error(char *cmd, char *error);
int			ft_is_(t_token *tokens);
int			ft_is_pipe(t_token *tokens);
int			ft_is_input(t_token *tokens);
int			ft_is_output(t_token *tokens);

/*   utils7   */
bool		ft_isspace(int c);
bool		ft_is_separator(char c);
int			ft_isdigit(int c);
int			ft_contains_digit(const char *str);
int			ft_isalnum(int c);

#endif
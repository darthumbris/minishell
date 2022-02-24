/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_expansion.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/07 12:53:52 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/24 12:35:59 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "minishell.h"

/*
 * This function returns the expanded string with
 * the env variable that is expanded to its value.
 * (needs to be properly freed afterwards).
 */
static char	*normal_env_variable(char *input, char **envp, int len)
{
	char	*env_str;
	char	*env_expand;
	char	*remain;
	int		i;

	i = 0;
	while (ft_isalnum(input[i]))
		i++;
	env_str = ft_substr(input, 0, i);
	if (!ft_getenv(env_str, envp))
	{
		env_expand = ft_substr(input, ft_strlen(env_str), len);
		free(env_str);
		return (env_expand);
	}
	remain = ft_substr(input, ft_strlen(env_str), len);
	env_expand = ft_strjoin(ft_getenv(env_str, envp), remain);
	free(remain);
	free(env_str);
	return (env_expand);
}

/*
 * This function will expand the $ stuff 
 * $? $0 and $PWD (and other env variables)
 * are covered with this function.
 * the returned string should be freed properly.!
 * !!!!return value still needs to be done. !!!!!
 */
char	*expand_env_variable(char *input, char **envp)
{
	char	*env_expand;
	char	*remain;
	char	*return_str;

	if (input && *input)
	{
		if (*input == '0')
		{
			remain = ft_substr(input, 1, ft_strlen(input));
			env_expand = ft_strjoin("minishell", remain);
		}
		else if (*input == '?')
		{
			remain = ft_substr(input, 1, ft_strlen(input));
			return_str = envp[0];
			env_expand = ft_strjoin(return_str, remain);
		}
		else
			return (normal_env_variable(input, envp, ft_strlen(input)));
		free(remain);
		return (env_expand);
	}
	return_str = ft_strdup("$");
	return (return_str);
}

static void	free_strjoin_str(char *begin, char *env_expand)
{
	free(begin);
	free(env_expand);
}

static bool	is_heredoc(t_token *lst)
{
	while (lst)
	{
		if (!ft_strcmp(lst->token_name, "<"))
			return (true);
		lst = lst->next;
	}
	return (false);
}

/*
 * this function will check the string
 * for a $ and see if it needs expanding.
 * and then will expand it. 
 * (for heredoc delimiter if won't expand)
 */
void	check_for_env_expansion(char **str, char **envp, t_token *lst)
{
	size_t	i;
	char	*begin;
	char	*env_expand;
	bool	quote;

	i = 0;
	quote = false;
	while ((*str)[i])
	{
		if ((*str)[i] == '\"')
			quote = !quote;
		if ((*str)[i] == '$')
		{
			begin = ft_substr(*str, 0, i);
			if (is_heredoc(lst))
				env_expand = ft_strdup(*str);
			else
				env_expand = expand_env_variable(*str + i + 1, envp);
			free(*str);
			(*str) = ft_strjoin(begin, env_expand);
			free_strjoin_str(begin, env_expand);
			if (ft_strlen((*str)) == 0)
				break ;
		}
		if ((*str)[i] == '\'' && !quote)
			i = move_through_quotes(*str, i);
		i++;
	}
}

#include <stdio.h>
#include "includes/libft.h"

char	*expand_env_variable(char *input);

char	*double_quotes_string(char *input)
{
	int		len;
	char	*before_env_expand;
	char	*after_env_expand;

	len = ft_strchr(input + 1, '\"') - (input + 1);
	before_env_expand = ft_substr(input, 1, len);
	input += ft_strlen(before_env_expand);
	after_env_expand = expand_env_variable(before_env_expand);
	free(before_env_expand);
	return (after_env_expand);
}

char	*single_quotes_string(char *input)
{
	int	len;

	len = ft_strchr(input + 1, '\'') - (input + 1);
	return (ft_substr(input, 1, len));
}

int	get_env_name_len(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '?')
		return (1);
	while (str[i] && (ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

/*
 * not sure yet how to handle when there are multiple 
 * $ in the string.
 */
char	*expand_env_variable(char *input)
{
	int		i;
	char	*env_name;
	char	*env_value;
	int		env_pos;
	char	**env_split;

	printf("input: %s\n", input);
	env_split = ft_split(ft_strchr(input, '$'), '$');
	i = 0;
	while (env_split[i])
	{
		printf("%s\n", env_split[i]);
		env_name = ft_substr(env_split[i], 0, get_env_name_len(env_split[i]));
		printf("env name: %s\n", env_name);
		i++;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	int	i;
	int	expand_flag;
	int	len;
	char	*input = " testing $USER  waht\"hello  two$USER\" \'what is $USER\'happening";
	int	input_len;

	// i = 0;
	// expand_flag = 0;
	// len = 0;
	// input_len = ft_strlen(input);
	// while (i < input_len && input[i] && i >= 0)
	// {
	// 	while (input[i] == ' ' && input[i])
	// 			i++;
	// 	if (input[i] == '\"')
	// 		expand_flag = 1;
	// 	else if (input[i] == '\'')
	// 		expand_flag = 2;
	// 	if (expand_flag == 0) // normal tokenizing
	// 	{
	// 		//do convert here before doing the substr.
	// 		if (((ft_strchr(input + i, ' ') - (input + i)) < (ft_strchr(input + i, '\"') - (input + i))) && ft_strchr(input + i, '\"'))
	// 			len = ft_strchr(input + i, '\"') - (input + i); // in this case have to do some extra stuff to combine the things (strjoin with this len and than the string in the quotes stuff....)
	// 		else
	// 			len = ft_strchr(input + i, ' ') - (input + i) + 1;
	// 		if (len < 0)
	// 			len = input_len - i;
	// 		printf("exp=0: %s\n", ft_substr(input, i, len));
	// 		i += len;
	// 	}
	// 	else if (expand_flag == 1)//quote tokenizing 
	// 	{
	// 		//do convert here before doing the substr.
	// 		printf("%s\n", double_quotes_string(input + i));
	// 		i += ft_strlen(double_quotes_string(input + i)) + 2;
	// 		expand_flag = 0;
	// 	}
	// 	else if (expand_flag == 2)//quote tokenizing 
	// 	{
	// 		printf("%s\n", single_quotes_string(input + i));
	// 		i += ft_strlen(single_quotes_string(input + i)) + 2;
	// 		expand_flag = 0;
	// 	}
	// 	if (i <= 0 || i > input_len)
	// 		break ;
	// }
	// printf("\n\nexpected: \ntesting\nshoogenb\nwahthello  twoshoogenb\nwhat is $USERhappening\n---------\n");
	// printf("which is 5 arguments\n");
	expand_env_variable("ok $USER what$USER \'$USER\' what$? is this");
}
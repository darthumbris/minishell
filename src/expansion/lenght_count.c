/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lenght_count.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: abba <abba@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/07 12:47:36 by abba          #+#    #+#                 */
/*   Updated: 2022/02/08 10:48:05 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	len_until_char(char *str, int i, char c)
{
	int	len;

	len = 0;
	while (str[i] != c && str[i])
	{
		len++;
		i++;
	}
	return (len);
}

int	len_until_quote(char *str, int i)
{
	int	len;

	len = 0;
	while (str[i] && str[i] != '\'' )
	{
		if (str[i] == '"')
			break ;
		len++;
		i++;
	}
	return (len);
}

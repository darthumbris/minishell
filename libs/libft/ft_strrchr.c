/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 16:07:24 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/01/17 16:07:45 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*rev;

	rev = (char *)s;
	while (*rev)
		rev++;
	while (c > 256)
		c -= 256;
	while (rev >= s)
	{
		if (*rev == c)
			return (rev);
		rev--;
	}
	if (c == '\0')
		return (rev);
	return (0);
}

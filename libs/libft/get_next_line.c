/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 16:07:33 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/01/17 16:07:45 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Function: ft_strjoin
 * --------------------
 * This function add the buffer to the remainder
 * using ft_calloc to allocate the correct
 * amount of memory and also to null terminate
 * the joined string.
 * It also frees the remainder.
 * the buffer might be needed after this so this
 * gets freed later.
 */
static char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char	*ret;
	size_t	i;
	size_t	j;

	if (!s2)
		return (NULL);
	if (!s1)
		i = 0;
	else
		i = ft_strlen(s1);
	j = ft_strlen(s2);
	ret = ft_calloc(i + j + 1, 1);
	if (!ret)
		return (NULL);
	ft_memcpy(ret, s1, i);
	ft_memcpy(ret + i, s2, j + 1);
	return (ret);
}

static char	*rem_line(char **saved)
{
	size_t	end;
	char	*ret;
	char	*temp;

	if (!*saved)
		return (ft_substr("", 0, 0));
	if (ft_strchr(*saved, '\n'))
		end = ft_strchr(*saved, '\n') - *saved + 1;
	else
		end = (size_t) - 1;
	ret = ft_substr(*saved, 0, end);
	if (end != (size_t) - 1)
		temp = ft_substr(*saved, end, (size_t) - 1);
	else
		temp = NULL;
	free(*saved);
	*saved = temp;
	return (ret);
}

static char	*get_line(char **remain)
{
	char	*line;

	line = rem_line(&*remain);
	if (ft_strlen(line))
		return (line);
	free(line);
	if (*remain)
		free(remain);
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*buff;
	int			btrd;
	static char	*remain;
	char		*temp;

	btrd = 1;
	while ((!remain || !ft_strchr(remain, '\n')) && btrd)
	{
		buff = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
		btrd = read(fd, buff, BUFFER_SIZE);
		if (btrd > 0)
		{
			temp = ft_strjoin_gnl(remain, buff);
			free(remain);
			remain = temp;
		}
		free(buff);
		if (btrd == -1)
			return (NULL);
	}
	return (get_line(&remain));
}

// static char	*rem_line(char **remain)
// {
// 	size_t	end;
// 	char	*ret;
// 	char	*temp;

// 	if (!*remain)
// 		return (ft_substr("", 0, 0));
// 	if (ft_strchr(*remain, '\n'))
// 		end = ft_strchr(*remain, '\n') - *remain;
// 	else
// 		end = (size_t) - 1;
// 	ret = ft_substr(*remain, 0, end);
// 	if (end != (size_t) - 1)
// 		temp = ft_substr(*remain, end + 1, (size_t) - 1);
// 	else
// 		temp = NULL;
// 	free(*remain);
// 	*remain = temp;
// 	return (ret);
// }

// /*
//  * Function: ft_strjoingnl
//  * --------------------
//  * This is a changed strjoin
//  * so that it the s1 can be NULL
//  * and it still works
//  */
// static char	*ft_strjoingnl(char const *s1, char const *s2)
// {
// 	char	*ret;
// 	size_t	i;
// 	size_t	j;

// 	if (!s2)
// 		return (NULL);
// 	if (!s1)
// 		i = 0;
// 	else
// 		i = ft_strlen(s1);
// 	j = ft_strlen(s2);
// 	ret = malloc(i + j + 1);
// 	if (!ret)
// 		return (NULL);
// 	ft_memcpy(ret, s1, i);
// 	ft_memcpy(ret + i, s2, j + 1);
// 	return (ret);
// }

// static t_64i	ft_set64(t_64i *a, t_64i b)
// {
// 	*a = b;
// 	return (b);
// }

// static int	get_line(int fd, char **remain, char **line)
// {
// 	char	*buff;
// 	char	*temp;
// 	t_64i	aux;

// 	aux = 1;
// 	while ((!remain[fd] || !ft_strchr(remain[fd], '\n')) && aux)
// 	{
// 		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
// 		if (ft_set64((int64_t *)&aux, (int64_t)read(fd, buff, BUFFER_SIZE)) > 0)
// 		{
// 			buff[aux] = '\0';
// 			temp = ft_strjoingnl(remain[fd], buff);
// 			free(remain[fd]);
// 			remain[fd] = temp;
// 		}
// 		else if (aux == -1)
// 		{
// 			free(buff);
// 			*line = NULL;
// 			return (NULL);
// 		}
// 		free(buff);
// 	}
// 	*line = rem_line(&(remain[fd]));
// 	return ((remain[fd] && ft_strlen(remain[fd]) != 0) || aux);
// }

// char	*get_next_line(int fd)
// {
// 	static char	*remain[4096];
// 	char		*line;

// 	ft_putendl_fd("ok", 1);
// 	if (fd < 0 || fd == 1 || fd == 2 || fd >= 4096)
// 		return (NULL);
// 	if (get_line(fd, remain, &line))
// 		return (line);
// 	free(line);
// 	return (NULL);
// 	//return (get_line(fd, remain, &line));
// }

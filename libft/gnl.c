/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhamass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:18:31 by akhamass          #+#    #+#             */
/*   Updated: 2024/09/01 21:18:34 by akhamass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_stradd(char *str, char buff)
{
	int		i;
	char	*ret;
	int		len;

	i = 0;
	len = 0;
	if (str != NULL)
	{
		len = ft_strlen(str);
	}
	ret = (char *)malloc(sizeof(char) * (len + 2));
	if (ret == NULL)
		return (NULL);
	while (str && str[i])
	{
		ret[i] = str[i];
		i++;
	}
	if (str)
		free(str);
	ret[i++] = buff;
	ret[i] = '\0';
	return (ret);
}

int	gnl(int fd, char **str)
{
	char			buff;
	int				ret;

	*str = NULL;
	ret = read(fd, &buff, 1);
	while (ret > 0)
	{
		*str = ft_stradd(*str, buff);
		if (*str == NULL)
			return (-1);
		if (buff == '\n')
			return (ret);
		else
			ret += 1;
		ret = read(fd, &buff, 1);
	}
	if (ret == 0)
	{
		free(*str);
		*str = NULL;
	}
	return (ret);
}

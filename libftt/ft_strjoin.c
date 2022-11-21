/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaines <ibaines@student.42.urduli>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 19:06:25 by ibaines           #+#    #+#             */
/*   Updated: 2021/11/30 11:59:38 by ibaines          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_swap(char *s1, char *s2);

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr1;
	int		i;
	size_t	size;

	if (!s1 || !s2)
		return (NULL);
	size = 0;
	size = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	ptr1 = (char *) \
		ft_calloc(ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1, 1);
	if (!ptr1)
		return (NULL);
	ft_swap((char *)s1, ptr1);
	ft_swap((char *)s2, ptr1);
	ptr1[size] = '\0';
	return (ptr1);
}

static void	ft_swap(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s2[i])
		i++;
	while (s1[j])
	{
		s2[j + i] = s1[j];
		j++;
	}
}

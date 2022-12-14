/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaines <ibaines@student.42.urduli>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:20:38 by ibaines           #+#    #+#             */
/*   Updated: 2021/11/30 11:59:09 by ibaines          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	int		i;
	size_t	ptrs1;

	i = 0;
	ptrs1 = ft_strlen((char *)s1);
	ptr = (char *)malloc(ptrs1 + 1);
	if (!ptr)
		return (NULL);
	while (i < (int)ptrs1)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return ((char *)ptr);
}

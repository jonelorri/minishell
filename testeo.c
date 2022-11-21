/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testeo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaines <ibaines@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:14:39 by ibaines           #+#    #+#             */
/*   Updated: 2022/11/19 18:46:39 by ibaines          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

/*int close_mini(void)
{
	rl_clear_history()
	return(-1);
}*/

int checker(char *src)
{
	if (!ft_strncmp(src, "exit", 4))
		exit (-1);
	else
		return (0);
}
/*
int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	
}
*/
int	main(void)
{
	const char	*src;
	char		*ptr;

	src = "Minishell>";
	while (1)
	{
	ptr = readline(src);
	checker(ptr);
	if (ft_strlen(ptr))
		add_history(ptr);
	printf("%s\n",  ptr);
	free(ptr);
	}
	return (0);
}

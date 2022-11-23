/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testeo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaines <ibaines@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:14:39 by ibaines           #+#    #+#             */
/*   Updated: 2022/11/22 19:50:03 by ibaines          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
#include <string.h>
#define BOLD	"\001\033[1m\002"
#define CLOSE	"\001\033[0m\002"


#include <stdlib.h>

static int	ft_len_ptr(char *s, char c)
{
	int	i;
	int	len;
	int	ptr;

	len = 0;
	i = 0;
	ptr = 0;
	if (c == '\0' && s[0] == '\0')
		return (0);
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i] != '\0')
		{
			len++;
			i++;
		}
		if (len > 0)
		{
			ptr++;
			len = 0;
		}
	}
	return (ptr);
}

static int	ft_res_word(char *s, int len, int i, char **ptr)
{
	char	*wptr;

	len++;
	wptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!wptr)
		return (-1);
	wptr[len] = '\0';
	wptr[len - 1] = '/';
	len = len - 2;
	while (len >= 0)
	{
		wptr[len] = s[len + i];
		len--;
	}
	*ptr = wptr;
	return (0);
}

static int	ft_get_word(char *s, char c, char **ptr, int ptrlen)
{
	int	i;
	int	j;
	int	k;
	int	len;

	i = 0;
	j = 0;
	k = 0;
	len = 0;
	while (s[i] == c)
		i++;
	j = i;
	while (s[i] != c && s[i] != '\0')
	{
		len++;
		i++;
	}
	if (len > 0)
	{
		if (ft_res_word(s, len, j, ptr))
			return (-1);
	}
	if (ptrlen > 1)
		ft_get_word(s + i, c, &ptr[k + 1], ptrlen - 1);
	return (0);
}
static char	**ft_res_pointer(int ptr)
{
	char	**string;
	char	*ptrs;

	string = (char **)malloc((ptr + 1) * sizeof (ptrs));
	if (!string)
		return (NULL);
	return (string);
}

char	**ft_splitraro(char const *s, char c)
{
	int		ptr;
	char	**array;

	if (!s)
		return (NULL);
	ptr = ft_len_ptr((char *)s, c);
	array = ft_res_pointer(ptr);
	if (ptr > 0)
	{
		if (ft_get_word((char *)s, c, array, ptr))
			return (NULL);
	}
	array[ptr] = NULL;
	return (array);
}

/*int close_mini(void)

{
	rl_clear_history()
	return(-1);
}*/
/*
int	ft_get_command(char **argcc, char **env)
{
	int		x;
	int		i;
	char	*ptr;

	i = 0;
	while (env[i])
	{
		ptr = ft_strjoin(env[i], argcc[0]);
		x = access(ptr, X_OK);
		if (x == 0)
			execve(ptr, &argcc[0], env);
		else
		{
			if (i == (ft_get_size(env) - 1))
				ft_putstr2(argcc[0]);
		}
		free(ptr);
		i++;
	}
	return (0);
}*/

int checker(char **paths, char *src)
{
	if (!ft_strncmp(src, "exit", 4))
		exit (-1);
	if (!ft_strncmp(src, "ls", 2))
		system("ls");
	// if (!get_cmd(paths, src))
	// 	return(0);
	// la salida de este preceso hay que cambiar con dup2
	// execve(get_cmd(paths, src), &src, env);
	return (0);
}
/*
int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	
}
*/

char	**ft_getpath(char **env)
{
	int		i;
	char	*ptr;
	char	**path;

	i = 0;
	while (env[i])
	{
		ptr = strstr(env[i], "PATH=");
		if (ptr)
			break ;
		i++;
	}
	path = ft_splitraro(ptr + 5, ':');
	return (path);
}

int	main(int argc, char **argv, char **env)
{
	//const char	*src;
	char		*ptr;
	char		**ptr2;

	ptr2 = ft_getpath(env);
	argv[1] = NULL;
	int i;
	i = argc;
	i = 0;
	while (ptr2[i])
	{
		printf("%s\n", ptr2[i]);
		i++;
	}
	printf("\n");
	//src = /*green_start*/"Minishell>"/*green_end*/;
	while (1)
	{
		ptr = readline(BOLD "Minishell $> " CLOSE);
		if (ptr == NULL)
			exit(0);
		checker(ptr2, ptr);
		if (ft_strlen(ptr))
			add_history(ptr);
		printf("%s\n",  ptr);
		free(ptr);
	}
	return (0);
}

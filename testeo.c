/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testeo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaines <ibaines@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:14:39 by ibaines           #+#    #+#             */
/*   Updated: 2022/12/02 19:04:41 by ibaines          ###   ########.fr       */
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
#include <signal.h>


static int check;

void sighandler(int signum) {

	printf("%d\n", signum);
    if (signum == 2)
   {
    exit(1);
    check = 0;
   }
}

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

void	ft_putstr(char *str)
{	
	while (*(str) != '\0')
	{	
		write(2, str, 1);
		str = str + 1;
	}
}


void	ft_putstr2(char *str)
{
	ft_putstr("zsh: command not found: ");
	ft_putstr(str);
	ft_putstr("\n");
}

int	ft_get_size(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

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
}

char **ft_first_check(char *src)
{
	char **ptr;

	ptr = ft_split(src, '|');
	if (!ptr)
		return(NULL);
	return(ptr);
}

void	ft_env(t_mini *mini)
{
	int i;

	i = 0;
	while(mini->env[i])
	{		
		printf("%s\n", mini->env[i]);
		i++;
	}
}


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

int	ft_strlen_export(char *env)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return(i);
}

int	ft_check_var2(char *src)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != '=')
		i++;
	printf("%c ", src[i]);
	printf("%d\n", i);
	return(i);
}

int	ft_check_var(char *src, t_mini *mini)
{		
	int		i;

	i = 0;
	while (mini->env[i])
	{
		if (ft_strncmp(src + 7, mini->env[i], ft_check_var2(src + 7)) == 0 && (ft_strlen_export(mini->env[i]) == ft_strlen_export(src + 7)))
		{
			free(mini->env[i]);
			mini->env[i] = ft_strdup(src + 7);
			return(1);
		}
		i++;
	}
	return(0);
}

void	ft_make_export(char *src, t_mini *mini)
{
	int		i;
	char	**new_env;

	i = 0;
	while (mini->env[i])
		i++;
	i++;
	printf("mtrx len-> %d\n", i);
	new_env = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (mini->env[i])
	{
		new_env[i] = ft_strdup(mini->env[i]);
		i++;
		printf("%d\n",i);
	}
	new_env[i] = ft_strdup(src + 7);
	i++;
	new_env[i] = NULL;
	ft_free_malloc2(mini->env);
	mini->env = new_env;
}

void	ft_export(char *src, t_mini *mini) // copiar env y añadir el eport
{
	if (!ft_check_var(src, mini))
		ft_make_export(src, mini);
}


void	ft_unset(char *src, t_mini *mini)
{
	int		i;

	i = 0;
	while (mini->env[i])
	{
		if (ft_strncmp(src + 6, mini->env[i], ft_check_var2(src + 6)) == 0 && (ft_strlen_export(mini->env[i]) == ft_strlen_export(src + 6)))
		{
			printf("liberar este\n");
			return ;
		}
		i++;
	}
	printf("no se ha encontrado la variabe\n");
}
///
int	ft_cd_swap(char *src, t_mini *mini)
{		
	int		i;

	i = 0;
	while (mini->env[i])
	{
		if (ft_strncmp(src + 3, mini->env[i], ft_check_var2(src + 3)) == 0 && (ft_strlen_export(mini->env[i]) == ft_strlen_export(src + 3)))
		{
			free(mini->env[i]);
			mini->env[i] = ft_strdup(src + 7);
			return(1);
		}
		i++;
	}
	return(0);
}

int		ft_cd(char *str, t_mini *mini)
{
	printf("%s\n", mini->env[0]);
	if (chdir(str + 3) == -1)
	{
		printf("cd: no such file or directory: %s\n", str + 3);
		return (0);
	}
	
	//cambiar env las variables oldpwd, pwd
	return (1);
}

int checker(char **paths, char *src, t_mini *mini)
{
	int pid;
	char **command;
	
	command = ft_split(src, ' ');
	if (!ft_strncmp(src, "exit", 4))
		exit (-1);
	if (!ft_strncmp(src, "env", 3))
	{	
		ft_env(mini);
		return(0);
	}
	if (!ft_strncmp(src, "export", 6))
	{	
		ft_export(src, mini);
		return(0);
	}
	if (!ft_strncmp(src, "unset", 5))
	{	
		ft_unset(src, mini);
		return(0);
	}
	if (!ft_strncmp(src, "cd", 2))
	{	
		ft_cd(src, mini);
		return(0);
	}
	pid = fork();
	if (pid == 0)
		ft_get_command(command, paths);
	else
	{
		waitpid(pid, NULL, 0);
	}
	return (0);
}

int	ft_free_malloc2(char **src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		free(src[i]);
		i++;
	}
	free(src);
	return(1);
}

char **ft_malloc(char **src)
{
	char	**save;
	int		i;
	int		n;

	i = 0;
	while (src[i])
	{
		i++;
	}
	n = i;
	printf("%s\n", src[i]);
	save = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (i < n)
	{
		printf("%d\n", i);
		save[i] = ft_strdup(src[i]);
		i++;
	}
	save[i] = NULL;
	return(save);
}

int	main(int argc, char **argv, char **env)
{
	//const char	*src;
	char		*ptr;
	char		**ptr2;
	t_mini 		mini;
	int i;

	mini.env = ft_malloc(env);
	i = 0;
 	check = 1;
   	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
	signal(SIGABRT, sighandler);
	i = 0;
	ptr2 = ft_getpath(env);
	argv[1] = NULL;
	i = argc;
	i = 0;
	/*while (ptr2[i])
	{
		printf("%s\n", ptr2[i]);
		i++;
	}
	printf("\n");*/
	//src = /*green_start*/"Minishell>"/*green_end*/;
	while (1)
	{
		ptr = readline(BOLD "Minishell $> " CLOSE);
		if (ptr == NULL)
			exit(0);
		checker(ptr2, ptr, &mini);
		if (ft_strlen(ptr))
			add_history(ptr);
		free(ptr);
	}
	ft_free_malloc2(mini.env);
	return (0);
}

#   ifndef  MINISHELL
#   define  MINISHELL

#include <stddef.h>
#include "libftt/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n);


typedef struct s_mini
{
    int pid_id;
    char **env;
    
}   t_mini 


#endif

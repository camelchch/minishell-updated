/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 12:26:55 by saxiao            #+#    #+#             */
/*   Updated: 2018/02/01 11:45:42 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft/libft.h"

#ifndef MINISHELL_H
#define MINISHELL_H

typedef struct s_table
{
	char			name[NAME_MAX + 1];
	char			path[PATH_MAX + 1];
	struct s_table	*next;
}					t_table;

typedef struct	s_shtable
{
	t_table		*sh_ta;
}				t_sh;

char		**path(char **env);
int			calcu_index(char *name);
int			is_buildin(char *app);
void		do_build(char **paras, char ***env, t_sh *table);
void		put_env(char **env);
char		*ft_getenv(char **env, char *name);
void		init_shtable(t_sh *table, char **path);
void		shell(int ac, char **av, char **env, t_sh *table);
#endif

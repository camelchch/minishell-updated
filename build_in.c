#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

int		is_buildin(char *app)
{
	return (!strcmp(app, "echo") || !strcmp(app, "cd") ||\
			!strcmp(app, "setenv") || !strcmp(app, "unsetenv") ||\
			!strcmp(app, "env") || !strcmp(app, "exit"));
}

int		nb_str(char **paras)
{
	int		ct;

	ct = 0;
	while (*paras++)
		ct++;
	return (ct);
}

void	echo(char **paras)
{
	int		ct;

	ct = nb_str(paras);
	paras++;
	while (*paras)
	{
		ft_printf("%s", *paras++);
		if (ct-- > 2)
			ft_printf(" ");
		else
			ft_printf("\n");
	}
}

void	ft_exit(void)
{
	exit(0);
}


/*void	pwd(void)
{
	char	path[PATH_MAX + 1];

	getcwd(path, PATH_MAX + 1);
	ft_printf("%s\n", path);
}
*/

void	add_env(char ***env, char **paras)
{
	char	**cp;
	int		ct;
	int		i;
	char	*temp;

	i = 0;
	//put_env(*env);
	ct = nb_str(*env) + 2;

	cp = *env;
	*env = malloc(sizeof(char *) * ct);
	while (i < ct - 2)
	{
	//	temp = *cp;
		(*env)[i++] = ft_strdup(*cp++);
//		free(temp);
	}
	(*env)[i] = ft_strjoin(*paras, "=");
	paras++;
	temp = (*env)[i];
	(*env)[i] = ft_strjoin((*env)[i], *paras);
	free(temp);
	(*env)[++i] = NULL;
//	free(cp);
}

void	delet_env(char ***env, int index)
{
//	char	*temp;
	int		after;

	//put_env(*env);
	while (index < nb_str(*env) - 1)
	{
	//	temp = *cp;
		after = index + 1;
		(*env)[index++] = (*env)[after];
//		free(temp);
	}
	(*env)[nb_str(*env) - 1] = NULL;
//	free(cp);
}

void	set_env(char **paras, char ***env)
{
	char	**cp;
	char	*temp;

	cp = *env;
	paras++;
	while (*cp && !(!ft_strncmp(*paras, *cp, ft_strlen(*paras)) && ft_strlen(*paras) < ft_strlen(*cp) && (*cp)[ft_strlen(*paras)] == '='))
		cp++;
	if (*cp)
	{
		*cp = ft_strjoin(*paras++, "=");
		temp = *cp;
		*cp = ft_strjoin(*cp, *paras);
		free(temp);
	}
	else
		add_env(env, paras);
}

void	cd(char **paras, char ***env)
{
	int		ct;
	char	*tempwd[4];
	char	path[PATH_MAX + 1];


	ct = nb_str(paras);
	if (ct != 2)
		ft_printf("usage : cd path\n");
	else
	{
	tempwd[0] = "no real meaning here";
	tempwd[1] = "OLDPWD";
	tempwd[2] = getcwd(path, PATH_MAX + 1);
	tempwd[3] = NULL;
	paras++;
	if (!ft_strcmp(*paras, "~"))
		*paras = ft_getenv(*env, "HOME");
	if (!ft_strcmp(*paras, "-"))
		*paras = ft_getenv(*env, "OLDPWD");
	if (!chdir(*paras))
	{
		set_env(tempwd, env);
	tempwd[1] = "PWD";
	tempwd[2] = getcwd(path, PATH_MAX);
		set_env(tempwd, env);
	}
	else
		ft_printf("no such directory: %s\n", *paras);
	}
}

void	unset_env(char **paras, char ***env)
{
	char	**cp;
//	char	*temp;
	int		index;

	cp = *env;
	index = 0;
	paras++;
	while (*cp && !(!ft_strncmp(*paras, *cp, ft_strlen(*paras)) && ft_strlen(*paras) < ft_strlen(*cp) && (*cp)[ft_strlen(*paras)] == '='))
	{
		cp++;
		index++;
		}
	if (*cp)
		delet_env(env,  index);
	else
		ft_printf("no such variable %s\n", *paras);
}

void	do_build(char **paras, char ***env, t_sh *table)
{
	if (!ft_strcmp(*paras, "cd"))
		cd(paras, env);
	else if (!ft_strcmp(*paras, "echo"))
		echo(paras);
	//else if (!ft_strcmp(*paras, "pwd"))
	//	pwd();
	else if (!ft_strcmp(*paras, "setenv") || !ft_strcmp(*paras, "unsetenv"))
	{
	if (!ft_strcmp(*paras, "unsetenv"))
		unset_env(paras, env);
	else
		set_env(paras, env);
	if (!ft_strcmp(*++paras, "PATH"))
		init_shtable(table, path(*env));
	}
	else if (!ft_strcmp(*paras, "env"))
		put_env(*env);
	else if (!ft_strcmp(*paras, "exit"))
		ft_exit();
}


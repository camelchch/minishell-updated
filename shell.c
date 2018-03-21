#include "minishell.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <sys/wait.h>

char	*path_in_sh(char *app, t_sh *table)
{
	int			index;
	t_table		*cp;

	index = calcu_index(app);
	cp = table[index].sh_ta;
	while (cp)
	{
		if (!strcmp(app, cp->name))
			return (cp->path);
		cp = cp->next;
	}
	return (NULL);
}

void	shell(int ac, char **av, char **env, t_sh *table)
{
	char	*line;
	char	**paras;
	char	*path;
	char	**cmd;
	pid_t	pid_no;

	(void)ac;
	(void)av;

	while(1)
	{
		ft_printf("$> ");
		get_next_line(1, &line);
		cmd = ft_strsplit(line, ';');
		while (*cmd)
		{
		paras = ft_strsplit(*cmd, ' ');
		if (is_buildin(*paras))
			do_build(paras, &env, table);
		else
		{
		pid_no = fork();
		if (pid_no < 0)
			ft_printf("fork failled");
		else if (pid_no == 0)
		{
			path = path_in_sh(*paras, table);
			execve(path, paras, env);
			execve(*paras, paras, env);
			ft_printf("there is no such program\n");
		}
		else
		{
			if (wait(NULL) == -1)
				ft_printf("wait failled\n");
		}
		}
		cmd++;
		}
	}

}

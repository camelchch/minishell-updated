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

/*void	put_choice(t_sh *table, char *cmd)
{
	ft_printf("huhu\n");
	(void)table;
	(void)cmd;
}

char	*get_autoline(t_sh *table)
{
	char	buf[1];
	char	*cmd;

	cmd = NULL;
	while (read(1, buf, 1) > 0 && *buf != '\n' && (*buf == ' ' || *buf == '\t'))
		;;

	while (*buf != '\t' && *buf != ' ' && *buf != '\n')
	{
			cmd = ft_strjoin(cmd, buf);
			read(1, buf, 1);
	}
	ft_printf("00000000000000\n");
	if (*buf == '\t')
	{
		put_choice(table, cmd);
		ft_printf("just tring");
	}
	return (NULL);
}
*/

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
//		get_autoline(table);
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
			if (!access(*paras, F_OK))
			{
			execve(*paras, paras, env);
			ft_printf("permission denied for this program: %s\n", *paras);
			}
			path = path_in_sh(*paras, table);
			if (!path)
			ft_printf("there is no such program\n");
			else
			{
			execve(path, paras, env);
			ft_printf("permission denied for this program %s\n", *paras);
			}
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

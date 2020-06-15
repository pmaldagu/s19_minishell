#include "minishell.h"

void	put_cmd(t_cmd *cmd)
{
	t_list *args_cpy = cmd->args;
	t_list *vars_cpy = cmd->vars;

	printf("\nSIZEOF struct = %ld\n", sizeof(t_cmd));
	printf("line = %s\n", (char*)cmd->line);
	printf("pos = %d\n", cmd->i);
	printf("cmd = %d\n", cmd->cmd);
	printf("args :\n");
	while (args_cpy)
	{
		printf("- %s\n", (char*)args_cpy->content);
		args_cpy = args_cpy->next;
	}
	if (cmd->env)
		printf("2nd env line = %s\n", (char*)cmd->env->next->content);
	printf("vars :\n");
	while (vars_cpy)
	{
		printf("-%s\n", (char*)vars_cpy->content);
		vars_cpy = vars_cpy->next;
	}
	printf("fd_output = %d\n", cmd->fd_output);
	printf("fd_append = %d\n", cmd->fd_append);
	printf("fd_input = %d\n", cmd->fd_input);
	printf("exit status = %d\n\n", cmd->exit_status);
}

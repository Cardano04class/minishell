/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:44:40 by mobouifr          #+#    #+#             */
/*   Updated: 2024/11/17 15:27:50 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmdsize(t_cmd *lst)
{
	int	count;

	count = 0;
	if (lst == NULL)
		return (0);
	while (lst != NULL)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

void	ft_cmddisplay(t_cmd *command)
{
	int j;
	
	j = 0;
	//printf("lst size : %d\n\n", ft_cmdsize(command));
	while (command != NULL)
	{
		j = 0;
		while (command->cmd[j])
			// printf("content : %s\n",command->cmd[j++]);
		// puts("");
		while (command->files != NULL)
		{
			// printf("filename : %s\n",command->files->filename);			
			if (command->files->type == 0)
				// printf("type : WORD\n");
			if (command->files->type == 1)
				// printf("type : INRED\n");
			if (command->files->type == 2)
				// printf("type : OUTRED\n");
			if (command->files->type == 3)
				// printf("type : APPEND\n");
			if (command->files->type == 4)
				// printf("type : HERDOC\n");
			if (command->files->type == 5)
				// printf("type : PIPE\n");		
			command->files = command->files->next;
		}
		// puts("________________________");
		command = command->next;
	}
}

int	cmd_argument_size(t_list *lst)
{
	int count = 0;
	
	while (lst != NULL && lst->type != PIPE)
	{
		if (lst->type == WORD)
			count++;
		else if (lst->type == INRED || lst->type == OUTRED || lst->type == APPEND)
			count--;
		lst = lst->next;
	}
	return (count);
}

int	command_size(t_list *lst)
{
	int count = 0;
	
	while (lst != NULL && lst->type != PIPE)
	{
		if (lst->type == WORD)
			count++;
		else if (lst->type == INRED || lst->type == OUTRED || lst->type == APPEND)
			count--;
		lst = lst->next;
	}
	return (count);
}

void	parser(t_list *lst)
{
	int			cmd_arg_size;
	int 		index_count;
	t_state		state;
	t_cmd		*tmp_cmd;
	
	index_count = 0;
	state = STATE_DEFAULT;
	cmd_arg_size = cmd_argument_size(lst);
	g_mini.command->cmd = malloc(sizeof(char *) * (cmd_arg_size + 1));
	g_mini.command->cmd[cmd_arg_size] = NULL;
	tmp_cmd = g_mini.command;
	while (lst != NULL)
	{
		if (lst->type == WORD && index_count <= cmd_arg_size)
		{
			if (state == STATE_HEREDOC)
			{
				ft_heredoc_addback(ft_heredoc_new(ft_strdup(lst->content)));
				puts("heredoooc");
				state = STATE_DEFAULT;
			}
			else if (state == STATE_REDIRECTION)
			{
				puts("3amra");
				ft_file_addback(ft_file_new(ft_strdup(lst->content), lst->prev->type));
				// printf("test %s\n", g_mini.command->files->filename);
				/*puts("");
				printf("filename : %s\n",g_mini.command->files->filename);			
				if (g_mini.command->files->type == 0)
					printf("type : WORD\n");
				if (g_mini.command->files->type == 1)
					printf("type : INRED\n");
				if (g_mini.command->files->type == 2)
					printf("type : OUTRED\n");
				if (g_mini.command->files->type == 3)
					printf("type : APPEND\n");
				if (g_mini.command->files->type == 4)
					printf("type : HERDOC\n");
				if (g_mini.command->files->type == 5)
					printf("type : PIPE\n");		
				 puts("");*/
				// tmp_cmd->files = tmp_cmd->files->next;
				// printf("test %p\n", g_mini.command->files);
				
				state = STATE_DEFAULT;
			}
			else
			{
			//	printf(">> %d\n", index_count);
				puts("commmmaaaand");
				tmp_cmd->cmd[index_count] = ft_strdup(lst->content);
			//	printf("cc: %s\n", tmp_cmd->cmd[index_count]);
				//printf("\ncommand : %s\n\n", g_mini.command->cmd[index_count]);
				index_count++;
			}
		}
		else if (lst->type == INRED || lst->type == OUTRED || lst->type == APPEND)
			state = STATE_REDIRECTION;
		else if (lst->type == HEREDOC)
			state = STATE_HEREDOC;
		else if (lst->type == PIPE)
		{
			ft_cmd_addback(&tmp_cmd, ft_cmd_new(NULL));
			tmp_cmd = tmp_cmd->next;
			lst = lst->next;
			//printf("next : %s\n", lst->content);
			cmd_arg_size = cmd_argument_size(lst);
			lst = lst->prev;
			//printf("prev : %s\n", lst->content);
			index_count = 0;
			tmp_cmd->cmd = malloc(sizeof(char *) * (cmd_arg_size + 1));
			tmp_cmd->cmd[cmd_arg_size] = NULL;
		}
		if (lst != NULL)
			lst = lst->next;
	}
		//ft_cmddisplay(g_mini.command);
}




























// 	while (lst != NULL)
// 	{
// 		if (lst->type == WORD)
// 		{	
// 			if (flag == 1)
// 			{
// 				str = ft_ssplit(lst->content);
// 				free(lst->content);
// 				lst->content = str[0];
// 				remove_first_element(str);
// 				g_mini.command->cmd = str;
// 			}
// 			else
// 				g_mini.command->cmd = ft_ssplit(lst->content);
				
// 			j = 0;
// 			while (g_mini.command->cmd[j] != NULL)
// 			{
// 				printf("%s\n", g_mini.command->cmd[j]);
// 				j++;
// 			}
// 		}
// 		else if (lst->type == INRED)
// 		{
// 			ft_file_addback(ft_file_new(ft_strdup(lst->next->content), INRED));
// 			flag = 1;		
// 		}
// 		else if (lst->type == OUTRED)
// 		{
// 			ft_file_addback(ft_file_new(ft_strdup(lst->next->content), OUTRED));
// 			flag = 1;		
// 		}
// 		else if (lst->type == APPEND)
// 		{
// 			ft_file_addback(ft_file_new(ft_strdup(lst->next->content), APPEND));			
// 			flag = 1;
// 		}
// 		else if (lst->type == HEREDOC)
// 		{	
// 		}
// 		else if (lst->type == PIPE)
// 		{	
// 			ft_cmd_addback(&g_mini.command, ft_cmd_new(NULL));
// 			g_mini.command= g_mini.command->next;
// 		}
// 		lst = lst->next;
// 	}
// }

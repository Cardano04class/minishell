/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:44:40 by mobouifr          #+#    #+#             */
/*   Updated: 2024/10/01 18:52:34 by mobouifr         ###   ########.fr       */
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
		while (command->cmd[j])
			printf("content : %s\n",command->cmd[j++]);
		puts("");
		while (command->files != NULL)
		{
			printf("filename : %s\n",command->files->filename);			
			if (command->files->type == 0)
				printf("type : WORD\n");
			if (command->files->type == 1)
				printf("type : INRED\n");
			if (command->files->type == 2)
				printf("type : OUTRED\n");
			if (command->files->type == 3)
				printf("type : APPEND\n");
			if (command->files->type == 4)
				printf("type : HERDOC\n");
			if (command->files->type == 5)
				printf("type : PIPE\n");		
			command->files = command->files->next;
		}
		puts("");
		command = command->next;
	}
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
	int			cmd_size;
	int 		index_count;
	t_state		state;
	
	index_count = 0;
	state = STATE_DEFAULT;
	cmd_size = command_size(lst);
	g_mini.command->cmd = malloc(sizeof(char *) * (cmd_size + 1));
	g_mini.command->cmd[cmd_size] = NULL;
	while (lst != NULL)
	{
		if (lst->type == WORD && index_count <= cmd_size)
		{
			if (state == STATE_REDIRECTION)
			{
				ft_file_addback(ft_file_new(ft_strdup(lst->content), lst->prev->type));
				puts("");
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
				 puts("");
				g_mini.command->files = g_mini.command->files->next;
				state = STATE_DEFAULT;
			}
			else
			{
				g_mini.command->cmd[index_count] = ft_strdup(lst->content);
				printf("\ncommand : %s\n\n", g_mini.command->cmd[index_count]);
				index_count++;
			}
		}
		else if (lst->type == INRED || lst->type == OUTRED || lst->type == APPEND)
			state = STATE_REDIRECTION;
		else if (lst->type == HEREDOC)
		{	
		}
		else if (lst->type == PIPE)
		{
			puts("_____________");
			ft_cmd_addback(&g_mini.command, ft_cmd_new(NULL));
			g_mini.command= g_mini.command->next;
			lst = lst->next;
			cmd_size = command_size(lst);
			lst = lst->prev;
			index_count = 0;
			g_mini.command->cmd = malloc(sizeof(char *) * (cmd_size + 1));
		}
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

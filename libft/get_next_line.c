/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 14:58:02 by ahavrius          #+#    #+#             */
/*   Updated: 2018/11/04 18:30:48 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_search_swap(t_list **head, int fd)
{
	t_list	*start;
	t_buff	*swap;
	t_buff	*new_content;

	start = *head;
	while (start && ((t_buff *)start->content)->fd != fd)
		start = start->next;
	if (start)
	{
		swap = (t_buff *)start->content;
		start->content = (t_buff *)(*head)->content;
		(*head)->content = swap;
		return ;
	}
	new_content = (t_buff *)malloc(sizeof(t_buff));
	new_content->fd = fd;
	new_content->str = ft_strnew(BUFF_SIZE);
	new_content->isspace = 0;
	start = *head;
	*head = ft_lstnew(new_content, sizeof(t_buff));
	free(new_content);
	(*head)->next = start;
}

static int	ft_readwrite(t_list *head, const int fd, int *i)
{
	char	buff[BUFF_SIZE + 1];
	char	*str;
	int		cur_size;
	int		read_size;

	read_size = read(fd, buff, BUFF_SIZE);
	(*i) += (read_size > 0);
	if (read_size <= 0)
		return (read_size);
	buff[read_size] = '\0';
	cur_size = ft_strlen(((t_buff *)head->content)->str);
	str = ft_strnew(read_size + cur_size);
	str = ft_strcpy(str, ((t_buff *)head->content)->str);
	str = ft_strcat(str, buff);
	free(((t_buff *)head->content)->str);
	((t_buff *)head->content)->str = str;
	return (read_size);
}

static	int	ft_del_head(t_list **head, char **line)
{
	t_list	*current;

	if (line)
		*line = NULL;
	free(((t_buff *)(*head)->content)->str);
	current = (*head)->next;
	free((*head)->content);
	free(*head);
	*head = current;
	return (0);
}

static int	ft_rewrite(t_list **head, char **line, size_t size, int flag)
{
	char	*str;
	size_t	size_len;

	str = ft_strnew(size);
	str = ft_strncpy(str, ((t_buff *)(*head)->content)->str, size);
	str[size] = '\0';
	*line = str;
	if (flag == 0 || flag == 2)
		ft_del_head(head, NULL);
	else
	{
		size_len = ft_strlen(((t_buff *)(*head)->content)->str) - size - 1;
		str = ft_strdup(((t_buff *)(*head)->content)->str + size + 1);
		free(((t_buff *)(*head)->content)->str);
		((t_buff *)(*head)->content)->str = str;
	}
	return (flag > 0);
}

int			get_next_line(const int fd, char **line)
{
	static t_list	*head;
	size_t			str_size;
	int				read_size;
	int				i;

	ft_search_swap(&head, fd);
	read_size = 1;
	i = 0;
	while (!ft_strchr(((t_buff *)head->content)->str, '\n') && read_size > 0)
		read_size = ft_readwrite(head, fd, &i);
	if (read_size == -1)
		return (-1);
	if (i == 0 && ((t_buff *)head->content)->str[0] == '\0')
		return (ft_del_head(&head, line));
	str_size = ft_strshiftnot(((t_buff *)head->content)->str, '\n', 0);
	if (!ft_strchr(((t_buff *)head->content)->str, '\n'))
		return (ft_rewrite(&head, line, str_size, 2));
	if (!((t_buff *)head->content)->str[str_size + 1])
		return (ft_rewrite(&head, line, str_size, 2));
	return (ft_rewrite(&head, line, str_size, 1));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 17:55:16 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/07 19:24:43 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builting.h"

int	check_valid_name(char *name)
{
	int	i;

	i = 0;
	if (ft_isdigit(name[i]) != 0 || (ft_isalpha(name[i]) == 0 && name[i] != '_'))
		return (1);
	i++;
	while(name[i] != '\0')
	{
		if (ft_isalpha(name[i]) == 0 && ft_isdigit(name[i]) == 0 && name[i] != '_' && name[i] != '+')
			return (1);
		i++;
	}
	return (0);
}

void	fd_putchar(char c, int fd)
{
	write (fd, &c, 1);
}

void	not_valid(char *cmd, char *arg, int type)
{
	fd_putstr("minishell: ", 2);
	if (cmd)
	{
		fd_putstr(cmd, 2);
		fd_putchar(':', 2);
	}
	if (type == 0 && arg)
	{
		fd_putstr(" [", 2);
		fd_putstr(arg, 2);
		fd_putstr("] : No such file or directory\n", 2);
	}
	else if (type == 1 && arg)
	{
		fd_putstr(" `", 2);
		fd_putstr(arg, 2);
		fd_putstr("': not a valid identifier\n", 2);
	}
	return ;
}

void	print_help(t_table *table, int i)
{
	// char	*err_message;

	// err_message = ft_calloc(1,1);
	fd_putstr("minishell: ", 2);
	fd_putstr(table->commend, 2);
	fd_putstr(": illegal option -- ", 2);
	fd_putchar(table->option[0][1], 2);
	fd_putchar('\n', 2);
	fd_putstr(table->commend, 2);
	fd_putstr(": usage: ", 2);
	fd_putstr(table->commend, 2);
	fd_putstr(" [no option]", 2);
	if (i == 1)
		fd_putstr(" [name ...]\n", 2);
	else
		fd_putchar('\n', 2);

	// printf("minishell: %s: illegal option -- %c\n", table->commend, table->option[0][1]);
	// printf("%s: usage: %s [no option]", table->commend, table->commend);
	return;
}

// int main(int ac, char **av)
// {
// 	printf("RESULT: %d\n", check_valid_name(av[1]));
// }
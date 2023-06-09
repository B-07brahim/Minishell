/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:43:21 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/19 16:51:13 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builting.h"

int	err_ch(char *arg)
{
	int	i;

	i = 0;
	if (ft_isdigit(arg[0]) == 0 && arg[0] != '+' && arg[0] != '-' )
		return (1);
	if (arg[0] == '-' || arg[0] == '+')
		i++;
	while (arg[i])
	{
		if (ft_isdigit(arg[i]) == 0)
			return (1);
		i++;
	}
	if (ft_atoi(arg) == -1 && ft_strcmp(arg, "-1") != 0)
	{
		if (ft_strcmp(arg, "-9223372036854775808") != 0)
			return (1);
		else
			exit (0);
	}
	return (0);
}

int	check_status(char **arg)
{
	int	i;
	int	type;

	i = 0;
	type = err_ch(arg[0]);
	if (type == 1)
	{
		fd_putstr("minishell: exit: ", 2);
		fd_putstr(arg[0], 2);
		fd_putstr(": numeric argument required\n", 2);
		exit(255);
	}
	if (arg[1] != NULL)
	{
		fd_putstr("minishell: exit: too many arguments\n", 2);
		g_exit = 1;
		free_array(arg);
		return (1);
	}
	if (ft_strcmp(arg[0], "-9223372036854775808") == 0)
		exit (0);
	else
		exit(ft_atoi(arg[0]) & 255);
}

int	ft_exit(t_table *table, t_env **env)
{
	char		*result;
	char		**spl;
	int			i;

	i = 0;
	if (*env && search_and_return(*env, "_", 0))
		rm_env_var(env, "_");
	new_env_var(env, ft_strjoin("_=", ft_strdup("exit")), 0);
	if (table->option[i] == NULL && table->arg[i] == NULL)
		exit(g_exit);
	result = ft_calloc(1, 1);
	while (table->option[i] != NULL)
	{
		result = sp_strjoin(result, table->option[i++], 0);
		result = sp_strjoin(result, "  ", 0);
	}
	i = 0;
	while (table->arg[i] != NULL)
	{
		result = sp_strjoin(result, table->arg[i++], 0);
		result = sp_strjoin(result, "  ", 0);
	}
	spl = ft_split(result, ' ');
	free(result);
	return (check_status(spl));
}

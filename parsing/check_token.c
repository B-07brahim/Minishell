/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 22:59:06 by bchifour          #+#    #+#             */
/*   Updated: 2023/05/19 16:50:28 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*_print_r(void)
{
	write(2, "minishell: unexpected EOF ", 26);
	write(2, "while looking for matching\n", 27);
	return (NULL);
}

t_token	*qutes(char *data, t_env *env, int i)
{
	t_token	*new;

	new = NULL;
	if (data[0] == '\"')
	{
		if (data[ft_strlen(data) - 1] == '\"' && data[1] != '\0')
		{
			(ft_strchr(data, '$')) && (i = 1);
			if (ft_strchr(data, '$'))
				data = expanding(data, env);
			new = new_token(data);
			if (i == 1)
				free(data);
		}
		else
			return (_print_r());
	}
	else if (data[0] == '\'')
	{
		if (data[ft_strlen(data) - 1] != '\'' || data[1] == '\0')
			return (_print_r());
		else
			new = new_token(data);
	}
	return (new);
}

void	save_n(t_token **new, t_env *env, char *split, int *count)
{
	char	*tmp;
	char	*part;

	part = get_part(split, split[0], split[ft_strlen(split) - 1], 2);
	tmp = part;
	while (*tmp && *tmp == ' ')
		tmp++;
	if (*tmp != '\0')
	{
		(ft_strchr(part, '$')) && (tmp = part);
		if (ft_strchr(part, '$'))
			part = expanding(part, env);
		if (ft_strchr(tmp, '$'))
			free(tmp);
		if (*count == 1 && (*count)++)
			*new = new_token(part);
		else
			lst_add_back(*new, new_token(part));
	}
	free(part);
	part = ft_strchr(split, split[ft_strlen(split) - 1]);
	if (*count == 1 && (*count)++)
		*new = new_token(part);
	else
		lst_add_back(*new, new_token(part));
}

void	save_n_1(t_token **new, t_env *env, char *split, int *count)
{
	char	*part;

	if (ft_strchr(split, '$'))
	{
		part = expanding(split, env);
		if (*count == 1 && (*count)++)
			*new = new_token(part);
		else
			lst_add_back(*new, new_token(part));
		free(part);
	}
	else
	{
		if (*count == 1 && (*count)++)
			*new = new_token(split);
		else
			lst_add_back(*new, new_token(split));
	}
}

t_token	*check_token(char *data, t_env *env, int i, int count)
{
	char	**split;
	char	fin;
	t_token	*new;

	if (data[0] == '\"' || data[0] == '\'')
		new = qutes(data, env, 0);
	else
	{
		split = ft_strtok(data, "<>|", 1);
		while (split[i])
		{
			fin = split[i][ft_strlen(split[i]) - 1];
			if (split[i][0] != fin && (fin == '|' || fin == '>' || fin == '<'))
				save_n(&new, env, split[i], &count);
			else
				save_n_1(&new, env, split[i], &count);
			i++;
		}
		free_array(split);
	}
	return (new);
}

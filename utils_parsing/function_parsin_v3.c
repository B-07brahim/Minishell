/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_parsin_v3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:16:02 by bchifour          #+#    #+#             */
/*   Updated: 2023/05/19 16:50:28 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../utils/utils.h"
#include <string.h>
#include <stdio.h>

int	rp_tab(char **line)
{
	int	i;

	i = 0;
	while ((*line)[i] && ((*line)[i] != '\"' && (*line)[i] != '\''))
	{
		if ((*line)[i] == '\t')
			(*line)[i] = ' ';
		i++;
	}
	return (i);
}

int	free_ft_strlen(char *str)
{
	int	i;

	i = ft_strlen(str);
	free(str);
	return (i);
}

void	her_doc(char *line, int i)
{
	while (line[++i])
	{
		if (line[i] == '<' && line[i + 1] == '<')
		{
			i = i + 2;
			while (line[i] == ' ' )
				i++;
			while (line[i] && line[i] != ' ')
			{
				(line[i] == '$') && (line[i] = '\5');
				if ((line[i] == '\"' || line[i] == '\'') && i++)
				{
					while (line[i] && !(line[i] == '\"' || line[i] == '\''))
					{
						(line[i] == '$') && (line[i] = '\5');
						i++;
					}
					(line[i] == '\"' || line[i] == '\'') && (i++);
				}
				else
					i++;
			}
			break ;
		}
	}
}

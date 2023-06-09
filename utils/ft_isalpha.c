/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 10:40:11 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/04 17:51:43 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_isalpha(int src)
{
	if ((src >= 65 && src <= 90) || (src >= 97 && src <= 122))
		return (1);
	return (0);
}

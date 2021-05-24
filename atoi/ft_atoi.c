/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntadevos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 14:41:43 by ntadevos          #+#    #+#             */
/*   Updated: 2020/12/09 13:46:28 by ntadevos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	signe(int s, int j)
{
	if (j % 2 == 0)
		return (s);
	else
		return (-1 * s);
}

int	ft_atoi(char *str)
{
	int s;
	int j;
	int i;

	i = 0;
	s = 0;
	j = 0;
	while (str[i] == '\n' || str[i] == '\t' || str[i] == '\v' ||
			str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			j++;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		s = s * 10 + (int)str[i] - '0';
		i++;
	}
	if (j % 2 == 0)
		return (s);
	else
		return (-1 * s);
}

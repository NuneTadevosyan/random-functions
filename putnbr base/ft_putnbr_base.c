/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntadevos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 13:14:32 by ntadevos          #+#    #+#             */
/*   Updated: 2020/12/09 13:16:25 by ntadevos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int		len(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int		anv(int nbr, char *base)
{
	int i;
	int j;

	i = -1;
	while (base[++i] != '\0')
	{
		j = i;
		while (base[++j] != '\0')
		{
			if (base[i] == base[j])
				return (0);
		}
	}
	i = 0;
	if (base[i] == '\0' || len(base) == 1)
		return (0);
	while (base[i] != '\0')
	{
		if (base[i] == ' ' || base[i] == '\f' || base[i] == '\n' ||
				base[i] == '\r' || base[i] == '\t' || base[i] == '\v' ||
				base[i] == '-' || base[i] == '+')
			return (0);
		i++;
	}
	return (1);
}

int		arrchap(int nbr, char *base)
{
	int c;
	int b;
	int i;

	i = 0;
	if (nbr < 0)
		b = (-1) * nbr;
	else
		b = nbr;
	c = len(base);
	while (b > 0)
	{
		b = b / c;
		i++;
	}
	if (nbr < 0)
		return (i + 1);
	else
		return (i);
}

void	ft_putnbr_base(int nbr, char *base)
{
	char	arr[arrchap(nbr, base)];
	int		j;
	int		c;
	int		k;

	if (anv(nbr, base) == 1)
	{
		k = len(base);
		j = arrchap(nbr, base) - 1;
		if (nbr < 0)
			c = (-1) * nbr;
		else
			c = nbr;
		while (c > 0)
		{
			arr[j] = base[c % k];
			c = c / k;
			j--;
		}
		if (nbr < 0)
			arr[0] = '-';
		write(1, arr, arrchap(nbr, base));
	}
}

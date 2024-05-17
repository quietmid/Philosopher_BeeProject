/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:35:00 by jlu               #+#    #+#             */
/*   Updated: 2024/05/17 23:39:30 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_get_int(const char *s, int i)
{
	unsigned long	nb;

	nb = 0;
	while (*s >= '0' && *s <= '9')
	{
		if (i == 1 && nb > (unsigned long)LONG_MAX / 10)
			return (-1);
		else if (i == -1 && nb > (unsigned long)LONG_MAX / 10)
			return (0);
		nb = nb * 10;
		if (i == 1 && nb > (unsigned long)LONG_MAX - (*s - 48))
			return (-1);
		else if (i == -1 && nb > (unsigned long)LONG_MAX - (*s - 48))
			return (0);
		nb += (*s - 48);
		s++;
	}
	return (nb);
}

int	ft_atol(const char *s)
{
	unsigned long	nb;
	int				i;

	nb = 0;
	i = 1;
	while (((*s > 8 && *s < 14) || *s == 32))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			i *= -1;
		s++;
	}
	nb = ft_get_int(s, i);
	return (nb * i);
}

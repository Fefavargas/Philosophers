/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefa <fefa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:36:21 by fvargas           #+#    #+#             */
/*   Updated: 2025/02/04 15:41:56 by fefa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_nbr(char *str)
{
	size_t	j;
	bool	flag;
	long	nbr;

	j = 0;
	flag = 1;
	while (str[j])
	{
		if (str[j] == '+' && flag)
			j++;
		flag = 0;
		if (!(str[j] >= '0' && str[j++] <= '9'))
			return (0);
	}
	nbr = ft_atoi(str);
	if (nbr < 0 || nbr > INT_MAX)
		return (0);
	return (1);
}

bool	checker_args(char **argv)
{
	int	i;

	i = 0;
	while (argv[++i])
	{
		if (!check_nbr(argv[i]))
		{
			ft_putstr_fd(ERR_INTEGER, STDERR_FILENO);
			return (0);
		}
	}
	return (1);
}

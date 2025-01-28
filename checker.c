/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:36:21 by fvargas           #+#    #+#             */
/*   Updated: 2025/01/28 15:04:19 by fvargas          ###   ########.fr       */
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
		if (str[j] == '-' && flag)
			j++;
		if (str[j] == '+' && flag)
			j++;
		flag = 0;
		if (!(str[j] >= '0' && str[j++] <= '9'))
			return (0);
	}
	nbr = ft_atoi(str);
	if (nbr < INT_MIN || nbr > INT_MAX)
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
			printf("The argument %ith is not a integer", i);
			return (0);
		}
	}
	return (1);
}
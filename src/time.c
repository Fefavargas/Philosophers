/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 19:14:23 by fvargas           #+#    #+#             */
/*   Updated: 2025/02/09 22:29:22 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 	Returns '0' when error occuors
			time when sucessed
 */
unsigned long long	get_time(void)
{
	unsigned long long	time_in_ms;
	struct timeval		tv;

	if (gettimeofday(&tv, NULL))
	{
		ft_putstr_fd(ERR_GET_TIME, STDERR_FILENO);
		return (0);
	}
	time_in_ms = (tv.tv_sec * 1000ULL) + (tv.tv_usec / 1000ULL);
	return (time_in_ms);
}

bool	precise_wait(unsigned int waiting_time)
{
	unsigned long long	t_started;
	unsigned long long	t_current;

	t_started = get_time();
	if (!t_started)
		return (0);
	while (1)
	{
		t_current = get_time();
		if (!t_current)
			return (0);
		if (t_current >= t_started + waiting_time)
			return (1);
	}
	return (0);
}

void	set_start_time(t_default *def)
{
	unsigned long long	time;
	size_t				i;

	i = 0;
	time = get_time();
	def->t_started = time;
	while (i < def->n_philo)
		def->philos[i++].last_meal = time;
}

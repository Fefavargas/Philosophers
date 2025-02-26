/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 19:51:59 by fvargas           #+#    #+#             */
/*   Updated: 2025/02/26 20:56:09 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	print_log(t_philo *philo, unsigned long long timestamp, \
					t_philo_action ac)
{
	if (get_mutex_stop_def(philo->def))
		return (1);
	if (!mtx_perform_action(&philo->def->mtx_print_lock, LOCK))
		return (0);
	if (ac == FORK)
		printf("%llu %d has taken a fork\n", timestamp, philo->id + 1);
	else if (ac == EAT)
		printf("%llu %d is eating\n", timestamp, philo->id + 1);
	else if (ac == SLEEP)
		printf("%llu %d is sleeping\n", timestamp, philo->id + 1);
	else if (ac == THINK)
		printf("%llu %d is thinking\n", timestamp, philo->id + 1);
	else if (ac == DIE)
		printf("%llu %d died\n", timestamp, philo->id + 1);
	if (!mtx_perform_action(&philo->def->mtx_print_lock, UNLOCK))
		return (0);
	return (1);
}

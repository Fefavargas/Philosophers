/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 19:51:59 by fvargas           #+#    #+#             */
/*   Updated: 2025/02/28 23:24:26 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_is_dead(t_default *def, t_philo *philo)
{
	print_log(philo, get_time() - def->t_started, DIE);
	mtx_stop(def);
}

void	print_log(t_philo *philo, unsigned long long timestamp, \
					t_philo_action ac)
{
	if (get_mtx_stop(philo->def))
		return ;
	mtx_action(&philo->def->mtx_print_lock, LOCK);
	if (ac == FORK)
		printf("%llu %d has taken a fork\n", timestamp, philo->id);
	else if (ac == EAT)
		printf("%llu %d is eating\n", timestamp, philo->id);
	else if (ac == SLEEP)
		printf("%llu %d is sleeping\n", timestamp, philo->id);
	else if (ac == THINK)
		printf("%llu %d is thinking\n", timestamp, philo->id);
	else if (ac == DIE)
		printf("%llu %d died\n", timestamp, philo->id);
	mtx_action(&philo->def->mtx_print_lock, UNLOCK);
}

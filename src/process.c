/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:19:22 by fvargas           #+#    #+#             */
/*   Updated: 2025/02/09 19:06:21 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	action_forks(t_mtx *fork, t_philo *philo, t_mtx_action ac)
{
	if (!mtx_perform_action(fork, ac))
		return (0);
	if (ac == LOCK)
		print_log(philo->id, get_time() - *philo->t_started, FORK);
	return (1);
}

/**
 Function to get the fork first into left side for odd index_numbers and first right side for even index_number
 Same function for pick or drop action
 PICK_FORK 
		ac = LOCK
 DROP_FORK
		ac = UNLOCK
 */
bool	pick_drop_forks(t_philo *philo, t_mtx_action ac)
{
	if (philo->id % 2)
	{
		if (action_forks(philo->l_fork, philo, ac))
			return (0);
		if (action_forks(philo->r_fork, philo, ac))
			return (0);
	}
	else
	{
		if (action_forks(philo->r_fork, philo, ac))
			return (0);
		if (action_forks(philo->l_fork, philo, ac))
			return (0);
	}
	return (1);
}

void	eat(t_philo *philo)
{
	philo->n_eats++;
	if (!mtx_perform_action(philo->meal_lock, LOCK))
	{
		pick_drop_forks(philo, UNLOCK);
		return ;
	}
	philo->last_meal = get_time();
	mtx_perform_action(philo->meal_lock, UNLOCK);
	{
		pick_drop_forks(philo, UNLOCK);
		return ;
	}
	print_log(philo->id, philo->last_meal - *philo->t_started, EAT);
	precise_wait(philo->t_eat);
	pick_drop_forks(philo, UNLOCK);
	return ;
}

void	*philo_process(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pick_drop_forks(philo, LOCK);
		eat(philo);

	}
	return (0);
}

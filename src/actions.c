/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:44:22 by fefa              #+#    #+#             */
/*   Updated: 2025/02/28 17:39:16 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	action_forks(t_mtx *fork, t_philo *philo, t_mtx_action ac)
{
	unsigned long long	timestamp;

	if (!mtx_perform_action(fork, ac))
		return (0);
	if (ac == LOCK)
	{
		timestamp = get_time() - philo->def->t_started;
		print_log(philo, timestamp, FORK);
	}
	return (1);
}

/**
 Function to get the fork first into left side for odd index_numbers and first right side for even index_number
 Same function for pick or drop action
 --odd numbers wait usleep(100) in the first meal to make sure that all even numbers take the fork together
 PICK_FORK 
		ac = LOCK
 DROP_FORK
		ac = UNLOCK
 */
bool	pick_drop_forks(t_philo *philo, t_mtx_action ac)
{
	if (get_mutex_stop(philo->def))
		return (0);
	if (philo->id % 2)
	{
		if (!philo->n_eats)
			usleep(100);
		if (!action_forks(philo->l_fork, philo, ac))
		{
			return (0);
		}
		if (!action_forks(philo->r_fork, philo, ac))
			return (0);
	}
	else
	{
		if (!action_forks(philo->r_fork, philo, ac))
			return (0);
		if (!action_forks(philo->l_fork, philo, ac))
			return (0);
	}
	return (1);
}

void	eat(t_philo *philo)
{
	if (get_mutex_stop(philo->def))
		return ;
	philo->n_eats++;
	if (!mtx_perform_action(&philo->mtx_meal_lock, LOCK))
	{
		pick_drop_forks(philo, UNLOCK);
		return ;
	}
	philo->last_meal = get_time() - philo->def->t_started;
	if (!mtx_perform_action(&philo->mtx_meal_lock, UNLOCK))
	{
		pick_drop_forks(philo, UNLOCK);
		return ;
	}
	print_log(philo, philo->last_meal, EAT);
	precise_wait(philo->def->t_eat);
	pick_drop_forks(philo, UNLOCK);
}

void	sleep_think(t_philo *philo, t_philo_action ac, unsigned int waittime, \
					unsigned long long timestamp)
{
	if (get_mutex_stop(philo->def))
		return ;
	print_log(philo, timestamp, ac);
	precise_wait(waittime);
}

void	ft_is_dead(t_default *def, t_philo *philo)
{
	print_log(philo, get_time() - def->t_started, DIE);
	mutex_stop(def);
}

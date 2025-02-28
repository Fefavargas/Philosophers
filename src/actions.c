/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:44:22 by fefa              #+#    #+#             */
/*   Updated: 2025/02/28 23:15:29 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	action_forks(t_mtx *fork, t_philo *philo, t_mtx_action ac)
{
	mtx_perform_action(fork, ac);
	if (ac == LOCK)
		print_log(philo, get_time() - philo->def->t_started, FORK);
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
	if (philo->id % 2)
	{
		action_forks(philo->l_fork, philo, ac);
		action_forks(philo->r_fork, philo, ac);
	}
	else
	{
		if (!philo->n_eats)
			usleep(100);
		action_forks(philo->r_fork, philo, ac);
		action_forks(philo->l_fork, philo, ac);
	}
	return (1);
}

bool	ft_eat(t_philo *philo)
{
	pick_drop_forks(philo, LOCK);
	mtx_perform_action(&philo->def->mtx_meal_lock, LOCK);
	philo->last_meal = get_time() - philo->def->t_started;
	philo->n_eats++;
	mtx_perform_action(&philo->def->mtx_meal_lock, UNLOCK);
	print_log(philo, philo->last_meal, EAT);
	precise_wait(philo->def->t_eat);
	pick_drop_forks(philo, UNLOCK);
	return (1);
}

bool	ft_sleep(t_philo *philo)
{
	if (get_mutex_stop(philo->def))
		return (0);
	print_log(philo, get_time() - philo->def->t_started, SLEEP);
	precise_wait(philo->def->t_sleep);
	return (1);
}

void	ft_think(t_philo *philo)
{
	if (get_mutex_stop(philo->def))
		return ;
	print_log(philo, get_time() - philo->def->t_started, THINK);
	precise_wait(philo->def->t_die - philo->def->t_eat - philo->def->t_sleep);
}

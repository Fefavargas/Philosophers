/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:44:22 by fefa              #+#    #+#             */
/*   Updated: 2025/04/16 14:22:28 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	action_forks(t_mtx *fork, t_philo *philo, t_mtx_action ac)
{
	mtx_action(fork, ac);
	if (ac == LOCK)
		print_log(philo, FORK);
}

/**
 Function to get the fork first into left side for odd index_numbers 
 and first right side for even index_number
 Same function for pick or drop action
 --odd numbers wait usleep(100) in the first meal to make sure that 
 all even numbers take the fork together
 PICK_FORK 
		ac = LOCK
 DROP_FORK
		ac = UNLOCK
 */
void	pick_drop_forks(t_philo *philo, t_mtx_action ac)
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
}

void	ft_eat(t_philo *philo)
{
	pick_drop_forks(philo, LOCK);
	mtx_action(&philo->def->mtx_meal_lock, LOCK);
	philo->last_meal = get_time() - philo->def->t_started;
	philo->n_eats++;
	mtx_action(&philo->def->mtx_meal_lock, UNLOCK);
	print_log(philo, EAT);
	precise_wait(philo->def->t_eat);
	pick_drop_forks(philo, UNLOCK);
}

void	ft_sleep(t_philo *philo)
{
	if (get_mtx_stop(philo->def))
		return ;
	print_log(philo, SLEEP);
	precise_wait(philo->def->t_sleep);
}

void	ft_think(t_philo *philo)
{
	if (get_mtx_stop(philo->def))
		return ;
	print_log(philo, THINK);
	precise_wait(1);
}

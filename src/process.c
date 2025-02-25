/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:19:22 by fvargas           #+#    #+#             */
/*   Updated: 2025/02/25 13:02:00 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	action_forks(t_mtx *fork, t_philo *philo, t_mtx_action ac)
{
	unsigned long long	timestamp;

	if (!mtx_perform_action(fork, ac))
		return (0);
	if (ac == LOCK)
		print_log(philo, get_time() - *philo->t_started, FORK);
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
	if (!mtx_perform_action(&philo->mtx_meal_lock, LOCK))
	{
		pick_drop_forks(philo, UNLOCK);
		return ;
	}
	philo->last_meal = get_time() - *philo->t_started;
	philo->n_eats++;
	if (!mtx_perform_action(&philo->mtx_meal_lock, UNLOCK))
	{
		pick_drop_forks(philo, UNLOCK);
		return ;
	}
	print_log(philo, philo->last_meal, EAT);
	precise_wait(philo->t_eat);
	pick_drop_forks(philo, UNLOCK);
	return ;
}

void	sleep_think(t_philo *philo, t_philo_action ac)
{
	if (ac == SLEEP)
	{
		print_log(philo, philo->last_meal + philo->t_eat, ac);
		precise_wait(philo->t_sleep);
	}
	if (ac == THINK)
	{
		print_log(philo, philo->last_meal + philo->t_eat + philo->t_sleep, ac);
		precise_wait(philo->t_die - philo->t_eat - philo->t_sleep);
	}
}

void	*philo_process(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!get_mutex_stop_philo(philo))
	{
		pick_drop_forks(philo, LOCK);
		eat(philo);
		sleep_think(philo, SLEEP, philo->t_sleep, \
			philo->last_meal + philo->t_eat);

		sleep_think(philo, THINK, philo->t_die - philo->t_eat - philo->t_sleep, \
			philo->last_meal + philo->t_eat + philo->t_sleep);
// sleep_think(philo, SLEEP, philo->t_sleep, 
// 	get_time() - *philo->t_started);

// sleep_think(philo, THINK, (philo->t_die - philo->t_eat - get_time() + philo->last_meal) / 2, 
// 	get_time() - *philo->t_started);
	}
	return (0);
}

bool	philo_thread(t_default *def)
{
	size_t	i;

	i = 0;
	while (i < def->n_philo)
	{
		if (pthread_create(&def->philos[i].thread_id, NULL, \
			philo_process, &def->philos[i]))
		{
			//ERROR:
			printf("ERROR");
			return (0);
		}
		i++;
	}
	i = 0;
	while (i < def->n_philo)
	{
		pthread_join(def->philos[i].thread_id, NULL);
		i++;
	}
	return (1);
}

bool	solution(t_default *def)
{
	set_start_time(def);
	if (!start_monitoring(def))
		return (0);
	if (!philo_thread(def))
		return (0);
	if (!end_monitoring(def))
		return (0);
	return (1);
}

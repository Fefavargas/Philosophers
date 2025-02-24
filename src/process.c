/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefa <fefa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:19:22 by fvargas           #+#    #+#             */
/*   Updated: 2025/02/24 15:21:49 by fefa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

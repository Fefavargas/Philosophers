/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefa <fefa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:19:22 by fvargas           #+#    #+#             */
/*   Updated: 2025/02/28 22:17:06 by fefa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_process(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!get_mtx_stop(philo->def))
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (0);
}

bool	start_threads(t_default *def)
{
	size_t	i;

	i = 0;
	while (i < def->n_philo)
	{
		pthread_create(&def->philos[i].thread_id, NULL, \
			philo_process, &def->philos[i]);
		i++;
	}
	pthread_create(&def->monitor, NULL, &monitor, def);
	return (1);
}

bool	end_threads(t_default *def)
{
	size_t	i;

	i = 0;
	while (i < def->n_philo)
		pthread_join(def->philos[i++].thread_id, NULL);
	pthread_join(def->monitor, NULL);
	return (1);
}

bool	solution(t_default *def)
{
	set_start_time(def);
	// if (def->n_philo == 1)
	// {
	// 	if (!action_forks(def->philos[0].r_fork, &def->philos[0], LOCK))
	// 		return (0);
	// 	precise_wait(def->t_die);
	// 	ft_is_dead(def, &def->philos[0]);
	// 	return (1);
	// }
	start_threads(def);
	end_threads(def);
	
	return (1);
}

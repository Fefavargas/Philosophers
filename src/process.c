/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:19:22 by fvargas           #+#    #+#             */
/*   Updated: 2025/02/26 20:56:43 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_process(void *arg)
{
	t_philo	*philo;
	unsigned int time;
	//unsigned long long	timestamp;

	philo = (t_philo *)arg;
	while (!get_mutex_stop_def(philo->def))
	{
		pick_drop_forks(philo, LOCK);
		eat(philo);
		sleep_think(philo, SLEEP, philo->def->t_sleep, get_time() - philo->def->t_started);
		time = philo->def->t_die - philo->def->t_eat - philo->def->t_sleep;
		if (time < 0)
			time = 0;
		sleep_think(philo, THINK, time , get_time() - philo->def->t_started);
		
		//sleep_think(philo, THINK, philo->t_die - philo->t_eat - philo->t_sleep, philo->last_meal + philo->t_eat + philo->t_sleep);

		//timestamp = (philo->t_die - (get_time() - (*philo->t_started + philo->last_meal)) - philo->t_eat) / 2;
		//printf("tempo de pensar e': %llu\n", timestamp);
		 //sleep_think(philo, THINK, (philo->t_die - (get_time() - (*philo->t_started + philo->last_meal)) - philo->t_eat) / 2, get_time() - *philo->t_started);
	}
	return (0);
}

bool start_threads(t_default *def)
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

bool end_threads(t_default *def)
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
	if (def->n_philo == 1)
	{
		if (!action_forks(def->philos[0].r_fork, &def->philos[0], LOCK))
			return (0);
		precise_wait(def->t_die);
		if (!action_forks(def->philos[0].r_fork, &def->philos[0], UNLOCK))
			return (0);
		ft_is_dead(def, &def->philos[0]);
		return (1);
	}
	start_threads(def);
	end_threads(def);
	return (1);
}

// bool	philo_thread(t_default *def)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < def->n_philo)
// 	{
// 		pthread_create(&def->philos[i].thread_id, NULL, \
// 			philo_process, &def->philos[i]);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < def->n_philo)
// 		pthread_join(def->philos[i++].thread_id, NULL);
// 	return (1);
// }

// void	checkstop(t_default *def)
// {
// 	int					full;
// 	size_t				i;
// 	size_t				count_full;

// 	i = 0;
// 	count_full = 0;
// 	while (i < def->n_philo)
// 	{
// 		if (check_starving(def, &def->philos[i]))
// 		{
// 			ft_is_dead(def, &def->philos[i]);
// 			return ;
// 		}
// 		full = check_full(def, &def->philos[i]);
// 		if (full == -1) 
// 			return ; //ERROR:
// 		count_full += full;
// 		i++;
// 	}
// 	if (count_full == def->n_philo)
// 	{
// 		mutex_stop(def);
// 		return ;
// 	}
// }

// bool	solution(t_default *def)
// {
// 	set_start_time(def);
// 	if (def->n_philo == 1)
// 	{
// 		if (!action_forks(def->philos[0].r_fork, &def->philos[0], LOCK))
// 			return (0);
// 		precise_wait(def->t_die);
// 		if (!action_forks(def->philos[0].r_fork, &def->philos[0], UNLOCK))
// 			return (0);
// 		ft_is_dead(def, &def->philos[0]);
// 		return (1);
// 	}
// 	if (!philo_thread(def))
// 		return (0);
// 	while (!def->stop)
// 	{
// 		checkstop(def);
// 		usleep(100);
// 	}
// 	return (1);
// }

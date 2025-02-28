/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:45:23 by fefa              #+#    #+#             */
/*   Updated: 2025/02/28 17:39:43 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/** 
 * Return -1 Mutex error
 * 		   0 Philosophers is not full
 * 		   1 Philosophers is full
*/
int	check_full(t_default *def, t_philo *philo)
{
	int	full;

	full = 0;
	if (!mtx_action(&philo->mtx_meal_lock, LOCK, def))
		return (-1);
	if (def->n_eats == philo->n_eats)
		full = 1;
	if (!mtx_action(&philo->mtx_meal_lock, UNLOCK, def))
		return (-1);
	return (full);
}

/** 
 * Return -1 Mutex error
 * 		   0 Philosophers is not dead/starving
 * 		   1 Philosophers is dead/starving
*/
int	check_starving(t_philo *philo)
{
	int					result;

	result = 0;
	if (!mtx_action(&philo->mtx_meal_lock, LOCK, philo->def))
		return (-1);
	if (philo->def->t_started + philo->last_meal + philo->def->t_die < get_time())
		result = 1;
	if (!mtx_action(&philo->mtx_meal_lock, UNLOCK, philo->def))
		return (-1);
	return (result);
}

bool	check_full_philos(t_default *def)
{
	size_t	i;

	i = 0;
	while (i < def->n_philo)
	{
		if (!check_full(def, &def->philos[i++]))
			return (0);
	}
	mutex_stop(def);
	return (1);
}

bool	check_starv_philos(t_default *def)
{
	size_t	i;

	i = 0;
	while (i < def->n_philo)
	{
		if (check_starving(&def->philos[i]))
		{
			print_log(&def->philos[i], get_time() - def->t_started, DIE);
			mutex_stop(def);
			return (1);
		}
		i++;
	}
	return (0);
}

/** 
 	Checks if all philosofers already eat the selected number of times 
 	and check if any philosofer are dead
*/
void	*monitor(void *arg)
{
	t_default			*def;

	def = (t_default *)arg;
	while (1)
	{
		if (check_full_philos(def))
			return (0);
		if (check_starv_philos(def))
			return (0);
		usleep(100);
	}
	return (0);
}


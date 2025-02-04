/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefa <fefa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:45:23 by fefa              #+#    #+#             */
/*   Updated: 2025/02/04 19:54:29 by fefa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/** 
 * Return -1 Mutex error
 * 		   0 Philosophers is not dead/starving
 * 		   1 Philosophers is dead/starving
*/
int	check_starving(t_default *def, t_philo *philo,
					unsigned long long current_time)
{
	if (!mtx_action(philo->meal_lock, LOCK, def))
		return (-1);
	if (philo->last_meal + def->t_die < current_time)
		return (1);
	if (!mtx_action(philo->meal_lock, UNLOCK, def))
		return (-1);
	return (0);
}

/** 
 	Checks if all philosofers already eat the selected number of times 
 	and check if any philosofer are dead
*/
void	*monitor(t_default *def)
{
	int	i;
	int	count_full;

	while (1)
	{
		i = 0;
		count_full = 0;
		while (i < def->n_philo)
		{
			if (def->n_eats >= def->philos[i].n_eats)
			{
				count_full++;
			}
			if (def->philos[i++].dead)
			{
				return (NULL);
			}
		}
		if (count_full == def->n_philo)
		{
			return (NULL);
		}
	}
	return (NULL);
}

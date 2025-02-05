/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:45:23 by fefa              #+#    #+#             */
/*   Updated: 2025/02/05 13:45:54 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	start_monitoring(t_default *def)
{
	if (!def->n_eats)
		return (1);
	if (pthread_create(&def->monitor, NULL, &monitor, def))
		return (ft_putstr_fd_return(ERR_TH_MONI, STDERR_FILENO, 0));
	return (1);
}

bool	end_monitoring(t_default *def)
{
	if (!def->n_eats)
		return (1);
	if (ptread_join(&def->monitor, NULL))
		return (ft_putstr_fd_return(ERR_TH_JOIN, STDERR_FILENO, 0));
	return (1);
}

/** 
 * Return -1 Mutex error
 * 		   0 Philosophers is not dead/starving
 * 		   1 Philosophers is dead/starving
*/
int	check_starving(t_default *def, t_philo *philo)
{
	unsigned long long	current_time;

	current_time = get_time();
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
			if (check_starving(def, &def->philos[i]))
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

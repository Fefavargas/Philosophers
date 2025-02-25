/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:45:23 by fefa              #+#    #+#             */
/*   Updated: 2025/02/13 16:31:19 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_stop(t_default *def)
{
	mtx_action(&def->mtx_stop, LOCK, def);
	def->stop = 1;
	mtx_action(&def->mtx_stop, UNLOCK, def);
}

void	ft_is_dead(t_default *def, t_philo *philo)
{
	print_log(philo, get_time() - def->t_started, DIE);
	ft_stop(def);
	return ;
}

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
int	check_starving(t_default *def, t_philo *philo, unsigned long long current_time)
{
	int					result;

	result = 0;
	if (!mtx_action(&philo->mtx_meal_lock, LOCK, def))
		return (-1);
	if (def->t_started + philo->last_meal + def->t_die < current_time)
		result = 1;
	if (!mtx_action(&philo->mtx_meal_lock, UNLOCK, def))
		return (-1);
	return (result);
}

/** 
 	Checks if all philosofers already eat the selected number of times 
 	and check if any philosofer are dead
*/
void	*monitor(void *arg)
{
	int					full;
	size_t				i;
	size_t				count_full;
	t_default			*def;

	def = (t_default *)arg;
	while (1)
	{
		i = 0;
		count_full = 0;
		while (i < def->n_philo)
		{
			full = check_full(def, &def->philos[i]);
			if (full == -1) 
				return (0); //ERROR:
			count_full += full;
			if (check_starving(def, &def->philos[i], get_time()) == 1)
			{
				ft_is_dead(def, &def->philos[i]);
				//printf("HERE2");
				return (0);
			}
			i++;
		}
		if (count_full == def->n_philo)
		{
			ft_stop(def);
			//printf("HERE");
			return (0);
		}
		usleep(100);
	}
	return (0);
}

bool	start_monitoring(t_default *def)
{
	if (!def->n_eats)
		return (1);
	if (pthread_create(&def->monitor, NULL, &monitor, def))
		return (ft_putstr_fd_return(ERR_TH_MONI, STDERR_FILENO, 0));
	//(void)usleep(100); //WHY?
	return (1);
}

bool	end_monitoring(t_default *def)
{
	if (!def->n_eats)
		return (1);
	if (pthread_join(def->monitor, NULL))
		return (ft_putstr_fd_return(ERR_TH_JOIN, STDERR_FILENO, 0));
	return (1);
}

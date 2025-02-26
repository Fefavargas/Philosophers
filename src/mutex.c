/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:24:44 by fvargas           #+#    #+#             */
/*   Updated: 2025/02/26 20:34:37 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	mtx_perform_action(t_mtx *mutex, t_mtx_action action)
{
	int	result;

	if (action == INIT)
		result = pthread_mutex_init(mutex, NULL);
	if (action == LOCK)
		result = pthread_mutex_lock(mutex);
	if (action == UNLOCK)
		result = pthread_mutex_unlock(mutex);
	if (action == DESTROY)
		result = pthread_mutex_destroy(mutex);
	if (!result)
		return (1);
	ft_putstr_fd(ERR_MTX, STDERR_FILENO);
	return (0);
}

bool	mtx_action(t_mtx *mutex, t_mtx_action action, t_default *def)
{
	if (!mtx_perform_action(mutex, action))
	{
		free_def(def);
		return (0);
	}
	return (1);
}

void	mutex_stop(t_default *def)
{
	mtx_action(&def->mtx_stop, LOCK, def);
	def->stop = 1;
	mtx_action(&def->mtx_stop, UNLOCK, def);
}

bool	get_mutex_stop_def(t_default *def)
{
	bool	value;

	mtx_action(&def->mtx_stop, LOCK, def);
	value = def->stop;
	mtx_action(&def->mtx_stop, UNLOCK, def);
	return (value);
}


bool	get_mutex_stop_philo(t_philo *philo)
{
	bool	value;

	// printf("NUTEX\n");
	// mtx_perform_action(philo->mtx_stop, LOCK);
	// value = *(philo->stop);
	// mtx_perform_action(philo->mtx_stop, UNLOCK);
	value = get_mutex_stop_def(philo->def);
	return (value);
}


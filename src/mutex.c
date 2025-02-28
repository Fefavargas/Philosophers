/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:24:44 by fvargas           #+#    #+#             */
/*   Updated: 2025/02/28 21:06:59 by fvargas          ###   ########.fr       */
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
		destroy_mtx(def);
		return (0);
	}
	return (1);
}

void	mutex_stop(t_default *def)
{
	mtx_action(&def->mtx_meal_lock, LOCK, def);
	def->stop = 1;
	mtx_action(&def->mtx_meal_lock, UNLOCK, def);
}

bool	get_mutex_stop(t_default *def)
{
	bool	value;

	mtx_action(&def->mtx_meal_lock, LOCK, def);
	value = def->stop;
	mtx_action(&def->mtx_meal_lock, UNLOCK, def);
	return (value);
}

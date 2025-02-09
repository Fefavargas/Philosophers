/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:24:44 by fvargas           #+#    #+#             */
/*   Updated: 2025/02/09 18:55:23 by fvargas          ###   ########.fr       */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:24:44 by fvargas           #+#    #+#             */
/*   Updated: 2025/02/03 17:46:56 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/** 
 @return '0' on sucess;
*/
static int	mtx_perform_action(t_mtx *mutex, t_mtx_action action)
{
	if (action == INIT)
		return (pthread_mutex_init(mutex, NULL));
	if (action == LOCK)
		return (pthread_mutex_lock(mutex));
	if (action == UNLOCK)
		return (pthread_mutex_unlock(mutex));
	if (action == DESTROY)
		return (pthread_mutex_destroy(mutex));
	return (1);
}

bool	mtx_action(t_mtx *mutex, t_mtx_action action, t_default *def)
{
	if (mtx_perform_action(mutex, action) != 0)
	{
		print_err_free_def(def, ERR_MTX);
		return (0);
	}
	return (1);
}

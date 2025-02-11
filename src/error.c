/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:15:53 by fvargas           #+#    #+#             */
/*   Updated: 2025/02/11 16:52:05 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_fork_index(t_default *def, size_t index)
{
	size_t	i;

	i = 0;
	while (i > 0 && i < index)
		(void)mtx_action(&def->forks[i++], DESTROY, def);
	free(def->forks);
}

void	free_philos(t_default *def)
{
	size_t	i;

	i = 0;
	if (def && !def->philos)
	{
		while (i < def->n_philo)
		{
			mtx_action(&def->philos[i].mtx_meal_lock, DESTROY, def);
			free(&def->philos[i++]);
		}
		free(def->philos);
	}
}

void	free_def(t_default *def)
{
	if (!def)
		return ;
	if (def->philos)
		free_philos(def);
	if (def->forks)
		free_fork_index(def, def->n_philo);
	mtx_action(&def->mtx_print_lock, DESTROY, def);
	mtx_action(&def->mtx_stop, DESTROY, def);
}

void	print_err_free_def(t_default *def, char *msg)
{
	free_def(def);
	ft_putstr_fd(msg, STDERR_FILENO);
}

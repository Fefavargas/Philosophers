/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefa <fefa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:15:53 by fvargas           #+#    #+#             */
/*   Updated: 2025/02/28 22:24:58 by fefa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_mtx(t_default *def)
{
	size_t	i;

	i = 0;
	while (i < def->n_philo)
		mtx_action(&def->forks[i++], DESTROY);
	mtx_action(&def->mtx_print_lock, DESTROY);
	mtx_action(&def->mtx_meal_lock, DESTROY);
	free(def->philos);
	free(def->forks);
}

void	print_err_free_def(t_default *def, char *msg)
{
	destroy_mtx(def);
	ft_putstr_fd(msg, STDERR_FILENO);
}

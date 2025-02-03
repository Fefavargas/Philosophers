/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:50:50 by fvargas           #+#    #+#             */
/*   Updated: 2025/02/03 17:52:01 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	init_philo(t_default *def, int index)
{
	def->philos[index].n_eats = 0;
	return (1);
}

bool	create_philo(t_default *def)
{
	int	i;

	def->philos = (t_philo *)malloc(sizeof(t_philo) * def->n_philo);
	if (!def->philos)
	{
		print_err_free_def(def, ERR_MALLOC);
		return (0);
	}
	i = -1;
	while (++i < def->n_philo)
	{
		init_philo(def, i);
	}
	return (1);
}

bool	create_fork(t_default *def)
{
	def->forks = malloc(sizeof(t_fork) * def->n_philo);
	if (def->forks)
	{
		print_err_free_def(def, ERR_MALLOC);
		return (0);
	}
	return (1);
}

bool	create_default(int argc, char **argv, t_default *def)
{
	size_t		i;

	def = (t_default *)malloc(sizeof(t_default));
	if (!def)
	{
		ft_putstr_fd(ERR_MALLOC, STDERR_FILENO);
		return (0);
	}
	i = 0;
	def->n_philo = ft_atoi(argv[1]);
	def->t_die = ft_atoi(argv[2]);
	def->t_eat = ft_atoi(argv[3]);
	def->t_sleep = ft_atoi(argv[4]);
	def->n_eats = -1;
	if (argc == 6)
		def->n_eats = ft_atoi(argv[5]);
	if (!create_philo(def))
		return (0);
	if (!create_fork(def))
		return (0);
	return (1);
}

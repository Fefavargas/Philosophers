/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:50:50 by fvargas           #+#    #+#             */
/*   Updated: 2025/02/25 12:56:02 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	init_philo(t_default *def, int index)
{
	def->philos[index].n_eats = 0;
	def->philos[index].t_started = &def->t_started;
	def->philos[index].t_die = def->t_die;
	def->philos[index].t_eat = def->t_eat;
	def->philos[index].t_sleep = def->t_sleep;
	def->philos[index].id = index;
	def->philos[index].mtx_print_lock = &(def->mtx_print_lock);
	def->philos[index].mtx_stop = &(def->mtx_stop);
	def->philos[index].stop = &def->stop;
	def->philos[index].l_fork = &(def->forks[index]);
	def->philos[index].r_fork = &(def->forks[(index + 1) % def->n_philo]);
	if (!mtx_action(&(def->philos[index].mtx_meal_lock), INIT, def))
	{
		//WHAT TO DO IF ERROR?
		return (0);
	}
	return (1);
}

bool	create_philo(t_default *def)
{
	size_t	i;

	def->philos = (t_philo *)malloc(sizeof(t_philo) * def->n_philo);
	if (!def->philos)
	{
		print_err_free_def(def, ERR_MALLOC);
		return (0);
	}
	i = 0;
	while (i < def->n_philo)
		init_philo(def, i++);
	return (1);
}

bool	create_fork(t_default *def)
{
	size_t	i;

	def->forks = malloc(sizeof(t_mtx) * def->n_philo);
	if (!def->forks)
	{
		print_err_free_def(def, ERR_MALLOC);
		return (0);
	}
	i = 0;
	while (i < def->n_philo)
	{
		if (!mtx_action(&def->forks[i], INIT, def))
		{
			free_fork_index(def, i);
			return (0);
		}
		i++;
	}
	return (1);
}

bool	create_default(int argc, char **argv, t_default **def)
{
	*def = (t_default *)malloc(sizeof(t_default));
	if (!def)
		return ((bool)ft_putstr_fd_return(ERR_MALLOC, STDERR_FILENO, 0));
	(*def)->stop = 0;
	(*def)->n_philo = ft_atoi(argv[1]);
	(*def)->t_die = ft_atoi(argv[2]);
	(*def)->t_eat = ft_atoi(argv[3]);
	(*def)->t_sleep = ft_atoi(argv[4]);
	if (!(*def)->n_philo || !(*def)->t_die || !(*def)->t_eat \
										|| !(*def)->t_sleep)
		return ((bool)ft_putstr_fd_return(ERR_ZERO_ARG, STDERR_FILENO, 0));
	(*def)->n_eats = -1;
	if (argc == 6)
		(*def)->n_eats = ft_atoi(argv[5]);
	if (!mtx_action(&(*def)->mtx_print_lock, INIT, *def))
		return (0);
	if (!mtx_action(&(*def)->mtx_stop, INIT, *def))
		return (0);
	if (!create_fork(*def))
		return (0);
	if (!create_philo(*def))
		return (0);
	return (1);
}

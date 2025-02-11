/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:54:01 by fvargas           #+#    #+#             */
/*   Updated: 2025/02/11 18:16:41 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	philo_thread(t_default *def)
{
	size_t	i;

	i = 0;
	while (i < def->n_philo)
	{
		if (pthread_create(&def->philos[i].thread_id, NULL, philo_process, &def->philos[i]))
		{
			//ERROR:
			printf("ERROR");
			return (0);
		}
		i++;
	}
	i = 0;
	while (i < def->n_philo)
	{
		pthread_join(def->philos[i].thread_id, NULL);
		i++;
	}
	return (1);
}

bool	solution(t_default *def)
{
	set_start_time(def);
	if (!start_monitoring(def))
		return (0);
	if (!philo_thread(def))
		return (0);
	if (!end_monitoring(def))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_default	*def;

	def = NULL;
	if (argc != 5 && argc != 6)
	{
		printf("This program should receive 4 or 5 arguments.\n");
		return (1);
	}
	if (!checker_args(argv))
	{
		printf("Unable to initialize the parameters.\n");
		return (1);
	}
	if (!create_default(argc, argv, &def))
	{
		free_def(def);
		printf("Unable to initialize the parameters.\n");
		return (1);
	}
	if (!solution(def))
	{
		free_def(def);
		printf("Unable to finish the solution.\n");
		return (1);
	}
	return (0);
}

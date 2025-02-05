/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:54:01 by fvargas           #+#    #+#             */
/*   Updated: 2025/02/05 18:38:03 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	philo_thread(t_default *def)
{
	size_t	i;

	i = 0;
	while (i < def->n_philo)
	{
		if (pthread_create(&def->philos[i].thread_id, NULL, \
				&philo_process, &def->philos[i]))
		{
			return (0);
		}
		i++;
	}
	return (1);
}

bool	solution(t_default *def)
{
	if (!start_monitoring(def))
		return (0);
	if (!end_monitoring(def))
		return (0);
	def->t_die = 3;
	printf("%d\n", def->t_die);
	return (1);
}

int	main(int argc, char **argv)
{
	t_default	def;

	if (argc != 5 && argc != 6)
	{
		printf("This program should receive 4 or 5 arguments.\n");
		return (1);
	}
	if (!checker_args(argv))
		return (1);
	if (!create_default(argc, argv, &def))
	{
		printf("Program closed.\n");
		return (1);
	}
	solution(&def);
	return (0);
}

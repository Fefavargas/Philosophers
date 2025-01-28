/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:54:01 by fvargas           #+#    #+#             */
/*   Updated: 2025/01/28 15:06:36 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_default create_deafault(int argc, char **argv)
{
	t_default	def;
	size_t		i;

	i = 0;
	def.n_philosophers = ft_atoi(argv[1]);
	def.time_die = ft_atoi(argv[2]);
	def.time_eat = ft_atoi(argv[3]);
	def.time_sleep = ft_atoi(argv[4]);
	def.n_eats = 0;
	if (argc == 6)
		def.n_eats = ft_atoi(argv[5]);
	return (def);
}

int	main(int argc, char **argv)
{
	t_default	def;

	if (argc != 5 && argc != 6)
	{
		printf("This program should receive 4 or 5 arguments.\n");
		return (0);
	}
	if (!checker_args(argv))
		return (0);
	def = create_deafault(argc, argv);
	solution(def);
	return (0);
}

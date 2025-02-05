/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:54:01 by fvargas           #+#    #+#             */
/*   Updated: 2025/02/05 13:47:37 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	solution(t_default *def)
{
	// if (!start_monitoring(def))
	// 	return (0);
	// if (!end_monitoring(def))
	// 	return (0);
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

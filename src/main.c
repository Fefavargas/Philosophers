/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:54:01 by fvargas           #+#    #+#             */
/*   Updated: 2025/04/16 14:33:58 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_default	def;

	if (argc != 5 && argc != 6)
	{
		printf("This program should receive 4 or 5 arguments.\n", STDERR_FILENO);
		return (1);
	}
	if (!checker_args(argv))
	{
		printf("Unable to initialize the parameters.\n", STDERR_FILENO);
		return (1);
	}
	if (!create_default(argc, argv, &def))
	{
		printf("Unable to initialize the parameters.\n", STDERR_FILENO);
		return (1);
	}
	solution(&def);
	return (0);
}

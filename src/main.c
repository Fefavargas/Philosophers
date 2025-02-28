/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:54:01 by fvargas           #+#    #+#             */
/*   Updated: 2025/02/28 12:49:46 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_default	def;

	//def = NULL;
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
		destroy_mtx(&def);
		//free_def(&def);
		printf("Unable to initialize the parameters.\n");
		return (1);
	}
	if (!solution(&def))
	{
		destroy_mtx(&def);
		//free_def(&def);
		printf("Unable to finish the solution.\n");
		return (1);
	}
	return (0);
}

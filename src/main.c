/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:54:01 by fvargas           #+#    #+#             */
/*   Updated: 2025/02/03 17:47:46 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	solution(t_default *def)
{
	def->t_die = 3;
	printf("%d\n", def->t_die);
	return ;
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
	create_default(argc, argv, &def);
	if (&def == NULL)
	{
		printf("Program closed.\n");
		return (1);
	}
	solution(&def);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:54:01 by fvargas           #+#    #+#             */
/*   Updated: 2025/02/03 14:57:16 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	solution(t_default def)
{
	def.t_die = 3;
	printf("%d\n", def.t_die);
	return ;
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
	def = create_default(argc, argv);
	solution(def);
	return (0);
}

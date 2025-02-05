/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 19:51:59 by fvargas           #+#    #+#             */
/*   Updated: 2025/02/05 18:15:54 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_log(int philo_id, unsigned long long timestamp, t_philo_action ac)
{
	if (ac == FORK)
		printf("%d %d has taken a fork\n", timestamp, philo_id + 1);
	else if (ac == EAT)
		printf("%d %d is eating\n", timestamp, philo_id + 1);
	else if (ac == SLEEP)
		printf("%d %d is sleeping\n", timestamp, philo_id + 1);
	else if (ac == THINK)
		printf("%d %d is thinking\n", timestamp, philo_id + 1);
	else if (ac == DIE)
		printf("%d %d died\n", timestamp, philo_id + 1);
}

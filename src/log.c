/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 19:51:59 by fvargas           #+#    #+#             */
/*   Updated: 2025/02/09 18:02:52 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_log(int philo_id, unsigned long long timestamp, t_philo_action ac)
{
	if (ac == FORK)
		printf("%llu %d has taken a fork\n", timestamp, philo_id + 1);
	else if (ac == EAT)
		printf("%llu %d is eating\n", timestamp, philo_id + 1);
	else if (ac == SLEEP)
		printf("%llu %d is sleeping\n", timestamp, philo_id + 1);
	else if (ac == THINK)
		printf("%llu %d is thinking\n", timestamp, philo_id + 1);
	else if (ac == DIE)
		printf("%llu %d died\n", timestamp, philo_id + 1);
}

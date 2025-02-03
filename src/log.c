/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 19:51:59 by fvargas           #+#    #+#             */
/*   Updated: 2025/02/03 20:02:49 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_log_fork(int i, int philo, unsigned long long time, t_default def)
{
	printf("%d %d has taken fork %d\n", (time - def.t_started), philo, i + 1);
}

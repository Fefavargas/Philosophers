/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:00:23 by fvargas           #+#    #+#             */
/*   Updated: 2025/01/28 15:01:46 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS
# define PHILOSOPHERS

# include <stdio.h> //printf
# include <stddef.h> //size_of
# include <limits.h> //INT_MIN
# include <stdbool.h> //bool

// typedef struct s_philosophers
// {
    
// };

typedef struct s_default
{
    int n_philosophers;
    int time_die;
    int time_eat;
    int time_sleep;
    int n_eats;
} t_default;

//checker.c
bool	checker_args(char **argv);

//util.c
long	ft_atoi(const char *nptr);

#endif
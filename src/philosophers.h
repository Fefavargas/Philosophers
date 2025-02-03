/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:00:23 by fvargas           #+#    #+#             */
/*   Updated: 2025/02/03 15:23:51 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS
# define PHILOSOPHERS

# include <stdio.h> //printf
# include <stddef.h> //size_of
# include <limits.h> //INT_MIN
# include <stdbool.h> //bool

# define ERR_MALLOC		"ERROR: malloc() failed. \n"
// typedef struct s_philosophers
// {

// };

typedef struct s_default
{
	int	n_philo;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	n_eats;
	t_philo	*philos;
}	t_default;

typedef struct s_philo
{
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	n_eats;
}	t_philo;

//create.c
t_default create_default(int argc, char **argv);

//checker.c
bool	checker_args(char **argv);

//erroc.c
void	print_err_free_def(t_default def, char *msg);

//util.c
long	ft_atoi(const char *nptr);
void	ft_putstr_fd(char *s, int fd);

#endif
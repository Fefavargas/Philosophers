/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:00:23 by fvargas           #+#    #+#             */
/*   Updated: 2025/02/03 17:09:37 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS
# define PHILOSOPHERS

# include <unistd.h> //write
# include <stdio.h> //printf //DELETE
# include <stddef.h> //size_of
# include <limits.h> //INT_MIN
# include <stdlib.h> //malloc, free
# include <stdbool.h> //bool
# include <pthread.h> // Thread functions, like pthread_create() etc.

# define ERR_MALLOC		"ERROR: malloc() failed.\n"
# define ERR_MTX		"ERROR: mutex function failed.\n"

typedef pthread_mutex_t		t_mtx; // Abbreviation for 'pthread_mutex_t'

typedef enum e_mtx_action
{
	INIT = 1,
	LOCK,
	UNLOCK,
	DESTROY
}	t_mtx_action;

typedef struct s_fork
{
	int		fork_id;
	t_mtx	fork;
}	t_fork;

typedef struct s_philo
{
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	n_eats;
}	t_philo;

typedef struct s_default
{
	int		n_philo;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		n_eats;
	t_philo	*philos;
	t_fork	*forks;
}	t_default;

//create.c
t_default	create_default(int argc, char **argv);

//checker.c
bool		checker_args(char **argv);

//erroc.c
void		print_err_free_def(t_default *def, char *msg);

//mutex.c
bool		mtx_action(t_mtx *mutex, t_mtx_action action, t_default *def);

//util.c
long		ft_atoi(const char *nptr);
void		ft_putstr_fd(char *s, int fd);

#endif

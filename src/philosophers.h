/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefa <fefa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:00:23 by fvargas           #+#    #+#             */
/*   Updated: 2025/02/04 20:19:39 by fefa             ###   ########.fr       */
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
# include <sys/time.h> // gettimeofday()
# include <pthread.h> // Thread functions, like pthread_create() etc.

# define ERR_MALLOC		"ERROR: malloc() failed.\n"
# define ERR_MTX		"ERROR: mutex function failed.\n"
# define ERR_GET_TIME	"ERROR: gettimeofday() function.\n"
# define ERR_TIME_DIE	"ERROR: Time_die should be bigger than Time_eat + Time_sleep.\n"
# define ERR_ZERO_ARG	"ERROR: Argument ZERO not allowed for this variable.\n"
# define ERR_INTEGER	"ERROR: There is an argument that is not a positive integer\n"

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
	int		id;
	t_mtx	fork;
}	t_fork;

typedef struct s_philo
{
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					n_eats;
	bool				dead;
	pthread_mutex_t		*meal_lock;
	unsigned long long	last_meal;
}	t_philo;

typedef struct s_default
{
	unsigned int		n_philo;
	unsigned int		t_die;
	unsigned int		t_eat;
	unsigned int		t_sleep;
	unsigned int		t_think;
	unsigned int		n_eats;
	t_philo				*philos;
	t_fork				*forks;
	unsigned long long	t_started;
}	t_default;

//create.c
bool	create_default(int argc, char **argv, t_default *def);

//checker.c
bool	checker_args(char **argv);

//erroc.c
void	print_err_free_def(t_default *def, char *msg);
void	free_fork_index(t_default *def, size_t index);

//log.c
void	print_log_fork(int i, int philo, unsigned long long time, t_default def);

//mutex.c
bool	mtx_action(t_mtx *mutex, t_mtx_action action, t_default *def);

//time.c
unsigned long long	get_time(void);

//util.c
long	ft_atoi(const char *nptr);
void	ft_putstr_fd(char *s, int fd);
int	ft_putstr_fd_return(char *s, int fd, int error);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:00:23 by fvargas           #+#    #+#             */
/*   Updated: 2025/04/16 14:49:45 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h> //write
# include <stdio.h> //printf
# include <stddef.h> //size_of
# include <limits.h> //INT_MIN
# include <stdlib.h> //malloc, free
# include <stdbool.h> //bool
# include <sys/time.h> // gettimeofday()
# include <pthread.h> // Thread functions, like pthread_create() etc.
# define ERR_MALLOC		"ERROR: malloc() failed.\n"
# define ERR_MTX		"ERROR: mutex function failed.\n"
# define ERR_GET_TIME	"ERROR: gettimeofday() function.\n"
# define ERR_ZERO_ARG	"ERROR: Argument ZERO not allowed for this variable.\n"
# define ERR_INTEGER	"ERROR: There is an argument that is not a \
positive integer\n"

typedef pthread_mutex_t		t_mtx; // Abbreviation for 'pthread_mutex_t'
typedef struct s_default	t_default;

typedef enum e_mtx_action
{
	INIT = 1,
	LOCK,
	UNLOCK,
	DESTROY
}	t_mtx_action;

typedef enum e_philo_action
{
	FORK = 1,
	EAT,
	SLEEP,
	THINK,
	DIE
}	t_philo_action;

/**
	pthread_t			thread_id; -> each philo has a thread_id
	int					id; -> index starting from 0
	unsigned long long	*t_started; -> pointer to the start time
	unsigned int		t_die; -> pointer to the die time
	unsigned int		t_eat; -> pointer to the eat time
	unsigned int		t_sleep; -> pointer to the sleep time
	int					n_eats; -> number of times the philo has eaten
	unsigned long long	last_meal; -> last time the philo ate
	t_mtx				*r_fork; -> pointer to the right fork
	t_mtx				*l_fork; -> pointer to the left fork
 */
typedef struct s_philo
{
	pthread_t			thread_id;
	int					id;
	int					n_eats;
	unsigned long long	last_meal;
	t_mtx				*r_fork;
	t_mtx				*l_fork;
	t_default			*def;
}	t_philo;

/** 
	size_t				n_philo; -> number of philosophers
	unsigned int		t_die; -> time to die
	unsigned int		t_eat; -> time to eat
	unsigned int		t_sleep; -> time to sleep
	int					n_eats; -> number of times each philosopher must eat
	t_philo				*philos; -> array of philosophers
	t_mtx				*forks; -> array of forks
	t_mtx				mtx_print_lock; -> mutex for print lock
	t_mtx				mtx_meal_lock; -> mutex for stop
	bool				stop; -> stop variable
	unsigned long long	t_started; -> start time
	pthread_t			monitor; -> monitor thread
*/
typedef struct s_default
{
	size_t				n_philo;
	unsigned int		t_die;
	unsigned int		t_eat;
	unsigned int		t_sleep;
	int					n_eats;
	t_philo				*philos;
	t_mtx				*forks;
	t_mtx				mtx_print_lock;
	t_mtx				mtx_meal_lock;
	bool				stop;		
	unsigned long long	t_started;
	pthread_t			monitor;
}	t_default;

//action,c 
void				action_forks(t_mtx *fork, t_philo *philo, t_mtx_action ac);
void				pick_drop_forks(t_philo *philo, t_mtx_action ac);
void				ft_eat(t_philo *philo);
void				ft_sleep(t_philo *philo);
void				ft_think(t_philo *philo);

//create.c
bool				create_default(int argc, char **argv, t_default *def);

//checker.c
bool				checker_args(char **argv);

//erroc.c
void				print_err_free_def(t_default *def, char *msg);
void				destroy_mtx(t_default *def);

//log.c
void				ft_is_dead(t_default *def, t_philo *philo);
void				print_log(t_philo *philo, t_philo_action ac);

//monitor.c
void				*monitor(void *arg);

//mutex.c
int					mtx_action(t_mtx *mutex, t_mtx_action action);
void				mtx_stop(t_default *def);
bool				get_mtx_stop(t_default *def);

//process.c
void				solution(t_default *def);

//time.c
unsigned long long	get_time(void);
void				set_start_time(t_default *def);

//util.c
long				ft_atoi(const char *nptr);
void				ft_putstr_fd(char *s, int fd);
int					ft_putstr_fd_return(char *s, int fd, int error);

#endif

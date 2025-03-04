/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:10:56 by dalabrad          #+#    #+#             */
/*   Updated: 2025/03/04 11:14:32 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h> //		write, usleep
# include <stdio.h> //		printf
# include <stdlib.h> //		malloc,free
# include <stdbool.h> //	bool type
# include <sys/time.h> //	gettimeofday
# include <limits.h> //		INT_MAX
# include <pthread.h> //	threads : create, join, detach
//							mutex:	  init, destroy, lock, unlock
# include <errno.h> //		error constants

# define DEBUG_MODE 0
# define INPUT_ERROR 1
# define ARG_NEG 2
# define UNVALID_ARG 3
# define ARG_TOO_BIG 4
# define ARG_TOO_SMALL 5
# define NO_PHILO_ERROR 6
# define MALLOC_ERROR 7
# define WRONG_OPCODE 8

// Colors for the output : nice for debugging 

# define R   "\033[1;31m"  // Bold Red
# define G   "\033[1;32m"  // Bold Green
# define Y   "\033[1;33m"  // Bold Yellow
# define B   "\033[1;34m"  // Bold Blue
# define M   "\033[1;35m"  // Bold Magenta
# define C   "\033[1;36m"  // Bold Cyan
# define W   "\033[1;37m"  // Bold White
# define RST "\033[0m"     // Reset Color

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}	t_opcode;

typedef enum e_time_code
{
	SECOND,
	MILISECOND,
	MICROSECOND,
}	t_time_code;

typedef enum e_philo_status
{
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED,
}	t_philo_status;

typedef pthread_mutex_t	t_mutex; // For ease of read.

//	FORK STRUCT ()
typedef struct s_fork
{
	t_mutex	fork;
	int		fork_id;
}	t_fork;

typedef struct s_data	t_data;

// PHILOSOPHER STRUCT
typedef struct s_philo
{
	int			id;
	long		meal_counter;
	bool		full;
	long		last_meal_time; //time from last meal
	pthread_t	thread_id; // A philosopher is a thread!!!
	t_fork		*first_fork;
	t_fork		*second_fork;
	t_data		*data;
	t_mutex		philo_mutex; // Useful for races with the monitor
}	t_philo;

/* 	
 * 	GLOBAL DATA STRUCT 
 *	=======================
 *	./philo 5 600 300 200 [6] , [Optional]
*/
struct s_data
{
	long		n_philo;
	long		time_die;
	long		time_eat;
	long		time_sleep;
	long		n_limit_meals; // Optional!! , flag -1 if not entered in argv.
	long		start_simulation; // time of start of simulation.
	bool		end_simulation; // true when a philo dies or all philos full
	bool		all_threads_ready; // For a synchronizated start of the feast.
	t_fork		*forks; // Array of forks
	t_philo		*philos; //Array of philosophers
	t_mutex		table_mutex; //Avoid races while reading from data table
	t_mutex		write_mutex; //To print philo status thread safe.
	pthread_t	monitor; // Monitor to check for dead philos.
	long		nbr_threads_running;
};

//	src/philo_error_msg.c
int		error_msg(int err_id);
void	error_exit(int err_id);
int		error_str(char	*str);
void	error_str_exit(char	*str);

//	src/philo_parse_input.c
int		parse_input(t_data *table, char **argv);

//	src/philo_safe_functions.c
int		safe_mutex_handle(t_mutex *mutex, t_opcode opcode);
void	safe_thread_handle(pthread_t *thread, void *(*routine)(void *),
			void *data, t_opcode opcode);

//	src/philo_data_inint.c
int		data_init(t_data *table);

//	src/philo_getters_setters.c
void	set_bool(t_mutex *mutex, bool *dest, bool value);
bool	get_bool(t_mutex *mutex, bool *bool_ptr);
bool	simulation_finished(t_data *table);
void	set_long(t_mutex *mutex, long *dest, long value);
long	get_long(t_mutex *mutex, long *long_ptr);

//	src/philo_synchro_utils.c
void	wait_all_threads(t_data *table);
bool	all_threads_running(t_mutex *mutex, long *nbr_threads, long nbr_philos);
void	increase_long(t_mutex *mutex, long *dest);
void	desynchronize_philo(t_philo *philo);

//	src/philo_time_utils.c
long	get_time(t_time_code time_code);
void	precise_usleep(long usec, t_data *table);

//	src/philo_write_utils.c
void	write_status(t_philo_status status, t_philo *philo, bool debug);

//	src/philo_actions.c
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo, bool before_simulation);

//	src/philo_routines.c
void	*one_philo(void *data);
void	*philo_routine(void *data);
void	*monitor_feast(void *data);

//	src/philo_feast_simulation.c
void	feast_simulation(t_data *table);

//	src/philo_clean.c
void	clean(t_data *table);

#endif
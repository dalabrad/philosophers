/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:10:56 by dalabrad          #+#    #+#             */
/*   Updated: 2025/02/13 20:36:20 by dalabrad         ###   ########.fr       */
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

# define INPUT_ERROR 1
# define ARG_NEG 2
# define UNVALID_ARG 3
# define ARG_TOO_BIG 4
# define ARG_TOO_SMALL 5
# define NO_PHILO_ERROR 6
# define MALLOC_ERROR 7
# define WRONG_OPCODE 8

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
}	t_philo;

/* 	
 * 	GLOBAL DATA STRUCT 
 *	=======================
 *	./philo 5 600 300 200 [6] , [Optional]
*/
struct s_data
{
	size_t	n_philo;
	size_t	time_die;
	size_t	time_eat;
	size_t	time_sleep;
	long	n_limit_meals; // Optional!! , flag -1 if not entered in argv.
	long	start_simulation;
	bool	end_simulation; // true when a philo dies or all philos full
	bool	all_threads_ready; // For a synchronizated start of the feast.
	t_fork	*forks; // Array of forks
	t_philo	*philos; //Array of philosophers
};

//	src/philo_error_msg.c
void	error_exit(int err_id);
void	error_str_exit(char	*str);

//	src/philo_parse_input.c
void	parse_input(t_data *table, char **argv);

//	src/philo_safe_functions.c
void	*safe_malloc(size_t bytes);
void	safe_mutex_handle(t_mutex *mutex, t_opcode opcode);
void	safe_thread_handle(pthread_t *thread, void *(*routine)(void *),
			void *data, t_opcode opcode);

//	src/philo_data_inint.c
void	data_init(t_data *table);

#endif
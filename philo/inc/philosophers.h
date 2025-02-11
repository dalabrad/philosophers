/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:10:56 by dalabrad          #+#    #+#             */
/*   Updated: 2025/02/11 10:07:44 by dalabrad         ###   ########.fr       */
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

# define INPUT_ERROR 1
# define ARG_NEG 2
# define UNVALID_ARG 3
# define ARG_TOO_BIG 4
# define ARG_TOO_SMALL 5
# define NO_PHILO_ERROR 6

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
	long		meals_counter;
	bool		full;
	long		last_meal_time; //time from last meal
	pthread_t	thread_id; // A philosopher is a thread!!!
	t_fork		*left_fork;
	t_fork		*right_fork;
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
	t_fork	*forks; // Array of forks
	t_philo	*philos; //Array of philosophers
};

//	src/philo_error_msg.c
int		error_msg(int err_id);
void	error_exit(int err_id);

//	src/philo_parse_input.c
void	parse_input(t_data *table, char **argv);

#endif
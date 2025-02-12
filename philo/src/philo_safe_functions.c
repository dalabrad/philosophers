/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_safe_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:53:51 by dalabrad          #+#    #+#             */
/*   Updated: 2025/02/12 20:19:52 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

/*
 * This function is a malloc with protection.  Allocates size_t bytes and if 
 * allocation fails exits the program with the error message of MALLOC_ERROR.
*/
void	*safe_malloc(size_t bytes)
{
	void	*rtrn;

	rtrn = malloc(bytes);
	if (!rtrn)
		error_exit(MALLOC_ERROR);
	return (rtrn);
}

/*
 * This function handles the errors of pthread_mutex_[action]() functions. Needs
 * int status which is the return of the pthread_mutex_[init/dest/lock/unlock]()
 * and opcode to know which function it's beeing used.
*/
static void	handle_mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	else if (status == EINVAL && (opcode == LOCK || opcode == UNLOCK))
		error_str_exit("The value specified by mutex is invalid.\n");
	else if (status == EINVAL && opcode == INIT)
		error_str_exit("The value specified by attr is invalid.\n");
	else if (status == EDEADLK)
		error_str_exit("A deadlock would occur if the thread is blocked" \
			"waiting for mutex.\n");
	else if (status == EPERM)
		error_str_exit("The current thread does not hold a lock on mutex.\n");
	else if (status == ENOMEM)
		error_str_exit("Cannot allocate enough memory to create another" \
			"mutex.\n");
	else if (status == EBUSY)
		error_str_exit("Mutex is locked");
}

/*
 * This function performs a protected pthread_mutex usage, is able to:
 * 				ACTION						 	OPCODE
 * 		---------------------------	  |		--------------------
 * 		~ pthread_mutex_init()		--->		INIT
 * 		~ pthread_mutex_destroy()	--->		DESTROY
 * 		~ pthread_mutex_lock()		--->		LOCK
 * 		~ pthread_mutex_unlock()	--->		UNLOCK
 * And handles the possible errors caused when calling the former functions.
*/
void	safe_mutex_handle(t_mutex *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (opcode == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (opcode == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (opcode == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		error_exit(WRONG_OPCODE);
}

/*
 * This function handles the errors of pthread_[action]() functions. Needs
 * int status which is the return of the pthread_[create/join/detach]()
 * and opcode to know which of those functions it's beeing used.
*/
static void	handle_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	else if (status == EAGAIN)
		error_str_exit("No resources to create another thread.\n");
	else if (status == EPERM)
		error_str_exit("The caller does not have appropiate permission.\n");
	else if (status == EINVAL && opcode == CREATE)
		error_str_exit("The value specified by attr is unvalid.\n");
	else if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
		error_str_exit("The value specified by thread is not joinable.\n");
	else if (status == ESRCH)
		error_str_exit("No thread could be found corresponding to that" \
			"specified by the given thread ID, thread.\n");
	else if (status == EDEADLK)
		error_str_exit("A deadlock was detected or the value of thread" \
			"specifies the calling thread.\n");
}

/*
 * This function performs a protected pthread usage, is able to:
 * 				ACTION						 	OPCODE
 * 		---------------------------	  |		--------------------
 * 		~ pthread_create()			--->		CREATE
 * 		~ pthread_join()			--->		JOIN
 * 		~ pthread_detach()			--->		DETACH
 * 	And handles the possible errors caused when calling the former functions.
*/
void	safe_thread_handle(pthread_t *thread, void *(*routine)(void *),
	void *data, t_opcode opcode)
{
	if (opcode == CREATE)
		handle_thread_error(pthread_create(thread, NULL, routine, data),
			opcode);
	else if (opcode == JOIN)
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (opcode == DETACH)
		handle_thread_error(pthread_detach(*thread), opcode);
	else
		error_exit(WRONG_OPCODE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:05:20 by dalabrad          #+#    #+#             */
/*   Updated: 2025/02/07 12:44:39 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philosophers.h"

int main(int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
    {
		ft_putstr_fd("Introduced wrong number of arguments\n", 2);
		return (EXIT_FAILURE);
    }
	else
	{
		printf("Number of philosophers : %s\n", argv[1]);
		printf("Time to die : %s\n", argv[2]);
		printf("Time to eat : %s\n", argv[3]);
		printf("Time to sleep : %s\n", argv[4]);
		if (argc == 6)
			printf("N times philo must eat (opt) : %s\n", argv[5]);
	}
	return (EXIT_SUCCESS);
}

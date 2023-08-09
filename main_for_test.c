/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_for_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 20:15:11 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/09 18:58:06 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libc.h>
#include "memory_leak_detector.h"

__attribute__((destructor))
static void	destructor(void)
{
	print_report();
}

int main()
{
	char	*str = malloc(123);
	int pid = fork();
	if (pid == 0)
	{
		char	*str = malloc(123);
		printf("Hello form child\n");
	}
	else
	{
		printf("Hello form Parrent\n");
	}
}

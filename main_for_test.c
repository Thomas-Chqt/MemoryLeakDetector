/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_for_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 20:15:11 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/10 17:28:41 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory_leak_detector.h"

__attribute__((destructor))
static void	destructor(void)
{
	print_report();
}

int main()
{
	while(1)
	{
		void *ptr = malloc(100);
		if (ptr == NULL)
			exit(0);
		free(ptr);
		printf("No error\n");
	}
	return 0;
}

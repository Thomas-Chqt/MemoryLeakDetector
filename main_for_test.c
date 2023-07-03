/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_for_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 20:15:11 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/03 03:07:47 by tchoquet         ###   ########.fr       */
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
	void *a = malloc(100);
	void *b = malloc(100);
	void *c = ft_calloc(1, 400);
	void *d = ft_calloc(1, 400);

	free(b);
	free(d);
	return 0;
}

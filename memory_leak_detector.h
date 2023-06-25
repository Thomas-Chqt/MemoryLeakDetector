/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_leak_detector.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:04:06 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/25 19:17:47 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_LEAK_DETECTOR_H
# define MEMORY_LEAK_DETECTOR_H

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <libft.h>

# define MAX_ALLOCATIONS 100000
# define WARN(msg, line, file) (printf("Warning %s:%d: %s\n", file, line, msg))

/* 
Data Structure to keep track of memory allocations
*/
typedef struct s_mem {
    size_t address;
    size_t size;
    uint32_t line;
	char	*file;
} t_mem;

typedef struct s_data {
    t_mem mem[MAX_ALLOCATIONS];
    size_t total_allocated_size;
    size_t total_free_size;
} t_data;

void *_malloc(size_t size, uint32_t line, char *file);
void *_ft_calloc(size_t count, size_t size, uint32_t line, char *file);
void _free(void *ptr, uint32_t line, char *file);
void print_report();

# ifndef NO_REDEFINE

// redefine allocator functions
#  define malloc(size) _malloc(size, __LINE__, __FILE__)
#  define free(ptr) _free(ptr, __LINE__, __FILE__)

# endif // NO_REDEFINE

#endif // MEMORY_LEAK_DETECTOR_H



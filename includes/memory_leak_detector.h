/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_leak_detector.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:04:06 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/03 03:06:11 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_LEAK_DETECTOR_H
# define MEMORY_LEAK_DETECTOR_H

# include <libc.h>

# include <libft.h>

typedef struct s_mem
{
    size_t		address;
    size_t		size;
    t_uint32	line;
	char		*file;

} t_mem;


void *_malloc(size_t size, t_uint32 line, char *file);
void *_ft_calloc(size_t count, size_t size, t_uint32 line, char *file);
void _free(void *ptr);
void print_report();

# ifndef NO_REDEFINE

#  define malloc(size) _malloc(size, __LINE__, __FILE__)
#  define ft_calloc(count, size) _ft_calloc(count, size, __LINE__, __FILE__)
#  define free(ptr) _free(ptr)

# endif // NO_REDEFINE

#endif // MEMORY_LEAK_DETECTOR_H



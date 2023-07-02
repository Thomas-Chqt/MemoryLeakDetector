/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_leak_detector.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:04:06 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/02 20:33:27 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_LEAK_DETECTOR_H
# define MEMORY_LEAK_DETECTOR_H

# include <libft.h>

typedef struct s_mem
{
    size_t		address;
    size_t		size;
    t_uint32	line;
	char		*file;

} t_mem;


void *_malloc(size_t size, t_uint32 line, char *file);
void _free(void *ptr, t_uint32 line, char *file);
void print_report();

# ifndef NO_REDEFINE

#  define malloc(size) _malloc(size, __LINE__, __FILE__)
#  define free(ptr) _free(ptr, __LINE__, __FILE__)

# endif // NO_REDEFINE

#endif // MEMORY_LEAK_DETECTOR_H



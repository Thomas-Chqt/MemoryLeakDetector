/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_leak_detector.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:04:06 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/03 15:29:22 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_LEAK_DETECTOR_H
# define MEMORY_LEAK_DETECTOR_H

# include <libc.h>

void *_malloc(size_t size, uint32_t line, char *file);
void *_ft_calloc(size_t count, size_t size, uint32_t line, char *file);
void _free(void *ptr);
void print_report();

# ifndef NO_REDEFINE

#  define malloc(size) _malloc(size, __LINE__, __FILE__)
#  define free(ptr) _free(ptr)

# endif // NO_REDEFINE

#endif // MEMORY_LEAK_DETECTOR_H



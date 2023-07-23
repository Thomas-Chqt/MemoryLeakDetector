/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_leak_detector.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:04:06 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/23 14:40:28 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_LEAK_DETECTOR_H
# define MEMORY_LEAK_DETECTOR_H

void *_malloc(unsigned long size, unsigned int line, char *file);
void *_ft_calloc(unsigned long count, unsigned long size, unsigned int line, char *file);
void _free(void *ptr);
void print_report();

# ifndef NO_REDEFINE

#  define malloc(size) _malloc(size, __LINE__, __FILE__)
#  define free(ptr) _free(ptr)

# endif // NO_REDEFINE

#endif // MEMORY_LEAK_DETECTOR_H



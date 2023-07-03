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

typedef enum e_bool			t_bool;
typedef struct s_list		t_list;

enum e_bool { false = 0, true = 1 };

struct s_list
{
	void	*data;
	t_list	*next;
};

typedef struct s_mem
{
    size_t		address;
    size_t		size;
    uint32_t	line;
	char		*file;

} t_mem;


void *_malloc(size_t size, uint32_t line, char *file);
void *_ft_calloc(size_t count, size_t size, uint32_t line, char *file);
void _free(void *ptr);
void print_report();

# ifndef NO_REDEFINE

#  define malloc(size) _malloc(size, __LINE__, __FILE__)
#  define free(ptr) _free(ptr)

# endif // NO_REDEFINE

#endif // MEMORY_LEAK_DETECTOR_H



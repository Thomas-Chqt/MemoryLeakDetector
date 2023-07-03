
#define NO_REDEFINE

#include "memory_leak_detector.h"

t_list	*allocated_mem = NULL;
size_t	g_total_alloc = 0;
size_t	g_total_free = 0;

void print_free(void *mem)
{
    printf("Memory leak at line %d in file %s: (%lu bytes)\n", ((t_mem *)mem)->line, ((t_mem *)mem)->file, ((t_mem *)mem)->size);
	free(mem);
}

void insert(size_t address, size_t size, t_uint32 line, char *file)
{
	t_mem	*new_mem = malloc(sizeof(t_mem));
	if (new_mem == NULL)
	{
		printf("Malloc error int leak detector");
		return ;
	}
	*new_mem = (t_mem){
		.address = address,
		.size = size,
		.line = line,
		.file = file
	};
	ft_lstadd_front(&allocated_mem, ft_lstnew(new_mem));
	g_total_alloc += size;
}

t_bool adress_is_equad(void *mem, void *searched)
{
	if (((t_mem *)mem)->address == (size_t)searched)
	{
		g_total_free += ((t_mem *)mem)->size;
		return (true);
	}
	return (false);
}

void print_report() {
    printf("\nLeak Summary\n");
    printf("Total Memory allocated %lu bytes\n", g_total_alloc);
    printf("Total Memory freed     %lu bytes\n", g_total_free);
    printf("Memory Leaked          %lu bytes\n\n", g_total_alloc - g_total_free);

	ft_lstclear(&allocated_mem, &print_free);
	printf("\n");
}

void *_malloc(size_t size, t_uint32 line, char *file)
{
    void *ptr = malloc(size);
	if (ptr == NULL)
		printf("Allocation error line %d int file %s", line, file);
	else
    	insert((size_t)ptr, size, line, file);
    return ptr;
}

void *_ft_calloc(size_t count, size_t size, t_uint32 line, char *file)
{
	void *ptr = ft_calloc(count, size);
	if (ptr == NULL)
		printf("Allocation error line %d int file %s", line, file);
	else
    	insert((size_t)ptr, count * size, line, file);
    return ptr;
}

void _free(void *ptr)
{
	lst_delete_if(&allocated_mem, &free, &adress_is_equad, ptr);
    free(ptr);
}

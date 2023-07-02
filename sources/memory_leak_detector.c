
#define NO_REDEFINE

#include "memory_leak_detector.h"

t_list	*allocated_mem = NULL;
size_t	g_total_alloc = 0;
size_t	g_total_free = 0;

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


int erase(size_t address)
{
	t_list	**watched = &allocated_mem;

	while (*watched != NULL)
	{
		if (((t_mem *)(*watched)->data)->address == address)
			
		watched = watched->next;
	}
    g_total_free += 
    return 0;
}

void print_report() {
    printf("\nLeak Summary\n");
    printf("Total Memory allocated %lu bytes\n", g_data.total_allocated_size);
    printf("Total Memory freed     %lu bytes\n", g_data.total_free_size);
    printf("Memory Leaked          %lu bytes\n\n", g_data.total_allocated_size - g_data.total_free_size);

    if (g_data.total_free_size != g_data.total_allocated_size) {
        printf("Detailed Report\n");
        for (int i=0; i<MAX_ALLOCATIONS; i++) {
            if (g_data.mem[i].address != 0) {
                printf("Memory leak at line %d in file %s: (%lu bytes)\n", g_data.mem[i].line, g_data.mem[i].file, g_data.mem[i].size);
            }
        }
    }
}

void *_malloc(size_t size, t_uint32 line, char *file)
{
    void *ptr = malloc(size);
	if (ptr = NULL)
		printf("Allocation error line %d int file %d", line, file);
	else
    	insert((size_t)ptr, size, line, file);
    return ptr;
}

void _free(void *ptr, t_uint32 line, char *file)
{
	erase((size_t)ptr, line, file);
    free(ptr);
}

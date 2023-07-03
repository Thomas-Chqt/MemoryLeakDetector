
#define NO_REDEFINE

#include "memory_leak_detector.h"

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

t_list	*allocated_mem = NULL;
size_t	g_total_alloc = 0;
size_t	g_total_free = 0;

void	mem_lstadd_front(t_list **lst, t_list *new)
{
	if (lst == NULL)
		return ;
	new->next = (*lst);
	(*lst) = new;
}

t_list	*mem_lstnew(void *content)
{
	t_list	*new_lst;

	new_lst = malloc(sizeof(t_list));
	if (new_lst == NULL)
		return (NULL);
	new_lst->data = content;
	new_lst->next = NULL;
	return (new_lst);
}

void	mem_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*watched;
	t_list	*temp;

	watched = *lst;
	while (watched != NULL)
	{
		del(watched->data);
		temp = watched->next;
		free(watched);
		watched = temp;
	}
	(*lst) = NULL;
}

void	mem_lst_delete_if(t_list **head, void (*del)(void *),
			t_bool (*condition)(void *, void *), void *data)
{
	t_list	*current;
	t_list	*temp;

	if (head == NULL || (*head) == NULL || condition == NULL || del == NULL)
		return ;
	if (condition((*head)->data, data) == true)
	{
		temp = *head;
		*head = (*head)->next;
		del(temp->data);
		free(temp);
	}
	if (head == NULL || (*head) == NULL)
		return ;
	current = *head;
	while (current->next != NULL)
	{
		if (condition(current->next->data, data) == true)
		{
			temp = current->next;
			current->next = current->next->next;
			del(temp->data);
			free(temp);
		}
		else
			current = current->next;
	}
}

void print_free(void *mem)
{
    printf("Memory leak at line %d in file %s: (%lu bytes)\n", ((t_mem *)mem)->line, ((t_mem *)mem)->file, ((t_mem *)mem)->size);
	free(mem);
}

void insert(size_t address, size_t size, uint32_t line, char *file)
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
	mem_lstadd_front(&allocated_mem, mem_lstnew(new_mem));
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

	mem_lstclear(&allocated_mem, &print_free);
	printf("\n");
}

void *_malloc(size_t size, uint32_t line, char *file)
{
    void *ptr = malloc(size);
	if (ptr == NULL)
		printf("Allocation error line %d int file %s", line, file);
	else
    	insert((size_t)ptr, size, line, file);
    return ptr;
}

void _free(void *ptr)
{
	mem_lst_delete_if(&allocated_mem, &free, &adress_is_equad, ptr);
    free(ptr);
}

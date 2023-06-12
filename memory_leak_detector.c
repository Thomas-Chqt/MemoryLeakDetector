
#define NO_REDEFINE

#include "memory_leak_detector.h"

t_data	g_data;

/**
 * Find a memory by its address
 * 
 * @return: Pointer to memory
*/
t_mem *find_by_address(size_t address) {
    for (uint32_t i=0; i<MAX_ALLOCATIONS; i++) {
        if (g_data.mem[i].address == address)
            return &g_data.mem[i]; // as soon as find return
    }

    // otherwise return null
    return NULL;
}


/**
 * insert memory allocated with size
*/
void insert(size_t address, size_t size, uint32_t line, char *file) {
    // check for null
    if (address == 0) {
        WARN("Memory allocation failed", line, file);
        return;
    }

    t_mem *mem = find_by_address(0);
    // if the return value is null we need to increase the MAX_ALLOCATIONS value
    if (mem == NULL) {
        WARN("Max allocations reached", line, file);
        return;
    }

    // save all the allocation info
    mem->address = address;
    mem->size = size;
    mem->line = line;
	mem->file = file;
    g_data.total_allocated_size += size;
}

/**
 * Remove the memory allocation
 * 
 * @return: -1 on failure else 0
*/
int erase(size_t address, uint32_t line, char *file) {
    if (address == 0) {
        WARN("Tried to free a null ptr", line, file);
        return -1;
    }

    t_mem *mem = find_by_address(address);
    // if the address is not found we assume it is already deleted
    if (mem == NULL) {
        WARN("Double free detected", line, file);
        return -1;
    }

    // set address to null and update info
    mem->address = 0;
    g_data.total_free_size += mem->size;
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

// Override allocation functions
void *_malloc(size_t size, uint32_t line, char *file) {
    void *ptr = malloc(size);

    // insert to memory data
    insert((size_t)ptr, size, line, file);

    return ptr;
}

void _free(void *ptr, uint32_t line, char *file) {
    // erase memory data
    if (erase((size_t)ptr, line, file) == 0)
        free(ptr);
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "heap.h"

#define memerror  "Out of memory, program terminated."
#define ptrerror  "Invalid pointer, program terminated."

struct __node
{
    void *location;
    struct __node *next;
};

static struct __node *record = NULL;

static void print_memerror(void)
{
    puts(memerror);
    exit(0x1);
}

static void print_ptrerror(void)
{
    puts(ptrerror);
    exit(0x2);
}

static void push_location(void *__loc)
{
    struct __node *new_node = (struct __node *) malloc(sizeof(void *));
    if(new_node == NULL)
    {
        print_memerror();
    }
    new_node->location = __loc;
    new_node->next = record;
    record = new_node;
}


void *heap_malloc(size_t __size)
{
    void *heap_ptr = malloc(__size);
    if(heap_ptr != NULL)
    {
        push_location(heap_ptr); 
    }   
    else
    {
        print_memerror();
    }
    return heap_ptr;
}


void *heap_realloc(void *__prev, size_t __size)
{
    if(__prev == NULL)
    {
        return heap_malloc(__size);
    }
    bool found = false;    
    void *heap_ptr =  realloc(__prev, __size);
    if(heap_ptr != NULL)
    {
        for(struct __node *current = record; current; current = current->next)
        {
            if(current->location == __prev)
            {
                found = true;
                current->location = heap_ptr;
                break;
            }
        }
    }
    else
    {
        print_memerror();
    }
    if(found == false)
    {
        print_ptrerror();
    }
    return heap_ptr;
}


void *heap_calloc(size_t __nmemb, size_t __size)
{
    void *heap_ptr = calloc(__nmemb, __size);
    if(heap_ptr != NULL)
    {
        push_location(heap_ptr); 
    }   
    else
    {
        print_memerror();
    }
    return heap_ptr;
}


void heap_free(void *__ptr)
{
    if(__ptr == NULL)
    {
        return;
    }
    bool found = false;
    for(struct __node *current = record; current; current = current->next)
    {
        if(current->location == __ptr)
        {
            found = true;
            free(current->location);
            current->location = NULL;
            break;
        }
    }
    if(found == false)
    {
        print_ptrerror();
    }
}


void show_record(void)
{
    if(record == NULL)
    {
        puts("No memory blocks have been allocated.");
        return;
    }
    else
    {
        printf("\nYour heap allocations starts at\n%c", '{');
    }
    size_t i = 0;
    for(struct __node *current = record; current; current = current->next, i++)
    {
        if(current->location != NULL)
        {
            if(i && i % 4 == 0)
            {
                printf("%s", "\n ");
            }
            printf("%p, ", current->location);
        }
    }
    i ? printf("\033[2D%c\n", '}') : 0; 
}


void tear_down(void)
{
    struct __node *tmp = NULL;
    for(; record; )
    {
        if(record->location != NULL)
        {
            free(record->location);
        }
        tmp = record;
        record = record->next;
        free(tmp);
    }
}


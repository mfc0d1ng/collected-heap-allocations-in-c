#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "heap.h"

#define memerror  "Out of memory, program terminated."
#define ptrerror  "Invalid pointer, program terminated."

struct location
{
    void *heap_location;
    unsigned char status;
}__attribute__((packed));

struct __node
{
    struct location location;
    struct __node *next;
}__attribute__((packed));

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

static void push_location(struct location *__loc)
{
    struct __node *new_node = (struct __node *) malloc(sizeof(struct __node));
    if(new_node == NULL)
    {
        print_memerror();
    }
    new_node->location = *__loc;
    new_node->next = record;
    record = new_node;
}


void *heap_malloc(size_t __size)
{
    void *heap_ptr = malloc(__size);
    if(heap_ptr != NULL)
    {
        struct location __loc = {heap_ptr, __alloc};
        push_location(&__loc); 
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
            if(current->location.heap_location == __prev)
            {
                found = true;
                current->location.status = __alloc;
                current->location.heap_location = heap_ptr;
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
        struct location __loc = {heap_ptr, __alloc};
        push_location(&__loc); 
    }   
    else
    {
        print_memerror();
    }
    return heap_ptr;
}


void heap_free(void *__add)
{
    if(__add == NULL || (record == NULL))
    {
        return;
    }
    bool found = false;
    for(struct __node *current = record; current; current = current->next)
    {
        if((current->location.heap_location == __add) && current->location.status == __alloc)
        {
            found = true;
            current->location.status = __freed;
            free(current->location.heap_location);
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
    size_t i = 0;
    printf("%c", '{');
    for(struct __node *current = record; current; current = current->next, i++)
    {
        if(i && i % 4 == 0)
        {
            puts("");
        }
        if(current->location.status == __alloc)
        {
            printf("%p, ", current->location.heap_location);
        }
    }
    printf("\033[2D%c", '}');
}


void tear_down(void)
{
    if(record == NULL)
    {
        return;
    }
    struct __node *tmp = NULL;
    for(; record; )
    {
        if(record->location.status == __alloc)
        {
            free(record->location.heap_location);
        }
        tmp = record;
        record = record->next;
        free(tmp);
    }
}


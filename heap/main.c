#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"


int main(void)
{
    char *ptr = (char *) heap_malloc(12);
    memcpy(ptr, "Hello world", 12); 

    puts(ptr);

    ptr = (char *) heap_realloc(ptr, 20);
    memcpy(ptr, "Hello world, Again.", 20);

    puts(ptr);

    // show_record();    
    
    /*  
        // Try this
        free(ptr);
    */
    
    /*
    for(int i = 0; i < 1000000; i++)
    {
        heap_malloc(20);
    }
    show_recored();
    */
    return EXIT_SUCCESS;
}

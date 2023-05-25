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
    
    return EXIT_SUCCESS;
}

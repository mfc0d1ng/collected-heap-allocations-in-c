# Collected heap allocations in C language 
This implementation is based on the familiar malloc(), calloc(), realloc() and free(); it allocates the memory in heap and keeps tracking the starting addresses of the newly memory allocations in order to collect all the starting addresses in a record, so all the allocated memory blocks can be freed after the program execution (this is the scenario by default).


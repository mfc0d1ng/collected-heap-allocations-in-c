#ifndef HEAP_H
#define HEAP_H

#define  __freed     0x0
#define  __alloc     0x1

/* Allocate SIZE bytes of memory. */
extern void *heap_malloc(size_t __size);

/* Re-allocate the previously allocated block in PREV, making the new block SIZE bytes long. */
extern void *heap_realloc(void *__prev, size_t __size);

/* Allocate NMEMB elements of SIZE bytes each, all initialized to 0.  */
extern void *heap_calloc(size_t __nmemb, size_t __size);

/* Free a block allocated by `heap_malloc', `heap_realloc' or `heap_calloc'.  */
extern void heap_free(void *__add);

/* Show the starting addresses of all the allocated blocks. */
extern void show_recored(void);

/* Free all the memory blocks. */
extern void tear_down(void);

#define _Hardcoded_mode_   0x0
#define _Automatic_mode_   0x1
#define _tear_down_       _Automatic_mode_
#if     _tear_down_  ==   _Automatic_mode_
void tear_down(void) __attribute__((destructor));
#endif

#endif

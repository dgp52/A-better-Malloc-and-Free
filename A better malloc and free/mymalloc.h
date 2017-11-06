//Deepkumar Patel, dgp52, 145005704
//Viraj Patel, vjp60, 168001058

#ifndef MYMALLOC_H
#define MYMALLOC_H

//Modified Malloc and Free, 
//shows error along with file and line number
#define malloc( x ) mymalloc( x, __FILE__, __LINE__)
#define free( x ) myfree( x, __FILE__, __LINE__)

//Prototypes of mymalloc and myfree
void* mymalloc(unsigned int size,char *file, int line);
void myfree(void *p, char *file, int line);

//Structure of the block.
//It contains following meta data
// isallocated = is block allocated or free?
//		1 is allocated
//		0 is free
// size = stores the size of allocated memory or the available size for allocation
// *previous = points to previous node
// *next = points to next node 
typedef struct MemoryBlock {
	int isallocated;
	int size;
	struct MemoryBlock *previous;
	struct MemoryBlock *next;
} MemBlock;

#endif

//Deepkumar Patel, dgp52, 145005704
//Viraj Patel, vjp60, 168001058

#include "mymalloc.h"
#include <stdio.h>
//Simulate and set the size of total memory
#define MAIN_MEMORY_SIZE 5000
//Get Struct Size
#define STRUCT_SIZE sizeof(MemBlock)
//Virtual/Fake Memory, it acts as fake heap
static char virtualMem[MAIN_MEMORY_SIZE];
//Create the head pointer and set the value to NULL
static MemBlock* head = NULL;
//Check to see if the head is created or not
static int isHeadCreated = 0;
//enum Error
typedef enum {
	FREE_NULL_POINTER,
	FREE_MEMORY_NOT_ALLOCATED,
	ALLOCATE_SIZE_ZERO,
	ALLOCATE_SIZE_TOOBIG
} ErrorType;
//Errors
void showError (ErrorType errorIs, void* memLocation, unsigned int size, char* file, int line) {
	switch(errorIs){
		case FREE_NULL_POINTER:
			fprintf(stderr, "Error: Free Failed, cannot free a NULL pointer. FILE: '%s', LINE: '%d'\n", file,line);
		break;
		case FREE_MEMORY_NOT_ALLOCATED:
			fprintf(stderr, "Error: Free Failed, memory @%p is not allocated. FILE: '%s', LINE: '%d'\n", memLocation, file,line);
		break;
		case ALLOCATE_SIZE_ZERO:
			fprintf(stderr, "Error: Allocation Failed, cannot allocate %d byte. FILE: '%s', LINE: '%d'\n",size, file,line);
		break;
		case ALLOCATE_SIZE_TOOBIG:
			fprintf(stderr, "Error: Allocation Failed, cannot allocate %d byte. Requested memory is too big. FILE: '%s', LINE: '%d'\n", size, file,line);
		break;
	}
}
//mymalloc
void* mymalloc(unsigned int size,char *file, int line){
	//Points to the Current block
	MemBlock *current;
	//Points to the next block
	MemBlock *next;
	//Check if the requested memory is of size 0. Throws error if size is 0.
	if(size == 0) {
		showError(ALLOCATE_SIZE_ZERO, NULL,size,file,line);
		return 0;
	}
	//create the head if its not created
	if (isHeadCreated == 0) {
		//printf("virtualMem Location is: %d\n",virtualMem);
		//Initially if the requested size is too big then throw an error
		if (size > MAIN_MEMORY_SIZE - STRUCT_SIZE) {
			showError(ALLOCATE_SIZE_TOOBIG,NULL,size,file,line);
			return 0;
		}
		//Create the head
		head = (MemBlock*)virtualMem;
		//printf("Head Location is: %d\n",head);
		head -> isallocated = 1;
		head -> size = size;
		head -> previous = NULL;
		head -> next = NULL;
		//Create the next pointer
		next = (MemBlock*)(virtualMem + size + STRUCT_SIZE);
		//Set head's next to next
		head -> next = next;
		//printf("next Location is: %d\n",next);
		next -> isallocated = 0;
		next -> size = MAIN_MEMORY_SIZE - STRUCT_SIZE*2 - size;
		next -> previous = head;
		next -> next = NULL;
		isHeadCreated = 1;
		//Return Pointer to isallocated block
		//printf("Malloc in Heap: %d\n\n",virtualMem + STRUCT_SIZE );
		return virtualMem + STRUCT_SIZE;
	} else {// head is created
	//set current to head
	current = head;
	//printf("Current Location: %d\n", current);
	//while the current is not equal to NULL
	while(current != NULL){
		//Check if the current block is isallocated or not, if isallocated then move to next block OR
		//Check if the requested size is bigger than current.size
		if(current -> isallocated == 1 || size > current -> size){
			//Move to next block
			current = current -> next;
            //printf("Current Location after Next: %d\n", current);
		} else if (size + STRUCT_SIZE >= current -> size){
			//Check if total of size and meta data is greate or equal to current.size
			//current.size can fit the requested size
			current -> isallocated = 1;
			//printf("Malloc in small: %d\n\n",((char*)current) + STRUCT_SIZE);
			return ((char*)current) + STRUCT_SIZE;
		} else {
			//Set the next pointer to free and change size
			next = (MemBlock*)(((char*)current) + size + STRUCT_SIZE);
			next -> isallocated = 0;
			next -> size = current -> size - size - STRUCT_SIZE;
			next -> previous = current;
			next -> next = current -> next;
			//Allocate the current block
			if(current -> next != NULL){
				current -> previous = next;
			}
			current -> isallocated = 1;
			current -> size = size;
			current -> next = next;
			//printf("Malloc in long: %d\n\n",((char*)current) + STRUCT_SIZE);
			//Return Pointer to isallocated block
			return ((char*)current) + STRUCT_SIZE;
			} 
		}
	}
	showError(ALLOCATE_SIZE_TOOBIG,NULL,size,file,line);
	return NULL;
}
//myfree
void  myfree(void *p, char *file, int line) {
    //printf("myfree\n");
     //Points to start of allocated memory or Meta data
    MemBlock *sBlock;
    //Keep track of current block
    MemBlock *current;
    //points to previous block
    MemBlock *previous;
    //Points to next block
    MemBlock *next;
    //If the pointer to be freed is NULL then show error
    if (p == NULL){
        showError(FREE_NULL_POINTER,NULL, 0,file,line);
        return;
    }
    //Go through blocks and check if the current is allocated and its pointing to sBlock
    sBlock = (MemBlock*)(((char*)p) - STRUCT_SIZE);
    for (current = head; current != NULL; current = current->next){
        if (current->isallocated == 1 && current == sBlock )
            break;
    }
    //If current is Null, then show error
    if (current == NULL){
    	showError(FREE_MEMORY_NOT_ALLOCATED,p, 0,file,line);
        return;
    }
    //Change previous and next pointer
    previous = current->previous;
    next = current->next;
    //Merge the free memory depending on following cases
    //if previous block is free
    if (previous == NULL) {
    	current->isallocated = 0;
        if (current->next->isallocated == 0){
            current->size = current->size + current->next->size + STRUCT_SIZE;
            current->next = current->next->next;
            if (next->next != NULL){
                next->next->previous = current;
            }
        }
        return;
    } else if (next == NULL) {
    	//if next block is free
    	current->isallocated = 0;
        if (previous->isallocated == 0){
            previous->size = previous->size + current->size + STRUCT_SIZE;
            previous->next = current->next;
        }
        return;
    } else if (previous == NULL && next == NULL){
    	//Both previous and next is free
    	current->size = MAIN_MEMORY_SIZE - STRUCT_SIZE;
        current->isallocated = 0;
        return;
    } else {
    	//finally check following cases
    	//Check if previous is allocated
    	if(previous->isallocated == 1){
    		current->size = current->size + current->next->size + STRUCT_SIZE;
            current->next = current->next->next;
            if (next->next != NULL){
                next->next->previous = current;
            }
            return;
    	} else if (next->isallocated == 1) {	
    		//Next is allocated
    		previous->size = previous->size + current->size + STRUCT_SIZE;
            previous->next = current->next;
            next->previous = previous;
    	} else {
    		//Both blocks are allocated, nothing to merge
    		return;
    	}
    }
}

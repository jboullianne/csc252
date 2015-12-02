/*
Well I tried to implement an implicit free list.
As you can see by the driver test, it failed miserably.

I use the standard boundary tags, that are used to get the size and allocation bit of the block.
I also use the method of "first fit" when looking for a block.

I Understand the concept of how the list will work, but 
I'm encountering bugs in areas I don't quite understand how to fix.

Plain and simply, I ran out of time. May I have better luck next time.

**SOURCES**
"Computer Systems: A Programmers Perspective"
    - Chapter 9.9 Dynamic Memory Allocation
    (used part of their implicit list implementation)

 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/
team_t team = {
    /* Team name */
    "JBTeam",
    /* First member's full name */
    "Jean-Marc Boullianne",
    /* First member's email address */
    "jboullia@u.rochester.edu",
    /* Second member's full name (leave blank if none) */
    "",
    /* Second member's email address (leave blank if none) */
    ""
};

/* 16 byte alignment */
#define ALIGNMENT 16

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT) -1) & ~(ALIGNMENT- 1))

#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))

/*
All of my macros defined below...
Some gathered from "Computer Systems, A programmer's persepctive"
*/

//Returns the max of two numbers
#define WSIZE   4       /* Word and header/footer size (bytes) */
#define DSIZE   8       /* Double word size (bytes) */
#define CHUNKSIZE   (1<<12)     /* Extend heap by this amount (bytes) */
#define FULLBLOCK   32


#define MAX(x,y) ((x) > (y)? (x) : (y))

/* Pack a size and allocated bit into a word */
#define PACK(size, alloc) ((size) | (alloc))

/* Read and write a word at address ptr */
#define GET(ptr)    (*(size_t *) (ptr))
#define PUT(ptr, value) (*(size_t *) (ptr) = (value))

/* Read the size and allocated fields from address ptr */
#define GET_SIZE(ptr)   (GET(ptr) & ~0x7)
#define GET_ALLOC(ptr)  (GET(ptr) & 0x1)

/* Given block ptr, compute address of its header and footer */
#define HDRP(ptr)   ((char *) (ptr) - WSIZE)
#define FTRP(ptr)   ((char *) (ptr) + GET_SIZE(HDRP(ptr)) - DSIZE)

#define NEXT_BLKP(bp)   ((char *)(bp) + GET_SIZE(( (char *)(bp) - WSIZE) ))
#define PREV_BLKP(bp)   ((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE)))


void* extend_heap(size_t);
void* find_fit(size_t);
void place(void*, size_t);
void* coalesce(void* bp);

void* heap_ptr;

/* 
 * mm_init - initialize the malloc package.
 */
int mm_init(void) {

    if((heap_ptr = mem_sbrk(4*WSIZE)) == (void *) -1)
        return -1;

    PUT(heap_ptr, 0);
    PUT(heap_ptr + (1 * WSIZE), PACK(DSIZE, 1));
    PUT(heap_ptr + (2 * WSIZE), PACK(DSIZE, 1));
    PUT(heap_ptr + (3 * WSIZE), PACK(0, 1));
    heap_ptr += (2*WSIZE);

    if(extend_heap(CHUNKSIZE/WSIZE) == NULL)
        return -1;

    return 0;
}

/* 
 * mm_malloc - Allocate a block by incrementing the brk pointer.
 *     Always allocate a block whose size is a multiple of the alignment.
 */
void *mm_malloc(size_t size) {
    
    size_t asize;
    size_t extendsize;
    char *bp;

    if(size == 0)       /* Ignore zero memory requests */
        return NULL;

    if(size <= DSIZE)
        asize = 2*DSIZE;
    else
        asize = ALIGN(size);

    if((bp = find_fit(asize)) != NULL){ //Finds "first fit" for size requested
        place(bp, asize);
        return bp;
    }

    extendsize = MAX(asize, CHUNKSIZE); //Increase heap if not enough room
    if((bp = extend_heap(extendsize/WSIZE)) == NULL)
        return NULL;
    place(bp, asize);
    return bp;

}

/*
 * mm_free - Freeing a block does nothing.
 */
void mm_free(void *ptr) {

    size_t size = GET_SIZE(HDRP(ptr));

    PUT(HDRP(ptr), PACK(size, 0));
    PUT(FTRP(ptr), PACK(size, 0));
    //coalesce(ptr);

}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
void *mm_realloc(void *ptr, size_t size) {
    

    if(ptr == NULL)
        return mm_malloc(size);
    if(size == 0){
        mm_free(ptr);
        return NULL;
    }

    return NULL;
}

/*
 * extend_heap - Used to extend heap by size_t
 */
void* extend_heap(size_t words){

    char *bp;
    size_t size;

    size = (words % 2) ? (words +1) * WSIZE : words * WSIZE;
    if((long) (bp = mem_sbrk(size)) == -1)
        return NULL;

    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
    PUT(HDRP(NEXT_BLKP(bp)), PACK(0,1));
    return bp;
    //return coalesce(bp);
}

void* coalesce(void *bp){

    size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
    size_t size = GET_SIZE(HDRP(bp));

    if(prev_alloc && next_alloc)            /* Both Adjacent Blocks Are Allocated */
        return bp;

    else if(prev_alloc && !next_alloc){     /* Next is not allocated */ 
        size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
        PUT(HDRP(bp), PACK(size,0));
        PUT(FTRP(bp), PACK(size,0));
    }

    else if(!prev_alloc && next_alloc){     /* Prev is not allocated */
        size += GET_SIZE(HDRP(PREV_BLKP(bp)));
        PUT(FTRP(bp), PACK(size,0));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        bp = PREV_BLKP(bp);
    }

    else{                                   /* Both are not allocated */
        size += GET_SIZE(HDRP(PREV_BLKP(bp))) + GET_SIZE(FTRP(NEXT_BLKP(bp)));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
        bp = PREV_BLKP(bp);
    }

    return bp;
}

void* find_fit(size_t size){

    void* temp = heap_ptr;
    while(*NEXT_BLKP(temp) > 0){    //Keep on going while not footer block
        if(GET_ALLOC(temp) && (GET_SIZE(temp) > size))
            return temp;
        temp = NEXT_BLKP(temp);
    }
    return NULL; //Didn't find a block so returning NULL
}

void place(void* bp, size_t size){
    size_t oldsize = GET_SIZE(HDRP(bp));
    //If enough minimum space to split the block
    if(oldsize - size >= (DSIZE)){ //Splitting block to better utilize memory
        PUT(HDRP(bp), PACK(size, 1));
        PUT(FTRP(bp), PACK(size, 1));
        bp = NEXT_BLKP(bp);
        PUT(HDRP(bp), PACK(oldsize - size, 0));
        PUT(FTRP(bp), PACK(oldsize - size, 0));
        //coalesce(bp);
    }

    //Internal fragmentation could occur... if its not exactly equal
    else{
        PUT(HDRP(bp), PACK(oldsize, 1));
        PUT(FTRP(bp), PACK(oldsize, 1));
    }
}
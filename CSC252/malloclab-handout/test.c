#include <stdio.h>

typedef struct node{
    struct node *next, *prev;
}node;

#define GET_NODE(ptr)   ((node *)ptr)
#define NEW_NODE(ptr, left, right)  (*((node *)ptr) = (node) {(left), (right)})
#define NODE_SIZE   sizeof(node)

int main(){
	
	printf("%lu", NODE_SIZE);

	printf("\n%lu\n", sizeof(char*));

}
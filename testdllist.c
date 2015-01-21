/// @author Andrew Dunkum avd1379
/// path in git repo: Project2/testdllist.c
/// path on CS machine: Courses/CS243/Homeworks/mechanics-code/Project2/
/// testdllist.c

// for printf/NULL
#include <stdio.h>
// for true and false
#include <stdbool.h>
// for the other DlList_T functions and DlList_T typedeff
#include "dlListExtra.h"
// for the DlList_T functions
#include "dlList.h"
// for allocating space for the c-strings
#define LINE_LENGTH 20

// so I can use it in main
static void printList(DlList_T);

/// the main function of the testing file. Creates a DlList_T and uses all the
/// functions in it. Destroys the list after the program is done, so no leaks 
/// should occur
/// @return 1 if an error occurs, otherwise 0
int main(void) {
	// allocate the space for the c-string
	char * first = (char*) malloc(sizeof(char) * LINE_LENGTH);
	// copy 'first' into the space
	strcpy(first, "first");
	// allococate the space for the c-string
	char * second = (char*) malloc(sizeof(char) * LINE_LENGTH);
	// put 'second' in it	
	strcpy(second, "second");
	// make the DlList_T
	DlList_T list = dll_create();
	// test dll_empty with empty DlList_T
	printf("After creating the list, is the list empty? %s\n", 
	dll_empty(list) ? "true" : "false");
	// put first in the DlList_T
	dll_append(list, first);
	// test dll_empty with non-empty DlList_T
	printf("After appending first to the list, is the list empty? %s\n",
	dll_empty(list) ? "true" : "false");
	// print the DlList_T
	printList(list);
	// put second in the DlList_T
	dll_append(list, second);
	// test dll_size
	printf("After appending second to the list, the size is: %d\n", 
	dll_size(list));
	// print the DlList_T
	printList(list);
	// allocate the space for the c-string
	char * random = (char*) malloc(sizeof(char) * LINE_LENGTH);
	// copy 'random' in the space	
	strcpy(random, "random");
	// put random at index 1
	dll_insert_at(list, 1, random);
	printf("random was inserted at index 1\n");
	// print the DlList_T
	printList(list);
	// allocate space for the c-string
	char * word = (char*) malloc(sizeof(char) * LINE_LENGTH);
	// copy 'word' into the space	
	strcpy(word, "word");
	// set the c-string at index 0 to word
	dll_set(list, 0, word);
	// free the space for first
	free(first);
	printf("The c-string at position 0 was reset to 'word'\n");
	// print the DlList_T	
	printList(list);
	// test dll_index
	printf("The index of 'random' is: %d\n", dll_index(list, random));
	// test dll_move_to	
	dll_move_to(list, 2);
	printf("The cursor was moved to index 2\n");
	// test dll_get_current
	printf("The current Node is holding: %s\n", (char*)
	dll_get_current(list));
	// test dll_prev	
	dll_prev(list);
	printf("The cursor was moved back 1\n");
	// test dll_get_current with valid position
	printf("The current Node is holding: %s\n", (char*)
	dll_get_current(list));
	// test dll_next past end	
	dll_next(list);
	dll_next(list);
	printf("The cursor was moved forward 2\n");
	// tests dll_get_current with invalid position
	printf("The current Node is holding: %s\n", 
	(char*)dll_get_current(list));
	// go the the begining	
	dll_move_to(list, 0);
	// test dll_prev past begining
	dll_prev(list);	
	printf("The cursor was moved to index 0, then back 1\n");
	// again tests dll_get_current with invalid position
	printf("The current Node is holding: %s\n", 
	(char*)dll_get_current(list));
	// test dll_has_next
	printf("Is the cursor at a valid position? %s\n", dll_has_next(list) ?
	"true" : "false");
	// test dll_pop
	char * toRemove = dll_pop(list, 0);	
	printf("The item at index 0 was removed, which was: %s\n", toRemove);
	// free the item removed
	free(toRemove);
	// print the list
	printList(list);
	// test dll_clear	
	dll_clear(list);
	printf("The list was cleared\n");
	// print the empty list
	printList(list);
	// destroy the list so no leaks should occur
	dll_destroy(list);
	printf("The list was destroyed\n");
	// nothing went wrong so return 0
	return 0;
}	

/// a simple helper function to just print the current state of the list
/// @param list the list to print
void printList(DlList_T list) {
	// go to the beginging of the list
	dll_move_to(list, 0);
	printf("List is: {");
	// if the list isn't empty
	if(!dll_empty(list)) {
		// print the first item and move forward
		printf("%s", dll_next(list));
	}
	// while there are more items to print
	while(dll_has_next(list)) {
		// print the item and move forward
		printf(",%s", dll_next(list));
	}
	printf("}\n");
}

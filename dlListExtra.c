/// The implementation file for my additional double-linked list functionality.
/// includes implementation for the four functions that I wanted to use for 
/// mrEd, as outlined in dlListExtra.h 
/// @author Andrew Dunkum avd1379
/// path in git repo: Project2/dlListExtra.c
/// path on CS machine: Courses/CS243/Homeworks/mechanics-code/Project2/
/// dlListExtra.c

// for NULL
#include <stdlib.h>
// for true and false
#include <stdbool.h>
// for other DlList_T functions, and the the DlList_T typedeff
#include "dlListExtra.h"
// for the original DlList_T functions
#include "dlList.h"

/// the function that returns the data from the current Node, or the Node at
/// the "cursor". If the current position in lst is invalid, NULL is returned
/// @param lst the DlList_T to get the data from
/// @return the data, or NULL if invalid position
void * dll_get_current(DlList_T lst) {
	// if the cursor is at a valid position, return the data there
	if(dll_has_next(lst)) {
		return lst->current->data;
	}
	// otherwise return NULL
	return NULL;
}

/// the function that returns the index of the cursor, or at what index the
/// current position is. If lst is empty then -1 is returned
/// @param lst the DlList_t in question
/// @return the position in the DlList_T, or -1 if empty or invalid index
int dll_get_current_index(DlList_T lst){
	// if lst is empty
	if(dll_empty(lst)) {
		// signal this by returning -1
		return -1;
	}
	// if lst is at an invalid index
	if(!dll_has_next(lst)) {
		// signal this by returning -1
		return -1;
	}
	// if lst isn't empty, get the index of the current Node
	return dll_index(lst, lst->current->data);
}

/// the function that checks if the next position in the DlList_T is valid.
/// @param lst the DlList_T in question
/// @return 0 if it is not valid, otherwise 1
int dll_is_next_valid(DlList_T lst) {
	// check for empty list	
	if(!dll_empty(lst)) {
		// if the current Node is NULL
		if(!dll_has_next(lst)) {
			// return 0 (false)			
			return 0;
		}
		// if the next Node is NULL
		if(lst->current->next == NULL) {
			// return 0 (false)			
			return 0;
		// if the next Node is not NULL
		} else {
			// return 1 (true)
			return 1;
		}
	}
	// the empty list returns 0 (false)
	return 0;
}

/// the function that checks if the prevous position in the DlList_T is valid
/// @param lst the DlList_T in question
/// @return 0 if it is not valid, otherwise 1
int dll_is_prev_valid(DlList_T lst) {
	// check for empty list
	if(!dll_empty(lst)) {
		// if the current Node is NULL
		if(!dll_has_next(lst)) {
			// return 0 (false)			
			return 0;
		}
		// if the previous Node is NULL
		if(lst->current->prev == NULL) {
			// return 0 (false)
			return 0;
		// if the previous Node is not NULL
		} else {
			// return 1 (true)
			return 1;
		}
	}
	// the empty list returns 0 (false)
	return 0;
}

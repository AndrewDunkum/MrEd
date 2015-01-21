/// The dlList implementation. This file has the implementation for most of the
/// double-linked list functions. Also implements the struct definition for
/// DlList_T struct. 
/// @author Andrew Dunkum avd1379
/// path in git repo: Project2/dlList.c
/// path on CS machine: Courses/CS243/Homeworks/mechanics-code/Project2/
/// dlList.c

// for true and false
#include <stdbool.h>
// for NULL
#include <stdlib.h>
// for other DlList_T functions and the DlList_T typedeff
#include "dlListExtra.h"
// now the list has been implemented
#define _DLL_IMPL_
// now you can include the .h file
#include "dlList.h"

/// the function that creates an instance of the DlList_T struct, initializes
/// it, and returns it. The list and all Nodes are dynamically allocated
/// @return a new empty DlList_T
DlList_T dll_create(void) {
	// alocate the size needed for the list
	DlList_T newList = (DlList_T)  malloc(sizeof(struct list));
	// start the count at 0
	newList->count = 0;
	// first and current are NULL since it is empty
	newList->first = NULL;
	newList->current = NULL;
	// return the struct
	return newList;
}

/// the function that takes a given DlList_T and deallocates any memory used
/// for it or any of it's Nodes. After this function is called the pointer
/// passed to it as a parameter will no longer be valid. 
/// @param lst the DlList_T to deallocate
void dll_destroy(DlList_T lst) {
	// free all the nodes
	dll_clear(lst);
	// free the actual list
	free(lst);
}

/// the function that takes a given DlList_T and deallocates any memory used
/// only by it's Nodes. This means that after this call the pointer passed to
/// the function will still be valid, it just will point to an empty DlList_T.
/// It will be as if dll_create had just been called. 
/// @param lst the DlList_T to clear out
void dll_clear(DlList_T lst) {
	bool dll_empty(DlList_T);
	void * dll_pop(DlList_T, int);
	// to hold the data to free
	void * data;
	// as long as the list still has elements
	while(!dll_empty(lst)) {
		// pop off and free the memory for the first c-string
		data = dll_pop(lst, 0);	
		free(data);
	}
}

/// the function that moves the internal cursor of the given DlList_T to the 
/// given index. These indecies are 0-based. This function also returns whether
/// or not the move was succesful
/// @param lst the DlList_T to move the cursor on
/// @param index the index to move the cursor to
/// @return true if it was successful, otherwise false
bool dll_move_to(DlList_T lst, int index) {
	// index out of range
	if(index >= lst->count) {
		return false;
	}
	// invalid index
	if(index < 0) {
		return false;
	}
	// start at the begining
	lst->current = lst->first;
	// move 'index' amount of times
	for(int i = 0; i < index; i++) {
		// move to the next Node
		lst->current = lst->current->next;
	}
	// didn't fail, so return true
	return true;
}

/// the function that returns whether or not the cursor currently refers to a
/// valid position. One would probably assume this function returned whether or
/// not the next Node is a valid position, but this is not the case. 
/// @param lst the DlList_T in question
/// @return 0 if it does not point to a valid position, otherwise 1
int dll_has_next(DlList_T lst) {
	// if the current Node is not NULL
	if(lst->current != NULL) {
		// true
		return 1;
	}
	// otherwise false
	return 0;
}

/// the function that moves the cursor forward regardless of if this next
/// position is valid. It also returns a pointer to the data that was stored
/// in the old cursor position before it was moved. The client does not get 
/// ownership of this data however, it is expected that the user willl not 
/// free what is returned from this function
/// @param lst the DlList_T to manipulate
/// @return a pointer to the data that the old current node refers to
void * dll_next(DlList_T lst) {
	// if you already aren't at a valid index
	if(!dll_has_next(lst)) {
		// signal this with NULL
		return NULL;
	}	
	// get the data of the current node
	void * data = lst->current->data;
	// increment the current Node
	lst->current = lst->current->next;
	// return the data
	return data;
}

/// the function that moves the cursor back regardless of if this previous
/// position is valid. It also returns a pointer to the data that was stored
/// in the old cursor position before it was moved. The client does not get 
/// ownership of this data however, it is expected that the user willl not 
/// free what is returned from this function
/// @param lst the DlList_T to manipulate
/// @return a pointer to the data that the old current node refers to
void * dll_prev(DlList_T lst) {
	// if you already aren't at a valid index	
	if(!dll_has_next(lst)) {
		// signal this with NULL
		return NULL;
	}
	// get the the data of the current node
	void * data = lst->current->data;
	// move the current node back
	lst->current = lst->current->prev;
	// return the data
	return data;
}

/// the function that returns the number of elements current held in the 
/// DlList_T struct.
/// @param lst the DlList_T that you want the size of
/// @return the number of elements in this DlList_T
int dll_size(DlList_T lst) {
	// count is the same as size
	return lst->count;
}

/// the function that adds the data passed to it to the end of the DlList_T 
/// also passed to it. The data should be a pointer, and should point to a 
/// valid spot in heap memory. This method asssumes that this is done and does
/// not malloc for the data, only for the Node
/// @param lst the DlList_T to append to
/// @param data the data to be held in the new Node
void dll_append(DlList_T lst, void * data) {
	// move to the last node
	dll_move_to(lst, (dll_size(lst)-1));
	// make room for the new node
	Node * newNode = (Node*) malloc(sizeof(Node));
	// set the data for the new node
	newNode->data = data;
	// the new node will point forward to NULL
	newNode->next = NULL;
	// if the list is empty
	if(lst->count == 0) {
		// the current and first will be the new node
		lst->current = newNode;
		lst->first = newNode;
		// will also point back to NULL in a previously empty list
		newNode->prev = NULL;
		// increment the count
		lst->count++;
	// if the list is not empty
	} else {
		// make the node after the last node point to the new Node
		lst->current->next = newNode;
		// the new node should point back to the old last Node 
		newNode->prev = lst->current;
		// cursor should be moved to the new entry
		lst->current = newNode;
		// increment the counter
		lst->count++;
	}
}

/// the funciton to insert a data item at a given index. The data must be a
/// pointer to a c-string that has previously been allocated on the heap. This
/// function only allocates space for new Nodes, not for the c-strings. 
/// @param lst the DlList_T to be inserted into
/// @param index the index to put the data at (0 based) if index is invlid
/// nothing is done
/// @param data the data (a pointer) to put in the new Node at index
void dll_insert_at(DlList_T lst, int index, void * data) {
	// if the index isn't valid
	if(index < 0 || index > dll_size(lst)){
		// return without doing anything		
		return;
	}	
	// make room for the new node
	Node * newNode = (Node*) malloc(sizeof(Node));
	// set the data for the new Node
	newNode->data = data;
	// inserting to empty list
	if(dll_empty(lst)) {
		// the only valid index for an empty DlList_T is 0
		if(index != 0) {
			// if anything else was given, return without doing
			// anything
			return;
		}
		// it is the only node, so it is first and current
		lst->current = newNode;
		lst->first = newNode;
		// points both ways to NULL
		newNode->prev = NULL;
		newNode->next = NULL;
	// inserting to non-empty list	
	} else {
		// inserting into the front
		if(index == 0){
			// points forward to old first node
			newNode->next = lst->first;
			// points back to NULL
			newNode->prev = NULL;
			// old first node points back to new node
			lst->first->prev = newNode;
			// first and current will be new node
			lst->first = newNode;
			lst->current = newNode;
		//inserting into the end is the same as appending 
		} else if(index == lst->count) {
			// since this is the end, the new Node points forward
			// to NULL
			newNode->next = NULL;
			// go to the end
			dll_move_to(lst, index-1);
			// old last node points to the new node
			lst->current->next = newNode;
			// new node points back to old last node
			newNode->prev = lst->current;
			// make the new node the current node
			lst->current = newNode;
		// inserting into the middle of the list
		} else {
			// go the index before the spot to insert to
			dll_move_to(lst, index-1);
			// make the node ahead of where the new node will go 
			// point back to the new node
			lst->current->next->prev = newNode;
			// new node points forward to the node ahead of where 
			// it will go
			newNode->next = lst->current->next;
			// make the new Node point back to the current Node
			newNode->prev = lst->current;
			// node before points forward to newNode
			lst->current->next = newNode;
			// make the current node the new node
			lst->current = newNode;
		}
	}
	// increment the counter
	lst->count++;
} 

/// the function to get the data from the Node at the given index. The Node
/// is not removed or deallocated, but the pointer is not free'd. The pointer
/// should not be free'd by the user, this function assumes the user will not
/// @param lst the DlList_T to get an item from
/// @param index the position from which you want the data. Assumed to be in 
/// the proper range
/// @return the pointer held in the Node at the given index
void * dll_get(DlList_T lst, int index) {
	// make sure the index is in range
	if(index < 0 || index >= dll_size(lst)) {
		// if not signal this by returning NULL		
		return NULL;
	}
	// keep a record of where the cursor was
	int originalPosition = dll_get_current_index(lst);
	// go to the given index
	dll_move_to(lst, index);
	// get the data there
	void * data = lst->current->data;
	// put the cursor back where you found it
	dll_move_to(lst, originalPosition);
	// return the data
	return data;
}

/// the function to swap out the data in a Node at the given position. with
/// the data given to this function. The data supplied must be a pointer to 
/// a c-string that was previously allocated on the heap. This function will
/// not allocate any space since the Node already exists
/// @param lst the DlList_T to change the data of one of it's Nodes
/// @param index the position of the Node to be manipulated, assumed to be in
/// the proper range
/// @return the old data from the Node
void * dll_set(DlList_T lst, int index, void * data) {
	// make sure the index is in range
	if(index < 0 || index >= dll_size(lst)) {
		// if not signal this by returning NULL
		return NULL;
	}
	// keep a record of where the cursor was
	int originalPosition = dll_get_current_index(lst);
        // go to the given index
        dll_move_to(lst, index);
	// get the old data
	void * oldData = lst->current->data;
        // set the data there
        lst->current->data = data;
        // put the cursor back where you found it
        dll_move_to(lst, originalPosition);
	// return a pointer to the new node
	return oldData;
}

/// the funciton to remove a Node from a given position, and return the 
/// data stored in it. Although the Node is free'd, the pointer to the data
/// will still be valid, and the user of this function must free the data 
/// themselves
/// @param lst the list to pop a Node out of
/// @param index the index of the Node, assumed to be in range
/// @return the data stored in the Node removed
void * dll_pop(DlList_T lst, int index) {
	// make sure the index is in range
	if(index < 0 || index >= dll_size(lst)) {
		// if not signal this by returning NULL		
		return NULL;
	}
	// the data to be removed
	void * data = NULL;
	// removal of the only element
	if(lst->count == 1) {
		// get the data
		data = lst->first->data;
		// free the actual Node
		free(lst->first);
		// make first and current NULL, it is an empty list
		lst->first = NULL;
		lst->current = NULL;
		// decrement the counter
		lst->count--;
		// return the data
		return data;
	}
	// removal of the first element 
	if(index == 0) {
		// get the data
		data = lst->first->data;
		Node * toFree = lst->first;
		// make the next node the 'first' node
		lst->first = lst->first->next;
		free(toFree);
		// move the cursor to the next element
		lst->current = lst->first;
		// make the first Node have a NULL previous Node
		lst->first->prev = NULL;
		// decrement the count
		lst->count--;
		// return the data
		return data;
	}
	// removal of the last element
	if(index == lst->count - 1) {
		// move to the node before the last node
		dll_move_to(lst, index-1);
		// get the data from the last node
		data = lst->current->next->data;
		free(lst->current->next);
		// set the current node's next to NULL
		lst->current->next = NULL;
		// decrement the count
		lst->count--; 
		// return the data
		return data;
	}
	// removal of an element in the middle of a list
	// go to the node before the one to remove
	dll_move_to(lst, index-1);
	// get the data from the element to remove 
	data = lst->current->next->data;
	// make the node before the node to remove point forward to the node 
	// after the node to remove
	lst->current->next = lst->current->next->next;
	free(lst->current->next->prev);
	// make the node after the node to remove point back to the node before 
	// the node to remove
	lst->current->next->prev = lst->current;
	// now, the new current node should be the node after the one removed
	lst->current = lst->current->next;
	// decrement the count
	lst->count--;
	// return the data
	return data;
}

/// the function to find the index of a certain data item in the DlList_T. If
/// the data was not found, -1 is returned.
/// @param lst the DlList_T to search through
/// @param data the data to search for
/// @return the index of data (0 based) or -1 if not found
int dll_index(DlList_T lst, void * data) {	
	// check for an empty list
	if(dll_empty(lst)) {
		// won't find anything in an empty list
		return -1;
	}
	// start at the first Node
	Node * looper = lst->first;
	// used to know where you found the right Node
	int indexFound = 0;
	// as long as you havne't gotten to NULL
	while(looper != NULL) {
		// check if you found it
		if(looper->data == data) {
			return indexFound;		
		}
		// move forward in the list
		looper = looper->next;
		// increment the counter
		indexFound ++;
	}
	// didn't find it, so show this with returning -1
	return -1;
}

/// the function that tells if there are any Nodes in the DlList_T
/// @param lst the DlList_T to look through
/// @return true if there is at least one Node, otherwise false
bool dll_empty(DlList_T lst) {
	// list is empty when the count is 0
	if(lst->count > 0) {
		return false;
	}
	return true;
}

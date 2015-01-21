/// The header file for my additional double-linked list functionality. 
/// includes interface for the four functions that I wanted to use for mrEd 
/// @author Andrew Dunkum avd1379
/// path in git repo: Project2/dlListExtra.h
/// path on CS machine: Courses/CS243/Homeworks/mechanics-code/Project2/
/// dlListExtra.h

#ifndef _DLLIST_EXTRA_
#define _DLLIST_EXTRA_

/// the struct definition for a Node within the double-linked list. Each node
/// contains a pointer to the data representing that line of text in the buffer
/// and points back and forward to either another Node or NULL
typedef struct node {
	void * data;		// the pointer to the data
	struct node * next;	// the next Node
	struct node * prev;	// the previous Node
} Node;

/// the struct definition for the actual list. The only thing the list itself
/// needs to keep track of is the first Node, the current Node, and the number
/// of Nodes in the list
typedef struct list {
	Node * first;	// first Node in the list
	Node * current;	// the curret position of the "cursor"
	int count;	// the number of Nodes in the list
}*DlList_T;
// now the list has been implemented
#define _DLL_IMPL_

/// the function to return the data from the Node at the "cursor" or the 
/// current position in the DlList_T. This funciton assumes that the user
/// does not get ownership of the data and will not free it. If the DlList_T
/// is empty, NULL is returned
/// @param lst the DlList_T to get the current data from
/// @return the data from the current Node, or NULL if lst is empty
void * dll_get_current(DlList_T lst);

/// the function that returns the index of the "cursor" or the current Node. 
/// If given an empty DlList_T then -1 is returned
/// @param lst the DlList_T in question
/// return the index of the current Node, or -1 if the DlList_T is empty
int dll_get_current_index(DlList_T lst);

/// the function that checks if the Node after the current Node is valid.
/// Differs form dll_has_next because it isn't checking the current position
/// but rather the next Node
/// @param lst the DlList_T in question
/// @return 1 if the next NOde is valid, otherwise 0
int dll_is_next_valid(DlList_T lst);

/// the function that checks if the Node before the current Node is valid.
/// Differs form dll_has_next because it isn't checking the current position
/// but rather the previous Node
/// @param lst the DlList_T in question
/// @return 1 if the previous NOde is valid, otherwise 0
int dll_is_prev_valid(DlList_T lst);

#endif

/// The mrEd.c file. This is the main function of the program, which prompts
/// the user for command and, using a DlList_T stuct, carries out the commands.
/// Changes to the buffer are not saved anywhere untill either a 'wq' or 'w' 
/// command is performed. The buffer is allocated on the heap, and only freed
/// upon quitting from the program
/// @author Andrew Dunkum avd1379
/// NOTE:
/// path in git repo: Project2/mrEd.c
/// path on CS machine: Courses/CS243/Homeworks/mechanics-code/Project2/mrEd.c

// for printf, getline, NULL
#include <stdio.h>
// for true and false
#include <stdbool.h>
// for strtok
#include <string.h>
// for some DlList_T functions
#include "dlListExtra.h"
// for other DlList_T functions
#include "dlList.h" 
// for errno
#include <errno.h>

/// The main method of the mrEd program. The program can be run with an
/// optional command-line argument that specifies a file to edit. If this
/// file does not open, error messages will be printed.
/// @param argc the number of command-line arguments
/// @param argv the command-line arguments
/// @return 0 if no errors occured, otherwise 1
int main(int argc, char* argv[]){
	// the file read from and written to
	FILE * theFile;
	// the buffer that the user manipulates, double linked list
	DlList_T buffer = dll_create();
	// holds the filename. allocated on the heap so it can be accessed 
	// anywhere in the program
	char * fileName = malloc(sizeof(char) * 80);
	// to show there is not fileName	
	strcpy(fileName, "");
	// holds if the buffer differs at all from the current file, ie if it
	// needs to save before exiting
	int hasChanged = 0;
	// if a filename was supplied at the commandline
	if(argc > 1) {
		strcpy(fileName, argv[1]);
		// attempt to open the filename given
		theFile = fopen(fileName, "r");
		// if the file opening doesn't work
		if(!theFile) {
			// if the error wasn't that the file doesn't exist yet
			if(errno != ENOENT) {
				// print an error message to stderr
				fprintf(stderr, "could not read ﬁle ’%s’\n", 
				fileName);
				// there is now no fileName				
				strcpy(fileName, "");
				// print a detailed error message
				perror("open failed");
			};
		// if the file opens correctly
		} else {
			// used to hold each line as it is read from the file
			char * currentLine = NULL;
			// used to pass to getLine
			size_t currentSize = 0;
			// while there are still lines to read
			while(getline(&currentLine, &currentSize, theFile) != 
			-1) {
				// add each line to the buffer
				dll_append(buffer, currentLine);
				// reset the things that get passed to getLine
				currentLine = NULL;
				currentSize = 0;
			}
			// free any space for currentLine
			free(currentLine);
			// flush the file
			fflush(theFile);
			// close it for now
			fclose(theFile);		
		}
	// if no file name was supplied on command-line	
	} else {
		// print a message
		printf("no file supplied\n");
	}
	// keep prompting for commands
	while(1) {
		// used to hold the command input
		char * input = NULL;
		// used to hold the number of characters in the input
		size_t inputSize = 0;
		// gets the input
		getline(&input, &inputSize, stdin);
		// get the first letter, for switch-case usage
		char first = input[0];
		// vary depending on the command
		switch(first){
			// the append command
			case 'a' : ;
				// used to break out of the while loop
				int breaker = 1;
				// used to hold the c-string to be appended
				char * toAppend;
				// used to pass to getline
				size_t appendSize = 0;
				// get where you should start inserting at
				int appendIndex = dll_get_current_index(buffer);
				appendIndex++;
				// keep getting input untill '.' is printed
				while(breaker) {
					// reset the input c-string
					toAppend = NULL;
					// reset the size parameter going to 
					// getline
					appendSize = 0;
					// get the input from stdin
					getline(&toAppend, &appendSize, stdin);
					// if the user doesn't want to exit 
					if(strcmp(".\n", toAppend) != 0){
						dll_insert_at(buffer, 
						appendIndex, toAppend);
						// Something has been changed
						hasChanged = 1;
						appendIndex++;
					// if the user does want to exit
					} else {
						// get rid of the space 
						// allocated for the '.'
						free(toAppend);
						// break out of the while
						breaker = 0;
					}
				}
				// end of this command
				break;
			// the command to print the current line, or to print
			// the current line number
			case '.' :
				// for the '.=' command
				if(inputSize > 1 && input[1] == '='){
					// print the current index of the 
					// buffer, +1 to account for line
					// numbering
					printf("%d\n", 
					dll_get_current_index(buffer) + 1);
				// for the '.' command
				}else{
					// print the current line of the buffer
					printf("%s", (
					char*)dll_get_current(buffer));
				}
				// end of command
				break;
			// the command to go to the next line
			case '+' :
			case '\n' :
				// if the next line isn't NULL
				if(dll_is_next_valid(buffer)){
					// go to the next line
					dll_next(buffer);
					// and print the current line
					printf("%s", 
					(char*)dll_get_current(buffer));
				// if the next line is NULL
				} else {
					// print '?'
					printf("?\n");
				}
				// end of command
				break;
			// the command to go to the previous line
			case '-' :
				// if the previous line isn't NULL
				if(dll_is_prev_valid(buffer)) {
					// go to the previous line
					dll_prev(buffer);
					// print the current line
					printf("%s", 
					(char*)dll_get_current(buffer));
				// if the previous line is NULL
				} else {
					// print '?'
					printf("?\n");
				}
				// end of command	
				break;
			// the command to move to the last line and print it,
			// as well as the command to print the last line number	
			case '$' :
				// if the buffer is empty
				if(dll_empty(buffer)) {
					// print the '?'
					printf("?\n");
					// end of command
					break;
				}
				// if the last line number command was given
				if(strcmp("$=\n", input) == 0) {
					// print the size, since that is the 
					// line number of the last line
					printf("%d\n", 
					dll_size(buffer));
				// if the print last line command was given
				} else {
					// move to the last line
					dll_move_to(buffer, 
					dll_size(buffer) - 1);
					// print the line there
					printf("%s", 
					(char*)dll_get_current(buffer));
				}
				// end of command
				break;
			// the command to delete the current line
			case 'd' :
				// if the buffer is empty
				if(dll_empty(buffer)) {
					// print '?'
					printf("?\n");
				// if the buffer isn't empty 
				} else {
					// pop off the current line, and free
					// the memory allocated for it
					free(dll_pop(buffer, 
					dll_get_current_index(buffer)));
					// something has changed
					hasChanged = 1;
				}
				// end of command
				break;
			// the command to print the buffer to stdout
			case 'p' :
				// if the buffer is empty
				if(dll_empty(buffer)){
					// print '?'
					printf("?\n");
				// if the buffer isn't empty
				} else {
					// start at the beginning
					dll_move_to(buffer, 0);
					// while the next line is valid
					while(dll_is_next_valid(buffer)){
						// print the current line and 
						// move forward
						printf("%s", 
						(char*)dll_next(buffer));
					}
					// print the last line
					printf("%s", 
					(char*)dll_get_current(buffer));
				}
				// end of command
				break;
			// the command to insert before the current line
			case 'i' : ;
				// used to break out of the while loop
				int iBreaker = 1;
				// used to pass to getline
				size_t toInsertSize = 0;
				// used to hold input
				char * toInsert = NULL;
				// the line to insert before
				int startingIndex = 
				dll_get_current_index(buffer);
				// if the list was empty before last call
				if(startingIndex == -1) {
					// increment so it will insert into 
					// the empty DlList_T 
					startingIndex++;
				}
				// loop untill '.' is entered
				while(iBreaker) {
					// reset the input
					toInsert = NULL;
					// reset the size
					toInsertSize = 0;
					// get the new input
					getline(&toInsert, &toInsertSize, 
					stdin);
					// if the user isn't done inserting
					if(strcmp(".\n", toInsert) != 0) {
						// insert the input where you 
						// currently are in the buffer
						dll_insert_at(buffer, 
						startingIndex, toInsert);
						// something has changed
						hasChanged = 1;
						// move the index forward
						startingIndex++;
					// if the user is done inserting
					} else {
						// free the space for the '.'
						free(toInsert);
						// break out of the while
						iBreaker = 0;
					}
				}
				// end of command
				break;
			// the command to quit. This is the quit that does
			// check for unsaved changes
			case 'q' :
				// if something has changed
				if(hasChanged){
					// let the user know
					printf("? buffer dirty.\n");
				// if all changes were saved
				} else {
					// free all the memory from the buffer
					dll_destroy(buffer);
					// free the space allocated for input
					free(input);
					// free the space allocated for the
					// file name
					free(fileName);
					// print a message
					printf("\nBye\n");
					// exit without error
					exit(0);
				}
				// end of command
				break;
			
			// the command to quit. This is the quit taht does not
			// check for unsaved changes
			case 'Q' :
				// free all the memory from the buffer
				dll_destroy(buffer);
				// free the memory allocated for input
				free(input);
				// free the memory allocated for the file name
				// print a message
				printf("\nBye\n");
				// exit wihtout error
				exit(0);
				// end of command, but really will never be 
				// reached, just looks nice
				break;
			// the command to write the buffer to a file
			case 'w' : ;
				// get the first token of input, either w or wq
				char * firstToken = strtok(input, " ");
				// the optional filename part of the command
				char * secondToken = strtok(NULL, " \n");
				// the filename to be written to for this write
				char * thisWrite = NULL;
				// if a fileName was given
				if(secondToken != NULL) {
					// set the fileName field
					thisWrite = secondToken;
					// if no fileName was provided on the 
					// commandline
					if(*fileName == NULL) {
						// the file from this write is
						// now the fileName
						strcpy(fileName, thisWrite);
					}
				}
				// make sure a filename has been given
				if(thisWrite == NULL && strcmp(fileName, "")
				== 0) {
					// if not print a ?
					printf("?\n");
					// command over
					break;
				}
				// if a file name was given with the command
				if(thisWrite != NULL) {
					// open that file. Overwrite existing 
					// data
					theFile = fopen(thisWrite, "w");
				// if no file name was given with the command
				} else {
					//open the file from the command-line
					theFile = fopen(fileName, "w");
				}
				// if the file was open successfully
				if(theFile) {
					// for everyline, starting at 0
					for(int i = 0; i < dll_size(buffer);
					 i++){
						// add the line to the file
						fputs(dll_get(buffer, i), 
						theFile);
					}
					// reset the state for change, nothing 
					// has changed since write
					hasChanged = 0;
					// if a file was given along with this
					// command
					if(thisWrite != NULL){
						// print a message
						printf("file name: '%s'\n", 
						thisWrite);
					}
					// flush the file
					fflush(theFile);
					// close the file
					fclose(theFile);
					// if the user also wanted to quit
					if(strcmp(firstToken, "wq\n") == 0 || 
					strcmp(firstToken, "wq") == 0) {
						// free the buffer
						dll_destroy(buffer);
						// free the space for the input
						free(input);
						// free the space for the file
						// name
						free(fileName);
						// print a message
						printf("\nBye\n");
						// exit the program
						exit(0);
					}
				// if something went wrong opening the file
				} else {
					// print an error
					perror("open failed");
				}
				// end of command
				break;
			// if the user input a line number to print
			default: ;
				// get an integer from the input
				int value = atoi(input);
				// if the value was in the range of the buffer
				if(value > 0 && value <= dll_size(buffer)) {
					// go back one (indexing)
					value--;
					// go to that index
					dll_move_to(buffer, value);
					// and print it
					printf("%s", 
					(char*)dll_get_current(buffer));
				// if the value wasn't in range				
				} else {
					// print '?'
					printf("?\n");
				}
				// end of command
				break;
		}
		// always free the space each time that was made for input
		free(input);
	}
	// nothing messed up, so return 0. This won't ever be reached though..
	return 0;
}


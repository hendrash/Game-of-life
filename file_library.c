#include "file_library.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*
 * @param file_name: Name of a the file being read in  
 * @param contents:  Takes in array and writes content to it
 * @return st.st_size: return the size of the array
 * reads a filein and writes to to the content array
 */
size_t read_file(char* file_name, char** contents){
	struct stat st;
	stat(file_name, &st);
	FILE* file = fopen(file_name, "r");
	// allocating memory to content
	*contents = (char*) malloc(st.st_size * sizeof(char));
	// reading in the file
	size_t num_bytes = fread(*contents, st.st_size, 1, file);
	//close the file
	fclose(file);
	return st.st_size;
}

/* write_file writes a string of bytes to disk 
 * @param file_name: takes in a file name
 * @param content takes in the content from an array 
 * @param takes in the size
 * @return returns the size of the st
 * Writes to a file the array of contents in a file 
 * */
size_t write_file(char* file_name, char* contents, size_t size){
	struct stat st;
	int errnum;

	file_name = strtok(file_name, "\n");
	stat(file_name, &st);
	FILE* file = fopen(file_name, "wb");
	// if the file can't be open throw an error 
	if (file == NULL) {
      		errnum = errno;
      		fprintf(stderr, "Value of errno: %d\n", errno);
      		perror("Error printed by perror");
      		fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
   	}
	else{
		// else write to a file the contents of "contents"
		fwrite(contents, size, sizeof(contents), file);
		//close the file
		fclose(file);
		return st.st_size;
	}
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "tree.h"
#include <assert.h>

#define MAX_NUM_FIELDS 11
#define MAXCHARS 128
#define MAX_CHARS_LINE 512
#define XYCORD 2
#define INFINITE 99999999
int main(int argc, char * argv[]) {

	struct tree *tree = NULL, *newroot, *champion;
	int lineNumber = 0, coma = 0, j, diff, quotation = 0, i = 0, length = 0, index = 0, same = 0, d, comp;
	char * line = NULL, tradename[MAXCHARS + 1], new_data[XYCORD][MAXCHARS + 1], key[XYCORD][MAXCHARS + 1], *token, *token2;
	size_t lineBufferLength = MAX_CHARS_LINE;
	list_t * list;
	double min_distance;
    
	/*data as 2d array to store all information of a file*/
	char ** data = (char ** ) my_malloc(MAX_NUM_FIELDS * sizeof(char * ));

	/*filename as the csv file that we are going to look and output as the information from the keyfile*/ 
	FILE * filename = fopen(argv[1], "r"); 
	assert(filename);
	FILE * output = fopen(argv[2], "w");
	assert(output);
	
	list = make_empty_list();

	/*get each line from the csv file*/
	while (getline( & line, & lineBufferLength, filename) > 0) {

		/*throw the firstline (header) of the fields*/
		if (lineNumber == 0) {
		
		}else {
			
			/*check every line*/
			while (line[i] != '\0') {

				/*in each of the character of the line, check if there ie no coma or a coma inside a quotation, keep looping*/
				if (line[i] != ',' || (line[i] == ',' && quotation == 1)) {

					/* if it is the first quotation, mark them, to ensure that each quote has a pair */
					if ((line[i] == '\"') && quotation == 0) {
						quotation = 1;

					/*else, mark them back once we find the second quote*/
					}else if ((line[i] == '\"') && quotation == 1) {
						quotation = 0;
					}
					
					/*as long as there is no coma to seperate the words, keep track on how long the char is and also the last index */
					length++;
					index++;
				
				/*if there is coma that seperate each field*/
				} else {

					/*find the difference in order to find out the starting index of the words*/
					diff = index - length;

					/*each coma represent which field they are , malloc each array based on the length of a word and put those words */
					data[coma] = (char * )my_malloc(sizeof(char) * (length + 1));

					for (j = 0; j < length; j++) {
						data[coma][j] = line[diff + j];
					}
					data[coma][j] = '\0';
					length = 0;
					coma++;
					index++;
				}
				i++;
			}

			/*last field which is location. since last char is '\0', we need to do seperately as it can't go to the looping*/ 
			if (line[i] == '\0') {
				/*just do it like the previous one*/
				diff = index - length;
				data[coma] = (char * ) my_malloc(sizeof(char) * (length + 1));

				for (j = 0; j < length; j++) {
					data[coma][j] = line[diff + j];
				}
				data[coma][j] = '\0';
				
				/*allocate them in the linked list*/
				allocate_data(list, data);
				
				//coordinate is copied to a new data for building the tree
				strcpy(new_data[0], data[8]);
				strcpy(new_data[1], data[9]);
				
				// insert data to the tree
				tree = treeInsert(tree,new_data , &same);
				same = 0;
				
				/*free the data that we have used in each line in order to do the next malloc for the next line*/
				for (i = 0; i < MAX_NUM_FIELDS; i++) {
				  free(data[i]);
				}
			}		
			length = 0;
			coma = 0;
			index = 0;
			i = 0;
		}
		lineNumber++;
	}
	
	/*scan for the keyword and check them if they exist in the list*/
	while (scanf("%[^\n] ", tradename) == 1) {
		
		//initialise everything to null and 0 everytime it scan a new coordinate
		newroot = NULL, champion = NULL, min_distance = INFINITE,d = 0, comp = 0;
		token = strtok(tradename, " ");
		token2 = strtok(NULL, " ");
		
		//copy it into the key for later use
		strcpy(key[0],token);
		strcpy(key[1],token2);
		
		//search for a root which has the least distance with the given key
		newroot=treesearc(tree,key, d, &comp,  &min_distance, champion);
		
		//stdout
		printf("%s %s --> %d\n", key[0], key[1], comp);
		
		//check those coordinate which match to the linked list and bring it to the output
		check_list(list -> head, newroot->cord, output, key);
		fprintf(output,"\n");
	
	}


	/*free all the data */
	freeTree(tree);
	free_list(list);
	free(data);
	free(line);
	fclose(filename);
	fclose(output);
	return 0;
}
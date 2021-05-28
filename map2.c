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
#define EPSILON 1e9
#define LEFT 0
#define RIGHT 1

int main(int argc, char * argv[]) {

	int lineNumber = 0, coma = 0, j, diff, quotation = 0, i = 0, length = 0, index = 0,same = 0;
	char * line = NULL, input_line[MAXCHARS + 1], new_data[XYCORD][MAXCHARS + 1] , key[XYCORD][MAXCHARS + 1];
	size_t lineBufferLength = MAX_CHARS_LINE;
	list_t * list;
	struct tree *tree = NULL;
    
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
		}
		
		else {
			
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
				
				//copy to new data which is for  tree use later
				strcpy(new_data[0], data[8]);
				strcpy(new_data[1], data[9]);
				
				//insert to  tree
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
	
	//scan for the keyword and check them if they exist in the list
	while (scanf("%[^\n] ", input_line) == 1) {
		
		//initialise each variable to null and 0 each time check for a new cordinate
		int d = 0, comparison = 0;
		struct tree *champion = NULL;
		
		//split those input lie to get coordinates and radius
		char * token = strtok(input_line, " ");
		char * token2 = strtok(NULL, " ");
		char *token3 = strtok(NULL," ");
		
		strcpy(key[0],token);
		strcpy(key[1],token2);
		strcpy(key[2],token3);
		
		//search the nearest location based on the given radius
		radius_search(tree,key, d, &comparison, champion, list->head, output);
		printf("%s %s %s --> %d\n", key[0], key[1], key[2], comparison);
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

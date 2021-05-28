#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#define MAX_NUM_FIELDS 11
#define MAXCHARS 128



typedef struct node node_t;
/*structure for dictionary to store all info and make linked list*/
struct node {
	char * census_year;
	char * blockID;
	char * propertyID;
	char * bpropertyID;
	char * clue;
	char * tradename;
	char * inducode;
	char * indudes;
	char * xcord;
	char * ycord;
	char * location;
	node_t * next;
};

/*this function is to allow strdup and the assertion of each strdup*/
char * my_strdup(char *s) {
	char *new= strdup(s);
	assert(new);
	return new;
}

/*this function is to allow malloc and the assertion of each malloc*/
void *my_malloc( size_t n) {
	void *p= malloc( n );
	assert(p);
	return p;
}

/*list which point at the first item and at the last item . credit: alisair*/
typedef struct {
	node_t * head;
	node_t * foot;
}
list_t;

/*make an empty list and malloc them. credit:alisair */
list_t 
*make_empty_list(void) {
	list_t * list;
	list = (list_t * )my_malloc(sizeof( * list));
	
	/* initialize head and foot to NULL before using it*/
	list -> head = list -> foot = NULL;
	return list;
  }

/*this function is to eliminate beginning and end quotes as well as checking quote inside the sentence*/
void 
quoting(char * data, char * newdata) {
	int a = 0;
	char temp[MAXCHARS+1];
  
   /*initialise newdata as an empty string*/
	strcpy(newdata, "");

	if (data[0] == '\"') {
		/*store the data to a temporary string and drop the beginning quote if there is any*/
		strcpy(temp, & data[1]);

		/*delete any extra spaces or newline at the end and the close quotation*/
		while (temp[strlen(temp) - 1] == '\n' || isspace(temp[strlen(temp) - 1])) {
			temp[strlen(temp) - 1] = '\0';
		}
	temp[strlen(temp) - 1] = '\0';

	}else{
		/*if no quotation, copy all the word */
		strcpy(temp, & data[0]);
	}

/*check if there are multiple of quotation inside each sentence*/
	for (a = 0; a < strlen(temp); a++) {
  
		/*skip if there is quote in the current character and the next characters, otherwise, strcat to a newdata*/
		if (temp[a] == '\"' && temp[a + 1] == '\"') {
		/*do nothing*/

		} else {
			strncat(newdata, & temp[a], 1);
		}
	}
  return;
}

/*Allocate the each fields to linked list*/
list_t 
*allocate_data(list_t * list, char ** data) {
	node_t * new_node;
	char updated_data[MAX_NUM_FIELDS][MAXCHARS+1];
	int i = 0;
	new_node = (node_t * )my_malloc(sizeof( * new_node));
	assert(list != NULL);
	
	/*update each data to eliminate any unwanted quote*/
	for(i = 0; i < 11; i++){
		quoting(data[i],updated_data[i]);
	}
    
	/*put it in the node*/
	new_node -> census_year = my_strdup(updated_data[0]);
	new_node -> blockID = my_strdup(updated_data[1]);
	new_node -> propertyID = my_strdup(updated_data[2]);
	new_node -> bpropertyID = my_strdup(updated_data[3]);
	new_node -> clue = my_strdup(updated_data[4]);
	new_node -> tradename = my_strdup(updated_data[5]);
	new_node -> inducode = my_strdup(updated_data[6]);
	new_node -> indudes = my_strdup(updated_data[7]);   
	new_node -> xcord = my_strdup(updated_data[8]);
	new_node -> ycord = my_strdup(updated_data[9]);
	new_node -> location = my_strdup(updated_data[10]);
	new_node -> next = NULL;

	if (list -> foot == NULL) {
		/* this is the first insertion into the list */
		list -> head = list -> foot = new_node;
	} else {
		list -> foot -> next = new_node;
		list -> foot = new_node;
	}
	return list;
}

/* this function is to check the keyword and match to the dictionary */
void 
check_list(node_t * head, char key[2][129], FILE * output , char input[2][129]) {
	int j = 0;
	struct node * dictionary;
	
	dictionary = head;
	
	while (dictionary != NULL) {

	/*check the key by matching it to the coordinate loop everything and will print the output of it*/
		if ((strcmp(dictionary -> xcord, key[0]) == 0) &&(strcmp(dictionary -> ycord, key[1]) == 0)) {
			//output file for the stage 2
			if (input[2] != NULL){
				fprintf(output, "%s %s %s --> Census year: %s || Block ID: %s || Property ID: %s || Base property ID: %s || CLUE small area: %s || Trading Name: %s || Industry (ANZSIC4) code: %s || Industry (ANZSIC4) description: %s || x coordinate: %s || y coordinate: %s || Location: %s || \n", input[0],input[1],input[2], dictionary -> census_year, dictionary -> blockID, dictionary -> propertyID, dictionary -> bpropertyID, dictionary -> clue,dictionary -> tradename , dictionary -> inducode, dictionary -> indudes, dictionary -> xcord, dictionary -> ycord, dictionary -> location);

			//output file for stage 1
			}else {
				fprintf(output, "%s %s --> Census year: %s || Block ID: %s || Property ID: %s || Base property ID: %s || CLUE small area: %s || Trading Name: %s || Industry (ANZSIC4) code: %s || Industry (ANZSIC4) description: %s || x coordinate: %s || y coordinate: %s || Location: %s || \n", input[0],input[1], dictionary -> census_year, dictionary -> blockID, dictionary -> propertyID, dictionary -> bpropertyID, dictionary -> clue,dictionary -> tradename , dictionary -> inducode, dictionary -> indudes, dictionary -> xcord, dictionary -> ycord, dictionary -> location);
			}
			j++;
		} 
		dictionary = dictionary -> next; 
	}
	
	/*if there is no key found */
	if (j == 0) {
		fprintf(output, "%s %s--> NOT FOUND\n", key[0], key[1]);
	}
}

/*free all the list after using them. credits: Alisair*/
void
free_list(list_t * list) {
	node_t * now, * before;
	assert(list != NULL);

	now = list -> head;

	while (now) {
		before = now;
		now = now -> next;
		free(before -> census_year);
		free(before -> blockID);
		free(before -> propertyID);
		free(before -> bpropertyID);
		free(before -> clue);
		free(before -> tradename);
		free(before -> inducode);
		free(before -> indudes);
		free(before -> xcord);
		free(before -> ycord);
		free(before -> location);
		free(before);
	}
	free(list);
}


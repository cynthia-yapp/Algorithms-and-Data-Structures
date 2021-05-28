#ifndef DICTH
#define DICTH
#include "list.h"
#include "tree.h"
#include <assert.h>


typedef struct node node_t;
/*structure for dictionary to store all info and make linked list*/
struct node{
	char *census_year;
	char *blockID;
	char *propertyID;
	char *bpropertyID;
	char *clue;
	char *data;
	char *inducode;
	char *indudes;
	char *xcord;
	char *ycord;
	char *location;
	node_t *next;
};

/*list which point at the first item and at the last item . taken from: alisair*/
typedef struct {
	node_t *head;
	node_t *foot;
} list_t;

/*this function is to check the radius*/
struct tree *check_radius(struct tree *root, char cord[XYCORD][MAXCHARS + 1], int d, int *comp, double radius , struct tree *newchampion, int sides, node_t *list,FILE * output,char input[XYCORD][MAXCHARS + 1] );

/*this function is to search for a nearest location within the radius*/
struct tree *treeradiussearc(struct tree* root, char cord[XYCORD][MAXCHARS + 1], int d, int *comp, double radius, struct tree *champion, node_t * list, FILE * output , char input[COORDINATE][MAXCHARS + 1]);

/*this function is to allow the assertion of each malloc*/
void *my_malloc( size_t n);

 /*this function is to allocate them in the linked list*/
list_t *allocate_data(list_t *list, char **data);

/*this function is to free all the linked list. taken from :Alisair*/
void free_list(list_t *list);

/*main function*/
int
main(int argc, char *argv[]);

#endif

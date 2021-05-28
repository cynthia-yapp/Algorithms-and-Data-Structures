#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#define MAX_NUM_FIELDS 11
#define MAXCHARS 128
#define XYCORD 2

/*this struct is made for the tree*/
struct tree {
    struct tree *left;
    struct tree *right;
	char  cord[XYCORD][MAXCHARS + 1];
    int same;
};

/*this function is to build the KD Tree and insert all the data to the tree*/
struct tree *treeInsert(struct tree *parent, char key[XYCORD][MAXCHARS + 1], int *same);

/*this function is to free the tree*/
void freeTree(struct tree *parent);

/*this function is make a deep check  to find nearest coordinate*/
struct tree *check_tree(struct tree *root, char key[XYCORD][MAXCHARS + 1], int d, int *comp, double* curr_distance , struct tree *champion, int sides);

/*this function is to check for the nearest coordinate*/
struct tree *search(struct tree* root, char key[XYCORD][MAXCHARS + 1], int d, int *comp);

/*this function is used to make deep check in searching the location within the given radius*/
struct tree *check_radius(struct tree *root, char keycord[XYCORD][MAXCHARS + 1], int d, int *comparison, struct tree *newchampion, int side, node_t *list,FILE * output);

/*this function is to search the location within the given radius*/
struct tree *radius_search(struct tree* root, char keycord[XYCORD][MAXCHARS + 1], int d, int *comparison, struct tree *champion, node_t * list, FILE * output);
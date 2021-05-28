#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "list.h"

#define MAX_NUM_FIELDS 11
#define MAXCHARS 128
#define XYCORD 2
#define EPSILON 1e9
#define LEFT 0
#define RIGHT 1

/*this struct is made for building KD tree*/
struct tree {
	
    struct tree *left;
    struct tree *right;
	char cord[XYCORD][MAXCHARS+1];
    int same;
};


/* this function is to insert all the data to the tree*/
struct tree *treeInsert(struct tree *parent, char key[XYCORD][MAXCHARS+1], int *same){

    struct tree **insertloc = &parent;
    int d = 0;

	//check until it reach NULL so that we can insert into the leaf
    while(*insertloc){
       
		//if the input key is the same root cordinate,  don't put on the leaves but return to parent
        if (atof(key[d]) == atof(((*insertloc) -> cord[d])) && (atof(key[1 - d]) == atof(((*insertloc) -> cord[1 - d])))){
			//mark it as same
            *same = 1;
            (*insertloc) -> same = 1;
            return parent;   
        }
		
		// if input key is less than the root key, put it on the left and vice versa.
        if(atof(key[d]) < atof(((*insertloc) -> cord[d]))){
            insertloc = &((*insertloc) -> left);
			
        }else if (atof(key[d]) >= atof(((*insertloc) -> cord[d]))){
            insertloc = &((*insertloc) -> right);
        }
			//always change the x and y cordinate when checking
			d = 1 - d;
    }
	
    *insertloc = (struct tree *)malloc(sizeof(struct tree));
    assert(insertloc);
   
	//always initialise both side to be NULL 
    (*insertloc) -> left = NULL;
    (*insertloc) -> right = NULL;
    
	//if they are same then assign them to 1 else 0 and insert those key to the tree
    (*insertloc) -> same = 0;
    strcpy((*insertloc) -> cord[0], key[0]);
    strcpy((*insertloc) -> cord[1], key[1]);
	return parent;  
}

/* this function is to free the KD tree*/
void freeTree(struct tree *parent){
	
    if(!parent){
        return;
    }
    freeTree(parent->left);
    freeTree(parent->right);  
    free(parent);
 
}

/*thus function is to check the tree if any left/ right side already null, we still need to search for the other side*/
struct tree *check_tree(struct tree *root, char key[XYCORD][MAXCHARS+1], int d, int *comp, double* curr_distance , struct tree *champion, int sides){
	double x, distance,y;
	
	if (root == NULL){
		return champion;
	}
	 
	//find distance and increment the comparison
    x = (atof(root -> cord[0]) - atof( key[0]));
    y = (atof(root -> cord[1]) - atof( key[1]));
	*comp = *comp + 1;
   distance = (x * x + y * y);
   
    if (*curr_distance > distance){
        *curr_distance = distance;
        champion = root;
    }
	/*if left go to left root*/
	if (sides == LEFT){
		return check_tree(root -> left, key, 1 - d, comp, curr_distance, champion, sides); 
	}else {
		return check_tree(root -> right, key, 1 - d, comp, curr_distance, champion, sides);
	}	
}

/*this function is to search for the nearest locatiom*/
struct tree *treesearc(struct tree* root, char key[XYCORD][MAXCHARS+1], int d, int *comp, double *curr_distance, struct tree *champion) 
{ 
    double distance ,x ,y;
    int sides;
	
	// if the current root is NULL, check the current minimum root called champion
    if (root == NULL){
		
		//if there is no leaf in the current champion root, check the other side of the leaf either left or right 
		if (champion -> right == NULL){
			if ((champion -> left) != NULL){
				sides = LEFT;
				champion = check_tree(champion -> left, key, d,comp, curr_distance, champion, sides);
			}
		} else if (champion -> left == NULL){
			// and vice versa
			if ((champion -> right) != NULL){		
				sides = RIGHT;
				champion = check_tree(champion -> right, key, d,comp, curr_distance, champion, sides);
			}
		}
        return champion; 
    }
	
	//check distance
    x = (atof(root -> cord[0]) - atof( key[0]));
    y = (atof(root -> cord[1]) - atof( key[1]));
    *comp = *comp + 1;   
	distance = (x * x + y * y);

	// if current distance is bigger, replace them with smaller one
    if (*curr_distance > distance){
        *curr_distance = distance;
        champion = root;
    }

    if (((atof(root -> cord[d]) == atof( key[d])) && (atof(root -> cord[1 - d]) == atof( key[1 - d])))){
		//directly return to the tree if we found out the exact match of the coordinate 
       return champion; 
    } 
	
    //if the given Key is greater than root's key , check right side
    if (atof(root -> cord[d]) <= atof(key[d])) {
       return treesearc(root -> right, key,1-d, comp, curr_distance, champion); 
    }
	 
	//else check left
    return treesearc(root -> left, key, 1 - d, comp, curr_distance, champion); 
} 


/*check the other side of the root if the left /right has reached NULL*/
struct tree *check_radius(struct tree *root, char keycord[XYCORD][MAXCHARS + 1], int d, int *comparison, struct tree *newchampion, int side, node_t *list,FILE * output){
	
	double x, distance, y, radiuss;
	
	// times the radius with epsilon so the decimal wont be too long
	radiuss = atof( keycord[2] ) * atof( keycord[2] ) * EPSILON;
	
	//if no more root that is less than or equal the distance, return to the champion root before
	if (root == NULL){
		return newchampion;
	}
	*comparison = *comparison + 1;
	
	//find distance 
    x = (atof (root -> cord[0]) - atof(keycord[0]) );
    y = (atof (root -> cord[1]) - atof(keycord[1]) );
	distance = (x * x + y * y) * EPSILON;
	
    if (radiuss >= distance){
        newchampion = root;
		
		//check the right side again to make sure if there is any nearest loc in  the right side
		side = RIGHT;
		check_radius(newchampion -> right, keycord, d,comparison, newchampion, side, list, output);
		
		//print the output for the distance less than radius
		check_list(list , newchampion->cord, output, keycord);
    }
	
	if (side == RIGHT){
		//check left again so that we will not miss anything
		return check_radius(root -> left, keycord, 1 - d, comparison, newchampion, side,list, output); 
	}else {
		//check right again so that we will not miss anything
		return check_radius(root -> right, keycord, 1 - d, comparison, newchampion, side, list, output);
	}
}

/*this function is to search the location within the given radius*/
struct tree *radius_search(struct tree* root, char keycord[XYCORD][MAXCHARS + 1], int d, int *comparison, struct tree *champion, node_t * list, FILE * output) { 
    double distance ,x ,y ,radiuss;
    int side;
	struct tree *newchampion = NULL;
	
	// times the radius with epsilon so the decimal wont be too long
	radiuss = atof( keycord[2] ) * atof(keycord[2]) * EPSILON;
	
	
    if (root == NULL){
		
		//if there is one or more nearest location
		if (champion != NULL){
			
			//if  the nearest location is at right then check the left root and from that root check the right for nearest location and vice versa
			if (champion -> right == NULL){
				if ((champion -> left) != NULL){
		
					side = RIGHT;
					check_radius(champion -> left, keycord, d,comparison, newchampion, side, list, output);
				}
			}else if (champion -> left == NULL){
				if ((champion -> right) != NULL){
			
					side = LEFT;
					check_radius(champion -> right, keycord, d,comparison, newchampion, side, list, output);
				}
			}
		}
		
		// if there is no nearest location
		else if (champion == NULL){
			fprintf(output,"%s %s %s-->NOT FOUND\n", keycord[0], keycord[1], keycord[2]);
		}
		return champion;      
	}
	
    // find distance
    x = ( atof( root -> cord[0] ) - atof(keycord[0]) );
    y = ( atof(root -> cord[1] ) - atof(keycord[1]) );
	distance = (x * x + y * y) * EPSILON;
    *comparison = *comparison + 1;   
   
	
    if (radiuss >= distance){
        champion = root;
		
		//check if there is one  or more nearest location
		if (champion != NULL){
			//check the right of the root but on that root we want to find the left leaf and print the output
			side = LEFT;
			check_radius(champion -> right, keycord, d,comparison, newchampion, side, list, output);
			check_list(list , champion -> cord, output, keycord);
		}
    }
       
    // Key is greater than root's key  check right otherwise check left
    if (atof(root -> cord[d]) <= atof(keycord[d])) {
       return radius_search(root -> right, keycord,1-d, comparison ,champion ,list ,output); 
    }
	else {
		return radius_search(root -> left, keycord, 1-d, comparison ,  champion,list ,output); 
	}
} 

#ifndef LISTH
#define LISTH
#define XYCORD 2
#define MAXCHARS 128

    
    
  
    
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

/*this function is to allow malloc and the assertion of each malloc*/
void *my_malloc( size_t n);

/*this function is to allow strdup and the assertion of each strdup*/
char * my_strdup(char *s);
	
/*this function is to make an empty list. taken from :Alisair */
list_t *make_empty_list(void);

/*this function is to free all the linked list. taken from :Alisair*/
void free_list(list_t *list);

/*this function is to allocate them in the linked list*/
list_t *allocate_data(list_t *list, char **data);

/*this function is to check and delete quotation*/
void quoting(char * data, char * newdata);

/* this function is to check the keyword and match to the dictionary */
void check_list(node_t *head,char cordinate[XYCORD][MAXCHARS + 1], FILE *output,  char input[XYCORD][MAXCHARS + 1]);

/*this function is to search for the nearest location from a given coordinate*/
struct tree *treesearc(struct tree* root, char cord[XYCORD][MAXCHARS + 1], int d, int *comp, double *mind, struct tree *champion);

#endif
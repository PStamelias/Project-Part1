#include "struct1.h"

typedef struct bh_node { //mia uesh toy yperkyboy dhladh toy pinaka kat/smoy deixnei se mia lista apo bucket_hypercube
	struct bh_node* next;
	image_node *image;
} bucket_hypercube;


typedef struct tree_node { //to f_node einai o kombos enos BST.Ena BST antistoixei se mia f synarthsh
  int key;  //to key exei mia timh enos h
  int value; //to value einai eite 0 eite 1
  struct tree_node *l; //deikth se aristero kombo
  struct tree_node *r; //deikth se deji kombo
} f_node;


f_node **create_f_trees(int);
f_node* insert_f_tree(f_node *, int, int *);
int string01_of_image(image_node *, f_node **, int, int *, int, int**, int, int, int *);
bucket_hypercube** bucket_hypercube_creation(image_node*, int, int, f_node **, int *, int, int**, int, int, int *);
int hamming(int, int);
void print_tree(f_node *);
void free_tree(f_node *root);
void exit_memory_hypercube(char*, char*, char*, image_node*, int, bucket_hypercube**, int);

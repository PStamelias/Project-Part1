typedef struct i_node {
	int image_number;  /*o ayjontas ariumos poy antistoixei sthn eikona*/
	int* pixels;    /*o pinakas pixels einai enas monodiastatos pinakas akeraivn me <ariumos_grammvm>x<ariumos_sthlwn> ueseis*/
	                /*kai anaparista to dianysma mias eikonas*/
} image_node;  /*to image_node anaparista mia eikona(to image_number kai to dianusma ths)*/


typedef struct b_node {    /*to bucket periexei enan deikth se kapoio image_node,enan aproshmo*/
	image_node* image_info;  /*akeraio g o opoios einai h timh toy g mias eikonas gia enan sygkekrimeno*/
	unsigned int g;          /*pinaka katakermatismoy kai enan deikth se epomeno bucket*/
	struct b_node* next;     /*ua exoyme L pinakes katakermatismoy,kaue uesh kaue pinaka katakermatismoy ua deixnei se*/
} bucket;                  /*mia lista apo buckets(ta opoia ua exoyn tis g times poy dinoyn eikones gia enan */
	                         /*sygkekrimeno pinaka katakermatismoy)*/

typedef struct t_image_nd {
	int image;
	struct t_image_nd* next;
} image;


image_node* image_creation(FILE*, int, int);
int* create_hi(int ,int);
int** create_g(int ,int ,int );
int*** create_s_numbers_ofLtables(int ,int ,int ,int );  /*htan h create_Ltables*/
void input_info(FILE*, int* ,int*);
void exit_memory(char*, char*, char*, int, image_node*, int, int, int***, bucket***, int);
bucket*** Hash_Table_Creation(image_node*, int, int, int, int *, int, int***, int, int, int*);


int manhattan_dist(image_node *, image_node *, int);
int brute_force(image_node*, int, int, int);
int power(int, int);
int mod(int, int);
int *create_mmodM(int, int, int);
int compute_h(image_node *, int *, int, int*, int, int);
unsigned int compute_g(image_node *, int, int, int *, int, int***, int, int);

void range_search(image_node, unsigned int *, bucket***, int, int, FILE*, int, float);
int compare( const void*, const void*);
void insert_list(image**, int);
int search_list(image*, int);
int size_list(image*);
void print_list(image*, FILE*);
void approximateNN(image_node, unsigned int *, int, int, bucket***, int, int, int *, int *);
void exact_NN(image_node, image_node*, int, int, int *, int *, int);

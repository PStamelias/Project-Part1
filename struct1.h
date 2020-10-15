typedef struct i_node {
	int image_number;  /*o ayjontas ariumos poy antistoixei sthn eikona*/
	int* pixels;    /*o pinakas pixels einai enas monodiastatos pinakas akeraivn me <ariumos_grammvm>x<ariumos_sthlwn> ueseis*/
	                /*kai anaparista to dianysma mias eikonas*/
} image_node;  /*to image_node anaparista mia eikona(to image_number kai to dianusma ths)*/
typedef struct b_node{
	image_node* image_info;
	unsigned int g;
	struct b_node* next;
}bucket;
image_node* image_creation(FILE*, int, int);
int* create_hi(int ,int);
int** create_g(int ,int ,int );
int*** create_s_numbers_ofLtables(int ,int ,int ,int );  /*htan h create_Ltables*/
void input_info(FILE*, int* ,int*);
unsigned int  compute_g();
void exit_memory(char* ,char* ,char* ,int ,image_node* ,int ,int ,int*** ,bucket***,int );
bucket*** Hash_Table_Creation(image_node* image_table,int number_of_hash_tables,int number_of_images,int* table_siz);

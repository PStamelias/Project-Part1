typedef struct i_node {
	int image_number;  /*o ayjontas ariumos poy antistoixei sthn eikona*/
	int* pixels;    /*o pinakas pixels einai enas monodiastatos pinakas akeraivn me <ariumos_grammvm>x<ariumos_sthlwn> ueseis*/
	                /*kai anaparista to dianysma mias eikonas*/
} image_node;  /*to image_node anaparista mia eikona(to image_number kai to dianusma ths)*/

image_node* image_creation(char*);
int* create_hi(int ,int);
int** create_g(int ,int ,int );
int*** create_Ltables(int ,int ,int ,int );
void input_info(int* ,int*,char* );
void exit_memory(char* query_file,char* output,char* input,int number_of_images,image_node* image_table,int L,int K,int*** L_tables);
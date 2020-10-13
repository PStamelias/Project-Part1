typedef struct i_node {
	int image_number;  /*o ayjontas ariumos poy antistoixei sthn eikona*/
	int* pixels;    /*o pinakas pixels einai enas monodiastatos pinakas akeraivn me <ariumos_grammvm>x<ariumos_sthlwn> ueseis*/
	                /*kai anaparista to dianysma mias eikonas*/
} image_node;  /*to image_node anaparista mia eikona(to image_number kai to dianusma ths)*/

image_node* image_creation(FILE*, int, int);
int* create_hi(int ,int);
int** create_g(int ,int ,int );
int*** create_s_numbers_ofLtables(int ,int ,int ,int );  /*htan h create_Ltables*/
void input_info(FILE*, int* ,int*);
void exit_memory(char* ,char* ,char* ,int ,image_node* ,int ,int ,int*** );

typedef struct i_node {
	int image_number;  /*o ayjontas ariumos poy antistoixei sthn eikona*/
	int* pixels;    /*o pinakas pixels einai enas monodiastatos pinakas akeraivn me <ariumos_grammvm>x<ariumos_sthlwn> ueseis*/
	                /*kai anaparista to dianysma mias eikonas*/
} image_node;  /*to image_node anaparista mia eikona(to image_number kai to dianusma ths)*/

void exit_memory(char* query_file,char* input_file,char* output_file,FILE* fp,image_node* image_table,int number_of_images);
void input_info(FILE* file, int* number_of_im, int* sum);
image_node* image_creation(FILE* file, int number_of_images, int distances);
#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include "struct2.h"

void exit_memory_hypercube(char* query_file,char* input_file,char* output_file,FILE* fp,image_node* image_table,int number_of_images){
	free(query_file);
	free(input_file);
	free(output_file);
	fclose(fp);
	for(int i=0;i<number_of_images;i++)
		free(image_table[i].pixels);
	free(image_table);
}

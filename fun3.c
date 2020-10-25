#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include "struct3.h"
void exit_memory_cluster(char* input_file,char* configuration_file,char* output_file,char* method,char* optional,FILE* inptr,image_node* node,int num_img){
	free(input_file);
	free(configuration_file);
	free(output_file);
	free(method);
	free(optional);
	fclose(inptr);
	for(int i=0;i<num_img;i++)
		free(node[i].pixels);
	free(node);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "struct3.h"
#define MAX_COUNT_WORD 50
void exit_memory_cluster(char* input_file,char* configuration_file,char* output_file,char* method,char* optional,FILE* inptr,image_node* node,int num_img,int* Kmeans){
	free(input_file);
	free(configuration_file);
	free(output_file);
	free(method);
	free(optional);
	free(Kmeans);
	fclose(inptr);
	for(int i=0;i<num_img;i++)
		free(node[i].pixels);
	free(node);
}
void conf_info(char* configuration_file,int* K,int* number_of_vector_hash_tables,int* number_of_vector_hash_functions,int* max_number_M_hypercube,int* number_of_hypercube_dimensions,int* number_of_probes){
	FILE* f=fopen(configuration_file,"r");
	char command[50];
	int line=0;
	int pos;
	while(1){
		if(feof(f))
			break;
		fscanf(f,"%s",command);
		for(int i=0;i<strlen(command);i++){
			if(command[i]==':'){
				pos=i+1;
				break;
			}
		}
		int val=0;
		for(int j=pos;j<strlen(command);j++)
			val=val*10+command[j]-'0';
		if(line==0)
			*K=val;
		else if(line==1){
			if(val==0)
				*number_of_vector_hash_tables=3;
			else 
				*number_of_vector_hash_tables=val;
		}
		else if(line==2){
			if(val==0)
				*number_of_vector_hash_functions=4;
			else
				*number_of_vector_hash_functions=val;
		}
		else if(line==3){
			if(val==0)
				*max_number_M_hypercube=10;
			else
				*max_number_M_hypercube=val;
		}
		else if(line==4){
			if(val==0)
				*number_of_hypercube_dimensions=3;
			else
				*number_of_hypercube_dimensions=val;
		}
		else if(line==5){
			if(val==0)
				*number_of_probes=2;
			else
				*number_of_probes=val;
		}
		line++;
		memset(command, 0, strlen(command));
	}
	fclose(f);
}

int* initialization_kmeans(int K,image_node* image_table,int image_number){
	int* K_clust=malloc(K*sizeof(int));
	int first_K=rand()%image_number; 
	image_node first_img=image_table[first_K];
	int* D=malloc(image_number*sizeof(int));
	D[first_K]=-1;
	free(D);
	return K_clust;
}
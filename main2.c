#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "struct2.h"
#define MAX_LENGTH_WORD 500

int main(int argc,char** argv) {

	int arguments_number = argc-1;

	int K,M,N; //K = d'//M = max plhuos ypochfiwn poy ua elegxthoun
	double R;  //N plhsiesteroi geitones //R aktina anazhthshs

	int probes; //max plhuos koryfwn
	int number_of_images;
	image_node* image_table;

	char* input_file;
	char* query_file;
	char* output_file;

	int distances;

	FILE *fp;


	if(arguments_number != 0) {

		for (int pos = 1; pos <= arguments_number-1; ) {

			if(strcmp(argv[pos],"-d") == 0) {
				input_file = malloc((strlen(argv[pos+1])+1)*sizeof(char));
				strcpy(input_file,argv[pos+1]);
			} else if(strcmp(argv[pos],"-q") == 0) {
				query_file = malloc((strlen(argv[pos+1])+1)*sizeof(char));
				strcpy(query_file,argv[pos+1]);
			} else if(strcmp(argv[pos],"-o") == 0) {
				output_file = malloc((strlen(argv[pos+1])+1)*sizeof(char));
				strcpy(output_file,argv[pos+1]);
			} else if(strcmp(argv[pos],"-k") == 0) {
				K = atoi(argv[pos+1]);
			} else if(strcmp(argv[pos],"-M") == 0) {
				M = atoi(argv[pos+1]);
			} else if(strcmp(argv[pos],"-N") == 0) {
				N = atoi(argv[pos+1]);
			} else if(strcmp(argv[pos],"-R") == 0) {
				R = atof(argv[pos+1]);
			} else if(strcmp(argv[pos],"-probes") == 0) {
				probes = atoi(argv[pos+1]);
			}

			pos = pos + 2;

		}

	}
	else {
		printf("Give the input_file:");
		input_file = malloc(MAX_LENGTH_WORD*sizeof(char));
		scanf("%s", input_file);
		printf("Give the query_file:");
		query_file = malloc(MAX_LENGTH_WORD*sizeof(char));
		scanf("%s", query_file);
		printf("Give the output_file:");
		output_file = malloc(MAX_LENGTH_WORD*sizeof(char));
		scanf("%s", output_file);
		printf("%s\n","For default values for k,M,N,R,probes give -1");
		printf("%s\n","Give the parameter K:");
		scanf("%d", &K);
		printf("%s\n","Give the parameter M:");
		scanf("%d", &M);
		printf("%s\n","Give the parameter probes:");
		scanf("%d", &probes);
		printf("%s\n","Give the parameter N:");
		scanf("%d", &N);
		printf("%s\n","Give the parameter R:");
		scanf("%lf", &R);

		if((K==-1)&&(M==-1)&&(probes==-1)&&(N==-1)&&(R==-1)) {

			K = 14;
			M = 10;
			probes = 2;
			N = 1;
			R = 10000;

		}

	}



  	fp = fopen(input_file,"r"); /*anoigw to arxeio input_file to opoio periexei to synolo eikonwn moy(Dataset)*/
	input_info(fp, &number_of_images, &distances);
	printf("number_of_images=%d distances=%d\n", number_of_images,distances);
	image_table = image_creation(fp, number_of_images, distances);
	srand(time(NULL));
	exit_memory_hypercube(query_file,input_file,output_file,fp,image_table,number_of_images);

	return 0;

}

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
  //to K kalo einai na einai >=2 kai <31
	int probes; //max plhuos koryfwn
	int number_of_images;
	image_node* image_table;
	bucket_hypercube** Hash_Table = NULL;

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
	image_table = image_creation(fp, number_of_images, distances);

	srand(time(NULL));

	int w = 0;

  int deigma = 1000; /*gia na brw to w pairnw ena deigma poy einai oi 1000 prwtes eikones*/
	int min_dist = 0;

  for (int i = 0; i < deigma; ++i) {
  	/*min_dist = briskw gia mia eikona thn apostash ths apo ton plhsiestero geitona ths sto deigma*/
		min_dist = brute_force(image_table, i, deigma, distances);
		w = w + min_dist;

  }

	w = w/deigma;
  w = w*4;

	int** s_h_tables = create_g(K, w, distances);  /*o s_h_tables perilambanei ta s kauemias apo tis h synarthseis*/

  fclose(fp);


	int m = power(2,27) - 5;  /*m = 2^27 - 5*/
	int exponent = 32/K;
	int Mconst = power(2,exponent);  /*M = 2^(32/K)*/

	int *m_modM;/*o pinakas aytos ua exei ola ta (m)modM poy ua xreiastw kata ton ypologismo twn h synarthsevn*/

	m_modM = create_mmodM(m, Mconst, distances);

	int *twopower = malloc(K*sizeof(int)); /*pinakas me dynameis toy 2 poy ua mas xreiastei gia na metatrepoyme to string se int*/

	for (int i = 0; i < K; i++) {
		if(i == 0) twopower[i] = 1;
		else
			twopower[i] = 2*twopower[i-1];
	}

	f_node **f_functions = create_f_trees(K);

  Hash_Table = bucket_hypercube_creation(image_table, number_of_images, K, f_functions, m_modM, distances, s_h_tables, w, Mconst, twopower);

  int table_size = power(2, K);

  int count = 0;
  bucket_hypercube *temp;
  for (int i = 0; i < table_size; i++) {
		temp = Hash_Table[i];
		while(temp != NULL)
		{
			count++;
			temp = temp -> next;
		}
  }
	printf("count = %d  number_of_images = %d\n", count, number_of_images);


	printf("\nPrint Trees:\n\n");
	for (int i = 0; i < K; i++) {
		printf("f%d:\n", i+1);
		print_tree(f_functions[i]);
		printf("\n");
	}



  //NA TSEKARISTOYN:EINAI OK
  free(m_modM);
	free(twopower);

  for (int i = 0; i < K; i++)
  	free(s_h_tables[i]);
  free(s_h_tables);

  for (int i = 0; i < K; i++)
  	free_tree(f_functions[i]);
	free(f_functions);


	exit_memory_hypercube(query_file,input_file,output_file,image_table,number_of_images,Hash_Table,K);

	return 0;

}

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
  //printf("w is %d\n", w);

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

  //printf("waiting to create Hash_Table...\n");
  Hash_Table = bucket_hypercube_creation(image_table, number_of_images, K, f_functions, m_modM, distances, s_h_tables, w, Mconst, twopower);
  //printf("Hash_Table created\n");
  int table_size = power(2, K);


	char command[MAX_LENGTH_WORD];
	char command2[MAX_LENGTH_WORD];


  while(1) {

		FILE *fp_qr = fopen(query_file,"r");
	  FILE *out = fopen(output_file,"a");

		int qr_number_of_im;
		int qr_dist;
    input_info(fp_qr, &qr_number_of_im, &qr_dist);
    //printf("qr_number_of_im=%d qr_dist=%d\n", qr_number_of_im, qr_dist);//to query_file exei 10000 eikones me diastaseis 784

		int *appr_NN = malloc(N*sizeof(int)); //periexei ta image_numbers twn plhsiesterwn geitonwn
		int *dist_NN = malloc(N*sizeof(int)); //periexei ta distances twn plhsiesterwn geitonwn apo to kaue query

		int *exct_NN = malloc(N*sizeof(int));
		int *exdist_NN = malloc(N*sizeof(int));

		image_node node;
		node.pixels = malloc(qr_dist*sizeof(int));
//////
		for (int i = 0; i < qr_number_of_im; i++) { //gia kaue eikona apo to query_file  //htan to qr_number_of_im sthn uesh toy 100

			fprintf(out,"Query: %d\n",i);

			for(int j = 0; j < qr_dist; j++) {  /*bale arxika ston pinaka pixels toy node ta pixels ths*/

				unsigned char b;
				fread(&b, sizeof(unsigned char), 1, fp_qr);
				int pixel = (int)b;
				node.pixels[j] = pixel;

			}

			for (int j = 0; j < N; j++) {
				appr_NN[j] = -1;
				dist_NN[j] = -1;
				exct_NN[j] = -1;
				exdist_NN[j] = -1;
			}

			////
			int pos = string01_of_image(&node, f_functions, K, m_modM, distances, s_h_tables, w, Mconst, twopower);
      /*to pos einai h uesh toy pinaka kat/smoy(toy hypercube) poy ua mpei h sygkekrimenh eikona toy query_file*/
      if(M > number_of_images) M = number_of_images;

			clock_t t;
			t = clock();
			approximeteNN_hypercube(node, pos, Hash_Table, table_size, distances, M, probes, N, appr_NN, dist_NN);
			t = clock() - t;
			double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds


			clock_t t1;
			t1 = clock();
	    exact_NN(node, image_table, number_of_images, distances, exct_NN, exdist_NN, N);
			t1 = clock() - t1;
			double time_taken1 = ((double)t1)/CLOCKS_PER_SEC;


      for (int j = 0; j < N; j++) {
				fprintf(out,"Nearest neighbor-%d: %d\n",j+1,appr_NN[j]);
				fprintf(out,"distanceHypercube: %d\n",dist_NN[j]);
				fprintf(out,"distanceTrue: %d\n",exdist_NN[j]);
      }

			fprintf(out,"tHypercube: %f\n",time_taken);
			fprintf(out,"tTrue: %f\n",time_taken1);

			fprintf(out,"%s\n","R-near neighbors:");
    		range_search_cube(Hash_Table,node, pos, table_size, distances, out, M, R,probes);

		}

//////
    free(node.pixels);
		fclose(fp_qr);
		fclose(out);

		free(appr_NN);
		free(dist_NN);
		free(exct_NN);
		free(exdist_NN);

		printf("%s\n","Type the name of new query file and new output file or type NO if you want to terminate the program");
		scanf("%s",command);

		if(!strcmp(command,"NO"))
			break;
		else {
			memset(query_file, 0, strlen(query_file));
			strcpy(query_file, command);   /*ua asxolhuw me neo query_file an moy zhthuei apo ton xrhsth*/

	    scanf("%s",command2);
			memset(output_file, 0, strlen(output_file));
			strcpy(output_file, command2);
		}


	}







	exit_memory_hypercube(query_file,input_file,output_file,image_table,number_of_images,Hash_Table,K,m_modM,twopower,s_h_tables,f_functions);

	return 0;

}

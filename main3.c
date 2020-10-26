#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "struct3.h"
#define MAX_LENGTH_WORD 500

int main(int argc, char** argv) {

	srand(time(NULL));

	int arguments_number = argc-1;

	FILE* inptr;
  FILE* outptr;

	image_node* image_table = NULL;
	int* K_clusters_num; //apouhkeyoyme ta arxika K kentroeidh poy ua paroyme apo ton kmeans++

	int number_of_images;
	int distances;

	char* input_file;
	char* configuration_file;
	char* output_file;
	char* method;
	int complete = 0; //an complete == 0(den dinetai sthn grammh entolwn) tote emfanizontai mono ta kentra
                    //an complete == 1(dinetai sthn grammh entolwn) tote emfanizontai ta kentra kai ta shmeia gia kaue cluster
  int pos = 1;
	if(arguments_number%2 == 0) arguments_number--; //an den exei dwuei to complete

  while (pos <= arguments_number) {

		if(strcmp(argv[pos],"-i") == 0) {
			input_file=malloc((strlen(argv[pos+1])+1)*sizeof(char));
			strcpy(input_file,argv[pos+1]);
			if(pos == 8) break;
			pos = pos + 2;
		} else if(strcmp(argv[pos],"-c") == 0) {
			configuration_file=malloc((strlen(argv[pos+1])+1)*sizeof(char));
			strcpy(configuration_file,argv[pos+1]);
			if(pos == 8) break;
			pos = pos + 2;
		} else if(strcmp(argv[pos],"-o") == 0) {
			output_file=malloc((strlen(argv[pos+1])+1)*sizeof(char));
			strcpy(output_file,argv[pos+1]);
			if(pos == 8) break;
			pos = pos + 2;
		} else if(strcmp(argv[pos],"-m") == 0) {
			method=malloc((strlen(argv[pos+1])+1)*sizeof(char));
			strcpy(method,argv[pos+1]);
			if(pos == 8) break;
			pos = pos + 2;
		} else if(strcmp(argv[pos],"-complete") == 0) {
			complete = 1;
			pos = pos + 1;
		}

  }

  //Diabazw tis parametroys apo to clusters.conf:
  FILE *conf_fp;
	conf_fp = fopen(configuration_file, "r");
  //gia systades(clustering):
  int num_of_clusters;
	//gia LSH:
	int L_LSH = 3;
	int k_LSH = 4;
	//gia Hypercube:
	int M_hypercube = 10;
	int k_hypercube = 3;
	int probes = 2;


  for (int i = 0; i < 6; i++) {

  	if(i == 0) fscanf(conf_fp,"%*s %d\n", &num_of_clusters);
		if(i == 1) fscanf(conf_fp,"%*s %d\n", &L_LSH);
		if(i == 2) fscanf(conf_fp,"%*s %d\n", &k_LSH);
		if(i == 3) fscanf(conf_fp,"%*s %d\n", &M_hypercube);
		if(i == 4) fscanf(conf_fp,"%*s %d\n", &k_hypercube);
		if(i == 5) fscanf(conf_fp,"%*s %d\n", &probes);

  }

	fclose(conf_fp);
  ////


	inptr = fopen(input_file,"r");
	input_info(inptr, &number_of_images, &distances);
	image_table = image_creation(inptr, number_of_images, distances);
	K_clusters_num = initialization_kmeans(num_of_clusters, image_table, number_of_images, distances); //efarmozoyme ton kmeans++
	exit_memory_cluster(input_file, configuration_file, output_file, method, inptr, image_table, number_of_images, K_clusters_num);


	return 0;


}

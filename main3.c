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
  //K_in* K_info_table=NULL;
	image_node* image_table = NULL;
	int* K_clusters_num=NULL; //apouhkeyoyme ta arxika K kentroeidh poy ua paroyme apo ton kmeans++

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
	outptr=fopen(output_file,"a");
	input_info(inptr, &number_of_images, &distances);
	image_table = image_creation(inptr, number_of_images, distances);
	K_clusters_num = initialization_kmeans(num_of_clusters, image_table, number_of_images, distances); //efarmozoyme ton kmeans++
  //o K_clusters_num exei tis ueseis toy image_table poy exoyn ta prwta num_of_clusters kentra


  image_node *kentroeidh = malloc(num_of_clusters*sizeof(image_node)); //ston pinaka kentroeidh ua exoyme ta pixels
  for (int i = 0; i < num_of_clusters; i++)                            //twn num_of_clusters kentroeidwn
  	kentroeidh[i].pixels = malloc(distances*sizeof(int));

	for (int i = 0; i < num_of_clusters; i++) {  /*ta prwta kentroeidh poy briskoyme me ton kmeans++ einai eikones toy Dataset,*/
		int position = K_clusters_num[i];          /*opote arxika bazoyme se kaue uesh toy pinaka kentroeidh, ta pixels ths kaue eikonas*/
		for (int j = 0; j < distances; j++) {      /*toy Dataset h opoia einai kentroeides*/
			kentroeidh[i].pixels[j] = image_table[position].pixels[j];
		}
	}

  int *assignments = malloc(number_of_images*sizeof(int));  /*ston pinaka assignments ua exw akeraioys sto [0,num_of_clusters-1]*/
                                                            /*p.x. an sthn uesh assignments[2] exw thn timh 3,ayto shmainei oti*/
                                                            /*h eikona image_table[2] exei anateuei sto kentroeides kentroeidh[3]*/

	if(!strcmp(method,"Classic")) {

		for (int i = 0; i < number_of_images; i++)
			assignments[i] = -1;

		for (int i = 0; i < 1; i++) { //i < 20
			//BHMA ANAUESHS:
			Lloyds(assignments, image_table, kentroeidh, number_of_images, num_of_clusters, distances);
			//K_info_table=assignment_LLOYDS(num_of_clusters,image_table,K_clusters_num,number_of_images,distances);
			//BHMA UPDATE:
		}

	} else if(!strcmp(method,"LSH")) {

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

		int*** s_L_tables = create_s_numbers_ofLtables(L_LSH, k_LSH, w, distances);

		int m = power(2,27) - 5;  /*m = 2^27 - 5*/
		int exponent = 32/k_LSH;
		int M = power(2,exponent);  /*M = 2^(32/K)*/

		int *m_modM;
		m_modM = create_mmodM(m, M, distances);

		int table_size;
		bucket*** bucket_ptr_table = Hash_Table_Creation(image_table, L_LSH, number_of_images, k_LSH, m_modM, distances, s_L_tables, w, M, &table_size);
		///////////

    unsigned int g_value;
		int position;

		for (int i = 0; i < 1; i++) {  //ua kanw 20 fores ta bhmata anauesh-enhmerwsh toy algoriumoy

			for (int j = 0; j < number_of_images; j++) //arxikopoiw kaue fora ton assignments me -1
				assignments[j] = -1;
			//BHMA ANAUESHS:
			for (int j = 0; j < num_of_clusters; j++) { /*gia kaue kentroeides*/
        for (int k = 0; k < L_LSH; k++) {  /*gia to kentroeides kentroeidh[j] ypologizw gia kaue pinaka kat/smoy to g toy*/

          g_value = compute_g(&kentroeidh[j], k, k_LSH, m_modM, distances, s_L_tables, w, M);
					position = g_value%table_size;

					bucket *temp = bucket_ptr_table[k][position];

					while(temp != NULL) {  //anauetw tis eikones poy exoyn to idio g me to kentroeides moy sto kentroeides ayto

						int imagetable_pos = (temp -> image_info -> image_number) - 1;
						if(temp -> g == g_value) { //an h eikona exei idio g me to kentroeidh[j]
              if(assignments[imagetable_pos] == -1) //an h eikona den exei anateuei kapoy
								assignments[imagetable_pos] = j;    //thn bazw sto kentroeidh[j]
							else {  //alliws an symbainei collision prepei na thn balw sto kentroeides me to opoio exei thn mikroterh apostash
								int current = assignments[imagetable_pos];
								int curDist = manhattan_dist(&image_table[imagetable_pos], &kentroeidh[current], distances);
								int newDist = manhattan_dist(&image_table[imagetable_pos], &kentroeidh[j], distances);
								if(newDist < curDist) assignments[imagetable_pos] = j;
							}
						}
						temp = temp -> next;
					}

        }
			}
			//ua kanw Lloyd's gia osa den exoyn anateuei se kapoio kentroeides
			Lloyds(assignments, image_table, kentroeidh, number_of_images, num_of_clusters, distances);
		  //BHMA UPDATE:


		}
		//exw na apeleuerwsw mnhmh:
		freeLSH(m_modM, bucket_ptr_table, s_L_tables, L_LSH, k_LSH, table_size);

	} else if(!strcmp(method,"Hypercube")) {
		//
	}



	for (int i = 0; i < num_of_clusters; i++)
		free(kentroeidh[i].pixels);
	free(kentroeidh);

  free(assignments);

	exit_memory_Cluster(inptr,outptr,input_file,configuration_file,output_file,method,K_clusters_num,image_table,number_of_images);
	return 0;
}

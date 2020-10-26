#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include "struct3.h"
#define MAX_COUNT_WORD 50


void exit_memory_cluster(char* input_file,char* configuration_file,char* output_file,char* method,FILE* inptr,image_node* node,int num_img,int* Kmeans) {
	free(input_file);
	free(configuration_file);
	free(output_file);
	free(method);
	free(Kmeans);
	fclose(inptr);
	for(int i=0;i<num_img;i++)
		free(node[i].pixels);
	free(node);
}



double randfrom(double min, double max)
{
    double range = (max - min);
    double div = RAND_MAX / range;
    return min + (rand() / div);
}


int* initialization_kmeans(int K, image_node* image_table, int number_of_images, int distances) {
  //opoy K einai o ariumos twn clusters
	srand(time(NULL));

	int* K_clust = malloc(K*sizeof(int)); //pinakas me ta num_of_clusters se ariumo arxika kentra poy ua epilejw efarmozwntas ton kmeans++
	int first_K = rand()%number_of_images; //epilegw tyxaia to prvto kentro

	//image_node first_img = image_table[first_K]; //MALLON DEN XREIAZETAI6666^^^^^66666666666666^66^^^^^^^^^^^^^^^^^^^^^^????????????

	int* D = malloc(number_of_images*sizeof(int)); //pinakas me ta D(i)

	D[first_K] = -1;  //se kaue kentro bazw D(i) = -1
	int t = 1; //to t einai o ariumos twn kentrwn poy exw brei mexri stigmhs

	while(1) {

		if(t == K) //an exw brei ta K kentra teleiwsa
			break;

		int coun_K = 0;
		int* pos_first = NULL; //pinakas poy ua exei ta kentra poy exw brei mexri stigmhs

		for (int j = 0; j < number_of_images; j++) { //tsekarw mia-mia tis ueseis toy D
			if(D[j] == -1) {    //an brhka kentroeides
				pos_first = realloc(pos_first, (coun_K+1)*sizeof(int)); //to prosuetw ston pos_first
				pos_first[coun_K++] = j;
				if(coun_K == t) break;
			}
		}


    int max = -1;

		for (int l = 0; l < number_of_images; l++) { //gia kaue mh kentroeides caxnw na brw thn minimum apostash toy apo kapoio kentro
			if(D[l] == -1) //an eimai se kentroeides synexise
				continue;
			int min = INT_MAX;
			for (int e = 0; e < coun_K; e++) {
				int apostasi = manhattan_dist(&image_table[l], &image_table[pos_first[e]], distances);
				if(apostasi < min)
					min = apostasi;
			}
			D[l] = min;
			if(D[l] > max) max = D[l];
		}


		P* P_table = NULL; //pinakas me ta merika auroismata gia ta mh kentroeidh
		int coun2 = 0;

		for (int c = 0; c < number_of_images; c++) {
			if(D[c] == -1) //an eimai se kentroeides proxwraw
				continue;
			if(coun2 == 0) { //an eimai sto prwto mh kentroeides
				P_table = realloc(P_table, (coun2+1)*sizeof(P));
				P_table[coun2].img_num = c;
				P_table[coun2].P = (D[c]/max)*(D[c]/max);
				coun2++;
			}
			else { //an den eimai sto prwto mh kentroeides
				P_table = realloc(P_table,(coun2+1)*sizeof(P));
				P_table[coun2].img_num = c;
				P_table[coun2].P = P_table[coun2-1].P + (D[c]/max)*(D[c]/max);
				coun2++;
			}
		}

		float c = randfrom(0, P_table[coun2-1].P);

		for (int y = 0; y < coun2; y++) {
			if(c <= P_table[y].P) {
				D[P_table[y].img_num] = -1;
				break;
			}
		}

		free(P_table);
		free(pos_first);

		t+=1;

	}

	int size = 0;

	for (int y = 0; y < number_of_images; y++)
		if(D[y] == -1)
			K_clust[size++] = y;

	free(D);

	return K_clust;


}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include "struct3.h"
#define MAX_COUNT_WORD 50


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

	int* D = malloc(number_of_images*sizeof(int)); //pinakas me ta D(i)

  for (int i = 0; i < number_of_images; i++)
		D[i] = 0;

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

		Pnode* P_table = NULL; //pinakas me ta merika auroismata gia ta mh kentroeidh
		int coun2 = 0;
    //Pnode* P_table = malloc((number_of_images-t)*sizeof(Pnode)); //pinakas me ta merika auroismata gia ta mh kentroeidh

		for (int c = 0; c < number_of_images; c++) {
			if(D[c] == -1) //an eimai se kentroeides proxwraw
				continue;
			if(coun2 == 0) { //an eimai sto prwto mh kentroeides
				P_table = realloc(P_table, (coun2+1)*sizeof(Pnode));
				P_table[coun2].img_num = c;
				P_table[coun2].P = ((double)D[c]/(double)max)*((double)D[c]/(double)max);
				//if(t==4) printf("P_table[%d].P = %f\n", coun2, P_table[coun2].P);
				coun2++;
				if(coun2 == number_of_images - t) break;
			}
			else { //an den eimai sto prwto mh kentroeides
				P_table = realloc(P_table,(coun2+1)*sizeof(Pnode));
				P_table[coun2].img_num = c;
				P_table[coun2].P = P_table[coun2-1].P + ((double)D[c]/(double)max)*((double)D[c]/(double)max);
				//if(t==4) printf("P_table[%d].P = %f\n", coun2, P_table[coun2].P);
				coun2++;
				if(coun2 == number_of_images - t) break;
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
		{
			K_clust[size] = y;
      size++;
			if(size == K) break;
		}


	free(D);

	return K_clust;


}



/*K_in* assignment_LLOYDS(int K,image_node* image_table,int* Clusters_K,int number_of_images,int distances) {

	K_in* table = malloc(K*sizeof(K_in));

	for (int e = 0; e < K; e++) {
		table[e].img_assing = NULL;
		table[e].coun_img_assing = 0;
		table[e].K_clust = &image_table[Clusters_K[e]];
	}

	for (int i = 0; i < number_of_images; i++) {
		int pos;
		int min = INT_MAX;
		for (int h = 0; h < K; h++) {
			image_node* kentroeides = table[h].K_clust;
			int man_dist = manhattan_dist(kentroeides,&image_table[i],distances);
			if(man_dist < min) {
				pos = h;
				min = man_dist;
			}
		}
		table[pos].img_assing = realloc(table[pos].img_assing,(table[pos].coun_img_assing+1)*sizeof(int));
		table[pos].img_assing[table[pos].coun_img_assing] = i+1;
		table[pos].coun_img_assing++;
	}

	return table;

}*/


void Lloyds(int *assignments, image_node* image_table, image_node *kentroeidh, int number_of_images, int num_of_clusters, int distances) {

  for (int j = 0; j < number_of_images; j++) { //gia kaue eikona poy antistoixei se kaue uesh toy assignments

    if(assignments[j] == -1) { //an den exei anateuei ayth h eikona se kapoio kentro
      int min = INT_MAX;
      int temp;
      for (int k = 0; k < num_of_clusters; k++) { //gia thn eikona image_table[j] caxnw na brw to kontinotero kentroeides se aythn
        temp = manhattan_dist(&image_table[j], &kentroeidh[k], distances);
        if(temp < min) {
          min = temp;
          assignments[j] = k;
        }
      }
    }

  }

}



void update(int *assignments, image_node* kentroeidh, image_node* image_table, int number_of_images, int num_of_clusters) {
//kentroeidh[0]
  int *array = malloc(num_of_clusters*sizeof(int)); //se ayton ton pinaka ua exw gia kaue kentroeides poses eikones toy anateuhkan
    //an p.x. array[3] = 35 ayto shmainei oti sto cluster me kentro to kentroeidh[3] toy exoyn anateuei 35 eikones
  for (int i = 0; i < num_of_clusters; i++)
    array[i] = 0;
  int cluster;

  for (int i = 0; i < number_of_images; i++) {
    cluster = assignments[i];
    array[cluster] = array[cluster] + 1;
  }

  ////array[3] = 4 --->kentroeidh[3] exw 4 eikones
  //eikona1(1,4,2,0,...)
  //eikona2(5,6,5,2,...)
  //eikona3(6,7,2,4,...)
  //eikona4(7,3,4,2,...)
//anwtabani(n/2) = anwtabani(4/2) = 2
  //neo kentroeides -->
  //-->1,5,6,7 --> 1<5<6<7
  // -->(5,4,4,...)
  //2,5,4 -->2<4<5


  free(array);

}



void freeLSH(int *m_modM, bucket ***bucket_ptr_table, int*** s_L_tables, int L_LSH, int k_LSH, int table_size) {

  free(m_modM);

  for (int i = 0; i < L_LSH; i++) {
    for (int k = 0; k < table_size; k++) {
      bucket* p = bucket_ptr_table[i][k];
      if(p == NULL)
        continue;
      bucket* i = p->next;
      while(1) {
        free(p);
        p = i;
        if(p == NULL)
          break;
        i = i->next;
      }
    }
    free(bucket_ptr_table[i]);
  }
  free(bucket_ptr_table);

  for (int i = 0; i < L_LSH; i++) {
    for (int a = 0; a < k_LSH; a++)
      free(s_L_tables[i][a]);
    free(s_L_tables[i]);
  }
  free(s_L_tables);


}



void exit_memory_Cluster(FILE* inptr,FILE* outptr,char* input_file,char* configuration_file,char* output_file,char* method,int* K_clusters_num,image_node* image_table,int image_number){
	fclose(inptr);
	fclose(outptr);
	free(input_file);
	free(configuration_file);
	free(output_file);
	free(method);
	free(K_clusters_num);
	/*for(int e=0;e<K;e++)
		free(K_info_table[e].img_assing);
	free(K_info_table);*/
	for(int i = 0; i < image_number; i++)
		free(image_table[i].pixels);
	free(image_table);
}

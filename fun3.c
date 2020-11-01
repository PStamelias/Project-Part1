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


int up_value_fun(int pos) {  //an pos = 7 epistrefei anwtabani(3,5) = 4
	float val = (double)pos/2.0; //an pos = 4 epistrefei anwtabani(2) = 2
	int g = (int)val;
	float y = (float)g +0.5;

	if(val >= y) return g+1;
	else return g;
}


void update(int *assignments, image_node* kentroeidh, image_node* image_table, int number_of_images, int num_of_clusters, int distances) {

	for (int k = 0; k < num_of_clusters; k++) { //gia kaue cluster
		for (int h = 0; h < distances; h++) { //gia kaue diastash toy

			int coun = 0;
			int* table_dist = NULL;
			for (int i = 0; i < number_of_images; i++) { //paw kai tsekarw kaue eikona
				if(assignments[i] == k) {  //an h eikona ayth anateuhke sto cluster k
					table_dist = realloc(table_dist,(coun+1)*sizeof(int));
					table_dist[coun] = image_table[i].pixels[h]; //bale to pixel ths h diastashs ths eikonas ston table_dist
					coun++;
				}
			}

			qsort( table_dist, coun, sizeof(int), compare ); //sortare ton table_dist kata ayjoysa seira
			int e = 0;
			int prev_val = -1;

			for (int g = 0; g < coun; g++) { //uelw tis diakrites times//to table_dist mporei na exei {0,1,4,4,8}, egv uelw to {0,1,4,8}
				if(table_dist[g] > prev_val) {
					e++;
					prev_val = table_dist[g]; //table_dist[e];<-----APORIA???????????????
				}
			}

      int upper_value = up_value_fun(e);
      e = 0;
			prev_val = -1;

			for (int g = 0; g < coun; g++) { //uelw tis diakrites times//to table_dist mporei na exei {0,1,4,4,8}, egv uelw to {0,1,4,8}
				if(table_dist[g] > prev_val) {
					e++;
					prev_val = table_dist[g]; //table_dist[e];<-----APORIA???????????????
				}
				if(e == upper_value) {
					kentroeidh[k].pixels[h] = prev_val;
					break;
				}
			}
			free(table_dist);

		}
	}

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


void freeHypercube(int **s_h_tables, int *m_modM, int *twopower, f_node **f_functions, bucket_hypercube **hash_table, int K, int *probes_array) {

  free(m_modM);
  free(twopower);
  free(probes_array);

  for (int i = 0; i < K; i++)
    free(s_h_tables[i]);
  free(s_h_tables);

  for (int i = 0; i < K; i++)
    free_tree(f_functions[i]);
  free(f_functions);

  int size = power(2, K);
	for(int i = 0; i < size; i++) {

		bucket_hypercube* e = hash_table[i];
		bucket_hypercube* k;

		while(1) {
			if(e == NULL)
			  break;
			k = e -> next;
			free(e);
			e = k;
		}

	}
	free(hash_table);

}



void exit_memory_Cluster(FILE* inptr,FILE* outptr,char* input_file,char* configuration_file,char* output_file,char* method,int* K_clusters_num,image_node* image_table,int image_number){
	fclose(inptr);
	fclose(outptr);
	free(input_file);
	free(configuration_file);
	free(output_file);
	free(method);
	free(K_clusters_num);

	for(int i = 0; i < image_number; i++)
		free(image_table[i].pixels);
	free(image_table);
}

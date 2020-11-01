#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include "struct2.h"



f_node **create_f_trees(int K) {

	f_node **f_functions = malloc(K*(sizeof(f_node*))); /*ua exw K synarthseis f(oses einai kai oi h)*/
	for (int i = 0; i < K; i++) {
		f_functions[i] = NULL;
	}

	return f_functions;
}




f_node* insert_f_tree(f_node *root, int newKey, int *val) { /*se ena BST poy einai antistoixo mias f paw na eisagw enan neo akeraio kai na epistrecw thn 0 'h 1 timh toy,*/
	                                           /*sthn periptwsh omws poy o akeraios aytos yparxei hdh sto dendro aplws epistrefw thn timh 0 'h 1 poy hdh exei*/
  int newValue;
	newValue = rand()%2; //newValue = 0 'h 1
  //printf("in insert_f_tree: newKey=%d random_newValue=%d\n", newKey, newValue);
  if(root == NULL) { //an to dendro den exei oute riza tote ftiaxnw thn riza
		root = malloc(sizeof(f_node));
		root -> key = newKey;
		root -> value = newValue;
		root -> l = NULL;
		root -> r = NULL;
		*val = newValue;
	  return root;
	}

	f_node *temp = root;

	while(1) //diatrexw to dendro eite mexri na brw idio key me to newKey eite mexri na brw poy ua topouethsw ena neo f_node me to newKey
	{
		if(temp -> key == newKey) //an brhka oti exw kombo me key idio me to newKey
		{	newValue = temp -> value; //tote epistrefw thn timh value toy komboy
			break;
		}
		if(newKey < temp -> key)
		{
			if(temp -> l == NULL)
			{
				temp -> l = malloc(sizeof(f_node));
				temp -> l -> key = newKey;
				temp -> l -> value = newValue;
				temp -> l -> l = NULL;
				temp -> l -> r = NULL;
				break;
			}
		  temp = temp -> l;
			continue;
		}
		if(newKey > temp -> key)
		{
			if(temp -> r == NULL)
			{
				temp -> r = malloc(sizeof(f_node));
				temp -> r -> key = newKey;
				temp -> r -> value = newValue;
				temp -> r -> l = NULL;
				temp -> r -> r = NULL;
				break;
			}
		  temp = temp -> r;
		}

	}

  *val = newValue;
  return root;

}





int string01_of_image(image_node *image, f_node **f_functions, int K, int *m_modM, int distances, int** s_h_tables, int w, int Mconst, int *twopower) {
	/*pairnei mia eikona kai epistrefei to string apo 0 kai 1 (to string to epistrefei se dekadiko)*/
  int result = 0;
  int *array = malloc(K*sizeof(int));

  int key; //exei thn timh hi(mias eikonas)
	int val; //einai 0 'h 1(einai h timh toy fi(hi(mias eikonas)))

	for (int i = 0; i < K; i++) {
		//printf("f%d:\n", i+1);
		key = compute_h(image, m_modM, distances, s_h_tables[i], w, Mconst);
		f_functions[i] = insert_f_tree(f_functions[i], key, &val); //thn timh key ths hi(mias eikonas) thn bazw mesa
    array[i] = val;                                            //sthn fi kai apouhkeyw an moy epestrece 0 'h 1
		//printf("key = %d value = %d\n", key, val);
	} //twra sto array exw to string apo 0 kai 1

	//ua to metatrecw se dekadiko:
  for (int i = 0; i < K; i++)     //estw k = 4 kai to array moy einai to 1101 -> me ayth thn fora ua parw to dekadiko apotelesma toy
  	result = result + (array[i]*twopower[i]);  //1011 dhladh ua parw 11


  free(array);

  return result;

}





bucket_hypercube** bucket_hypercube_creation(image_node* image_table, int number_of_images, int K, f_node **f_functions, int *m_modM, int distances, int** s_h_tables, int w, int Mconst, int *twopower) { //dhmioyrgei ton hypercube

	bucket_hypercube** node = NULL;
	int size = power(2, K); //to megeuos toy pinaka(dhladh toy yperkyboy)einai oso to 2^K,giati an ta strings apo mhdenika
	                        //kai assoys poy antiproswpeyoyn mia koryfh exoyn megeuos K, ayto shmainei oti mporei na sxhmatistoyn
													//2^K diaforetika tetoia strings
	node = malloc(size*sizeof(bucket_hypercube*));

	for(int i = 0; i < size; i++)  //arxikopoiw tis ueseis toy pinaka me NULL
		node[i] = NULL;

	for(int i = 0; i < number_of_images; i++) {

		int pos = string01_of_image(&image_table[i], f_functions, K, m_modM, distances, s_h_tables, w, Mconst, twopower);
		bucket_hypercube* newNode = malloc(sizeof(bucket_hypercube)); //ftiaxnw ton neo kombo poy ua balw sto katallhlo bucket
		newNode->next = NULL;    //toy yperkyboy kai ua deixnei sthn antistoixh eikona image_table[i]
		newNode->image = &image_table[i];

		bucket_hypercube** start = &node[pos];

		if(*start == NULL)
			*start = newNode;
		else {
			bucket_hypercube* temp = *start;
			while(1) {
				if(temp->next == NULL) {
					temp->next = newNode;
					break;
				}
				temp = temp->next;
			}

		}

	}

	return node;

}




int hamming(int a, int b) { //briskei thn hamming apostash metajy twn akeraiwn a kai b

	int temp;
	int res = 0;

	temp = a^b; //aXORb

	while(temp > 0) {
		int tr = temp&1;
		res = res + tr;
		temp = temp >> 1;
	}

	return res;

}





void approximeteNN_hypercube(image_node query, int pos, bucket_hypercube** Hash_Table, int table_size, int distances, int M, int probes, int N, int *appr_NN, int *dist_NN) {
//oles oi ueseis twn appr_NN kai dist_NN ua exoyn arxika -1

  bucket_hypercube *temp = Hash_Table[pos];
  int hammingVar = 1;

  int *probes_array = malloc(probes*sizeof(int)); //o pinakas aytos ua exei toys geitones poy mporei na xreiastei na episkefuoyme
  //prepei opwsdhpote probes <= table_size-1
	for (int i = 0; i < probes; ) {  //ua gemisw mia-mia tis ueseis toy pinaka probes_array.Oi prvtes ueseis toy probes_array ua einai
																	 //ueseis toy pinaka kat/smoy me hamming apostash ish me 1 apo thn pos uesh,afoy ejantlhuoyn oi ueseis me
																	 //apostash hamming 1 ua akoloyuhsoyn oi ueseis me hamming apostash 2 kok
		for (int j = 0; j < table_size; j++) { //gia kaue uesh toy table_size
			if(j != pos) { //(an ayth h uesh den einai h uesh pos)
				if(hamming(j, pos) == hammingVar) {  //ejetazw an ayth h uesh exei hamming apostash ish me hammingVar(opoy hammingVar einai 1 arxika)
					probes_array[i] = j;
					i++;
					if(i == probes) break;
				}
			}
		}
		hammingVar++;

	}

  int countM = 0;
	int countProbes = 0;
	int newPos; //se periptwsh poy xreiastei na paw se kapoion geitona sto hypercube
  //...
	int new_appr;
	int new_dist;
  //...
	while(1) {

    if(temp != NULL) //den eimai se NULL pointer ara ejetazw mia ypochfia eikona
		{
			//...  to kommati ayto mporei na allajei sto range_search(to kommati mesa sta //...)
			new_appr = temp -> image -> image_number;
			new_dist = manhattan_dist(&query, temp -> image, distances);

			int keep = -1;

			for (int i = 0; i < N; i++) {
				if(dist_NN[i] == -1)
				{	dist_NN[i] = new_dist;
					appr_NN[i] = new_appr;
					break;
				}
				if(new_dist < dist_NN[i])
				{	keep = i;
					break;
				}
			}

			if(keep != -1)
			{
				for (int i = N-1; i >= keep; i--) {
					if(i == keep)
					{	dist_NN[i] = new_dist;
						appr_NN[i] = new_appr;
						break;
					}
					dist_NN[i] = dist_NN[i-1];
					appr_NN[i] = appr_NN[i-1];
				}
			}
			//...

			countM++;
			if(countM == M) break;  //ejetasa tis M ypochfies eikones ara bgainw apo to loop
			temp = temp -> next;
			continue;
		}
		if(countProbes == probes) break; //ejetasa oloys toys ypochfioys geitones ara bgainw apo to loop

		if(temp == NULL) //an to temp einai NULL shmainei oti prepei na paw se allon geitona
		{ newPos = probes_array[countProbes];
			temp = Hash_Table[newPos];
			countProbes++;
		}


	}


	free(probes_array);


}







void range_search_cube(bucket_hypercube** hash_table,image_node node, int pos, int table_size, int distances, FILE* out, int M, float R,int probes){
        bucket_hypercube* start = hash_table[pos];
        image* im_list = NULL;
        int done=0;
        while(1) {
                if(start==NULL)
                        break;
                if(size_list(im_list)==M) {
                        done=1;
                        break;
                }
                if(manhattan_dist(&node, start->image, distances) < R)
                        insert_list(&im_list, start->image->image_number);
                start=start->next;
        }
        if(done==1){
                print_list(im_list,out);
                return ;
        }
        int new_distance=M-size_list(im_list);
        int hamming_dist_curr=1;
        int end=0;
        int checked_nodes=0;
        int num_visited=0;
        while(1){
                for(int i=0;i<table_size;i++){
                        if(i==pos)
                                continue;
                        num_visited++;
                        if(num_visited==probes){
                                end=1;
                                break;
                        }
                        if(hamming(pos,i)==hamming_dist_curr){
                                bucket_hypercube* e=hash_table[i];
                                while(1){
                                        if(e==NULL)
                                                break;
                                        if(manhattan_dist(&node, e->image, distances) < R) {
                                                insert_list(&im_list, e->image->image_number);
                                                checked_nodes++;
                                                if(checked_nodes==new_distance){
                                                        end=1;
                                                        break;
                                                }
                                        }
                                        e=e->next;
                                }
                                if(end==1)
                                        break;
                        }
                }
                hamming_dist_curr+=1;
                if(end==1){
                        print_list(im_list,out);
                        break;
                }
        }
}







void print_tree(f_node *root) {
	if(root != NULL) {
		printf("key=%d value=%d\n", root -> key,root->value);
		printf("l of %d\n", root -> key);
		print_tree(root -> l);
		printf("r of %d\n", root -> key);
		print_tree(root -> r);
	}

}


void free_tree(f_node *node) { //eleyuerwnw ena dendro BST poy perilambanei tis times twn h kai ta
	if(node != NULL)             //values 0 'h 1 poy toys antistoixhuhkan(to BST antiproswpeyei mia f)
	{
		free_tree(node -> l);
		free_tree(node -> r);
		free(node);
	}
}



void exit_memory_hypercube(char* query_file,char* input_file,char* output_file,image_node* image_table,int number_of_images, bucket_hypercube** hash_table, int K,int* m_modM,int* twopower,int** s_h_tables,f_node** komvos){
	free(query_file);
	free(input_file);
	free(output_file);
	free(m_modM);
	free(twopower);
	for (int i = 0; i < K; i++)
  		free(s_h_tables[i]);
  	free(s_h_tables);

  	for (int i = 0; i < K; i++)
  		free_tree(komvos[i]);
		free(komvos);

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

	for(int i = 0; i < number_of_images; i++)
		free(image_table[i].pixels);
	free(image_table);

}

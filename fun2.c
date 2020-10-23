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

		image_node cur_im = image_table[i];
		int pos = string01_of_image(&cur_im, f_functions, K, m_modM, distances, s_h_tables, w, Mconst, twopower);
		bucket_hypercube* newNode = malloc(sizeof(bucket_hypercube)); //ftiaxnw ton neo kombo poy ua balw sto katallhlo bucket
		newNode->next = NULL;    //toy yperkyboy kai ua deixnei sthn antistoixh eikona image_table[i]
		newNode->image = &cur_im;

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



void exit_memory_hypercube(char* query_file,char* input_file,char* output_file,image_node* image_table,int number_of_images, bucket_hypercube** hash_table, int K) {
	free(query_file);
	free(input_file);
	free(output_file);


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

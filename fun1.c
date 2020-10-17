#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <inttypes.h>
#include "struct1.h"

image_node* image_creation(FILE* file, int number_of_images, int distances) {

	image_node* my_table;
	unsigned char b;

  my_table = malloc(number_of_images*sizeof(image_node));

	for(int i = 0; i < number_of_images; i++) {
		my_table[i].pixels = malloc(distances*sizeof(int));
		my_table[i].image_number = i+1;
	}

	for(int i = 0; i < number_of_images; i++)
		for(int j = 0; j < distances; j++) {
			fread(&b,sizeof(unsigned char),1,file); /*diabazw ena pixel(poy einai enas akeraios sto [0,255])*/
                                              /*to pixel to diabazw san unsigned char(ena pixel einai 1 byte)giati diaforetika mporei*/
                                              /*na moy dwsei arnhtiko apotelesma, pragma poy den uelw*/
			my_table[i].pixels[j] = (int)b; /*telos kanw cast to b se integer gia na to apouhkeysw sthn j-osth uesh*/
                                      /*toy pinaka pixels ths sygkekrimenhs eikonas i*/
		}

	return my_table;

}



int* create_hi(int w,int d) { /*Function returns a d-size table with values between [0,w-1](s numbers)*/

	int* my_table=malloc(d*sizeof(int));

	for(int i=0;i<d;++i)
		my_table[i]=rand()%w;

	return my_table;
}



int** create_g(int k,int w,int d) { /*Function that returns k-functions h-create hash_table*/
	int** my_table=malloc(k*sizeof(int*));

	for(int i=0;i<k;++i)
		my_table[i]=create_hi(w,d);


	return my_table;
}



int*** create_s_numbers_ofLtables(int L,int k,int w,int d) { /*Function that create L g hash tables*/
	int*** my_table=malloc(L*sizeof(int**));
                                              /*ayth h synarthsh dinei telika enan trisdiastato pinaka*/
	for(int i=0;i<L;++i)                        /*o opoios gia kaue synarthsh g(ua exoyme L se ariumo synarthseis g)*/
		my_table[i]=create_g(k,w,d);              /*dinei k*d akeraioys ariumoys s sto diasthma [0,w)(giati kaue synarthsh*/
                                              /*g apoteleitai apo k synarthseis h kai kaue synarthsh h xreiazetai d se*/
	return my_table;                            /*ariumo ariumoys s)*/
}


void input_info(FILE* file, int* number_of_im, int* sum) { /*me thn input_info diabazw apo to arxeio eisodoy toys 4 prwtoys akeraioys*/
                                                  /*kai epistrefv tis diastaseis ths kaue eikonas(grammes*sthles) kai*/
                                                         /*to poses eikones exw*/
	int magic_number;
	int number_of_images;
	int number_of_columns;
	int number_of_rows;


	fread(&magic_number,sizeof(int),1,file);
	magic_number = ((magic_number>>24)&0xff)|((magic_number<<8)&0xff0000)|((magic_number>>8)&0xff00)|((magic_number<<24)&0xff000000);
  /*oi 4 prvtoi akeraioi ariumoi toy arxeioy einai se big endian*/
  /*toys diabazw loipon se big endian kai gia na toys metatrecw se little endian*/
  /*kanw thn parapanw diadikasia se epipedo bitwise(kai an ta bytes se */
  /*big endian exoyn thn seira 0 1 2 3, me thn parapanw metatroph ginontai 3 2 1 0)*/

	fread(&number_of_images,sizeof(int),1,file); /*pairnw to plhuos twn eikonwn*/
	number_of_images = ((number_of_images>>24)&0xff)|((number_of_images<<8)&0xff0000)|((number_of_images>>8)&0xff00)|((number_of_images<<24)&0xff000000);
	fread(&number_of_rows,sizeof(int),1,file); /*pairnw ton ariumo twn grammwn poy exei mia eikona*/
	number_of_rows = ((number_of_rows>>24)&0xff)|((number_of_rows<<8)&0xff0000)|((number_of_rows>>8)&0xff00)|((number_of_rows<<24)&0xff000000);
	fread(&number_of_columns,sizeof(int),1,file); /*pairnw ton ariumo twn sthlwn poy exei mia eikona*/
	number_of_columns = ((number_of_columns>>24)&0xff)|((number_of_columns<<8)&0xff0000)|((number_of_columns>>8)&0xff00)|((number_of_columns<<24)&0xff000000);


	*number_of_im = number_of_images;
	*sum = number_of_rows*number_of_columns;

}



void exit_memory(char* query_file,char* output,char* input,int number_of_images,image_node* image_table,int L,int K,int*** L_tables,bucket*** bucket_ptr,int table_size){
	free(output);
	free(query_file);
	free(input);
	for(int i=0;i<L;i++){
		for(int k=0;k<table_size;k++){
			bucket* p=bucket_ptr[i][k];
			if(p==NULL)
				continue;
			bucket* i=p->next;
			while(1){
				free(p);
				p=i;
				if(p==NULL)
					break;
				i=i->next;
			}
		}
		free(bucket_ptr[i]);
	}
	free(bucket_ptr);
	for(int i=0;i<number_of_images;i++)
		free(image_table[i].pixels);
	free(image_table);
	for(int i=0;i<L;i++){
		for(int a=0;a<K;a++)
			free(L_tables[i][a]);
		free(L_tables[i]);
	}
	free(L_tables);
}


unsigned int  compute_g(image_node* image_table,int number_of_hash_table){
	int w=rand()%100000;
	return w;
}


bucket*** Hash_Table_Creation(image_node* image_table,int number_of_hash_tables,int number_of_images,int* table_siz){
	int choice=rand()%2;
	bucket*** bucket_ptrs=malloc(number_of_hash_tables*sizeof(bucket**));
	int table_size;
	if(choice==0)
		table_size=number_of_images/8;
	else
		table_size=number_of_images/16;
	for(int i=0;i<number_of_hash_tables;i++)
		bucket_ptrs[i]=malloc(table_size*sizeof(bucket*));
	for(int i=0;i<number_of_hash_tables;i++)
		for(int j=0;j<table_size;j++)
			bucket_ptrs[i][j]=NULL;
	for(int i=0;i<number_of_hash_tables;i++)
		for(int j=0;j<number_of_images;j++){
			bucket* p=malloc(sizeof(bucket));
			int g=compute_g(&image_table[j],i);
			p->g=g;
			p->next=NULL;
			p->image_info=&image_table[j];
			int pos=g%table_size;
			bucket** node=&bucket_ptrs[i][pos];
			if(*node==NULL)
				*node=p;
			else{
				bucket* temp=*node;
				while(1){
					if(temp->next==NULL){
						temp->next=p;
						break;
					}
					temp=temp->next;
				}

			}
		}
	*table_siz=table_size;
	return bucket_ptrs;
}



void range_search(image_node k,bucket*** Hash_Tables,int number_of_hash_tables,int table_size,FILE* out){
	image* im_list=NULL;
	for(int i=0;i<number_of_hash_tables;i++){
		int s=compute_g(&k,i);
		int pos=s%table_size;
		bucket** start=Hash_Tables[i];
	}
	print_list(im_list,out);
}

void insert_list(image** start,int img_num){
	image* i=malloc(sizeof(image));
	i->next=NULL;
	i->image=img_num;
	if(*start==NULL)
		*start=i;
	else{
		image* k=start;
		while(1){
			if(k->next==NULL){
				k->next=i;
				break;
			}
			k=k->next;
		}
	}
}
int search_list(image* start,int img_num){
	int found=0;
	image* k=start;
	while(1){
		if(k->image==img_num){
			found=1;
			break;
		}
		k=k->next;
	}
	return found;
}	
void print_list(image* start,FILE* out){
	int size=0;
	image* k=start;
	image* e=start;
	while(1){
		if(start==NULL)
			break;
		size++;
		start=start->next;
	}
	int* my_table=malloc(size*sizeof(int));
	int coun=0;
	while(1){
		if(k==NULL)
			break;
		my_table[coun++]=k->image;
		k=k->next;
	}
	qsort( my_table, size, sizeof(int), compare );
	free(my_table);
	image* g=e->next;
	while(1){
		free(e);
		e=g;
		if(e==NULL)
			break;
		g=g->next;
	}
}

int compare( const void* a, const void* b){
     int int_a = * ( (int*) a );
     int int_b = * ( (int*) b );

     if ( int_a == int_b ) return 0;
     else if ( int_a < int_b ) return -1;
     else return 1;
}


int manhattan_dist(image_node *image1, image_node *image2, int distances) {  /*Uelw na brw thn apostash Manhattan metajy*/
	                                                                           /*twn eikonwn image1 kai image2*/
  int distance = 0;
  int diff = 0;

	for (int i = 0; i < distances; i++) {
		/*gia kaue zeygari syntetagmenwn twn image1, image2 briskw thn*/
		/*apolyth timh ths diaforas toy kai thn prosuetw sto distances*/
		/*Apostash_Manhattan(image1,image2) = Auroisma_1<=i<=distances(|image1_xi-image2_yi|)*/

	  diff = (image1 -> pixels[i]) - (image2 -> pixels[i]);

		if(diff < 0) diff = diff*(-1); /*an to diff htan arnhtiko,to pollaplasiazw me -1 gia na parw thn apolyth timh toy*/

		distance = distance + diff;

	}

  return distance;

}


int brute_force(image_node* image_table, int i, int number_of_images, int distances) {  /*se ena plhuos number_of_images eikonwn briskw ton */
                                                                                  /*plhsiestero geitona sthn eikona yp'arithmon i kai */
                                                                                  /*epistrefw thn apostash ths eikonas i apo ton*/
																																				          /*plhsiestero geitona ths*/
	int min_dist = -1;  /*to min_dist ua periexei thn apostash metajy ths eikonas i kai toy plhsiesteroy geitona ths eikonas i*/
  int new_dist = 0;

  for (int j = 0; j < number_of_images; ++j) {

		if (j != i) { /*an ejetazw diaforetikh eikona apo thn i (gia na mhn brw thn apostash ths eikonas i me ton eayto ths)*/

			if (min_dist == -1) /*an einai h prwth eikona poy ejetazw, anagkastika to min_dist ua parei thn Apostash_Manhattan metajy ths i kai ths j*/
				min_dist = manhattan_dist(&image_table[i], &image_table[j], distances);

			else { /*an den einai h prwth eikona poy ejetazw*/
				new_dist = manhattan_dist(&image_table[i], &image_table[j], distances);
				if(new_dist < min_dist)  min_dist = new_dist;
			}

  	}

  }

	return min_dist;

}


int power(int number, int exponent) {  /*ypologizw to number^exponent*/

	if(exponent == 0) return 1;

	int result = 1;

	for(int i = 0; i < exponent; i++)
		result = result*number;

	return result;
}


int mod(int a, int b) {   /*to b ua einai panta dynamh toy 2(kai uetikos ariumos) kai gia*/
													/*dynameis toy 2 isxyei oti xmod(2^n) == x&((2^n) - 1)*/
	int result;
	int new_b = b - 1;

	result = a&new_b;

	return result;

}


int *create_mmodM(int m, int M, int distances) {

	int *m_modM = malloc(distances*sizeof(int));  /*o pinakas m_modM periexei me thn seira ta ejhs stoixeia:*/
																								/*1,mmodM,(m^2)modM,(m^3)modM,...,(m^(d-1))modM*/
																								/*Kaue stoixeio mporei na ypologisuei etsi: (m^x)modM = (m*m^(x-1))modM =*/
																								/*= ((mmodM)*((m^(x-1))modM))modM*/
  m_modM[0] = 1;

  m_modM[1] = mod(m,M);  //sto m_modM[1] exw to mmodM

	unsigned int product;

	for (int i = 2; i < distances; ++i) {
			product = (unsigned int)(m_modM[1]*m_modM[i-1]);
			m_modM[i] = mod((int)product,M);
	}

	return m_modM;

}
#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include "struct2.h"

void exit_memory(char* query_file,char* input_file,char* output_file,FILE* fp,image_node* image_table,int number_of_images){
	free(query_file);
	free(input_file);
	free(output_file);
	fclose(fp);
	for(int i=0;i<number_of_images;i++)
		free(image_table[i].pixels);
	free(image_table);
}
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
		//exw brei ta g1 g2 g3 (L = 3)//OXI   SE JEXVRH SYNARTHSH
    //topouethsh///OXI
	return my_table;

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
#include<stdio.h>
#include<stdlib.h>
#include <inttypes.h>
#include "struct1.h"
image_node* image_creation(char* input){
	int magic_number;
	FILE* file;
	int number_of_images;
	int number_of_rows;
	int number_of_columns;
	image_node* my_table;
	unsigned char b;
	file=fopen(input,"r");
	fread(&magic_number,sizeof(int),1,file);
	magic_number = ((magic_number>>24)&0xff)|((magic_number<<8)&0xff0000)|((magic_number>>8)&0xff00)|((magic_number<<24)&0xff000000);
	printf("magic_number=%d\n",magic_number);
	fread(&number_of_images,sizeof(int),1,file);
	number_of_images = ((number_of_images>>24)&0xff)|((number_of_images<<8)&0xff0000)|((number_of_images>>8)&0xff00)|((number_of_images<<24)&0xff000000);
	printf("number_of_images=%d\n",number_of_images);
	my_table=malloc(number_of_images*sizeof(image_node));
	fread(&number_of_rows,sizeof(int),1,file);
	number_of_rows = ((number_of_rows>>24)&0xff)|((number_of_rows<<8)&0xff0000)|((number_of_rows>>8)&0xff00)|((number_of_rows<<24)&0xff000000);
	fread(&number_of_columns,sizeof(int),1,file);
	number_of_columns = ((number_of_columns>>24)&0xff)|((number_of_columns<<8)&0xff0000)|((number_of_columns>>8)&0xff00)|((number_of_columns<<24)&0xff000000);
	printf("number_of_rows=%d\n",number_of_rows);
	for(int i=0;i<number_of_images;i++){
		my_table[i].pixels=malloc(number_of_columns*number_of_rows*sizeof(int));
		my_table[i].image_number=i+1;
	}
	for(int i=0;i<100;i++){
		printf("i=%d\n",i);
		for(int j=0;j<number_of_rows*number_of_columns;j++){
			printf("%s\n","enter");
			fread(&b,sizeof(unsigned char),1,file);
			my_table[i].pixels[j]=(int)b;
			printf("my_table[i].pixels[j]=%d\n",my_table[i].pixels[j]);
		}
	}
	fclose(file);
	return my_table;
}
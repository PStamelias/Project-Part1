#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "struct2.h"
#define MAX_LENGTH_WORD 500
int main(int argc,char** argv){
	int arguments_number=argc-1;
	int K,M,N;
	double R;
	int probes;
	int number_of_images;
	image_node* image_table;
	char* input_file;
	char* query_file;
	int distances;
	FILE *fp;
	char* output_file;
	if(arguments_number==16){
		int coun1=0;
		int coun2=0;
		int coun3=0;
		int coun4=0;
		int coun5=0;
		int coun6=0;
		int pos=1;
		int coun7=0;
		int coun8=0;
		while(1){
			if(!strcmp(argv[pos],"-d")&&coun1==0){
				input_file=malloc((strlen(argv[pos+1])+1)*sizeof(char));
				strcpy(input_file,argv[pos+1]);
				coun1=1;
			}
			else if(!strcmp(argv[pos],"-q")&&coun2==0){
				query_file=malloc((strlen(argv[pos+1])+1)*sizeof(char));
				strcpy(query_file,argv[pos+1]);
				coun2=1;
			}
			else if(!strcmp(argv[pos],"-k")&&coun3==0){
				K=atoi(argv[pos+1]);
				coun3=1;
			}
			else if(!strcmp("-M",argv[pos])&&coun4==0){
				M=atoi(argv[pos+1]);
				coun4=1;
			}
			else if(!strcmp("-probes",argv[pos])&&coun5==0){
				probes=atoi(argv[pos+1]);
				coun5=1;
			}
			else if(!strcmp("-R",argv[pos])&&coun6==0){
				R=atoi(argv[pos+1]);
				coun6=1;
			}
			else if(!strcmp("-N",argv[pos])&&coun7==0){
				N=atoi(argv[pos+1]);
				coun7=1;
			}
			else if(!strcmp("-o",argv[pos])&&coun8==0){
				output_file=malloc((strlen(argv[pos+1])+1)*sizeof(char));
				strcpy(output_file,argv[pos+1]);
				coun8=1;
			}
			pos++;
			if(coun1==1&&coun2==1&&coun3==1&&coun4==1&&coun5==1&&coun6==1&&coun7==1&&coun8==1)
				break;
		}
	}
	else{
		printf("Give the input_file:");
		input_file=malloc(MAX_LENGTH_WORD*sizeof(char));
		scanf("%s",input_file);
		printf("Give the query_file:");
		query_file=malloc(MAX_LENGTH_WORD*sizeof(char));
		scanf("%s",query_file);
		printf("Give the output_file:");
		output_file=malloc(MAX_LENGTH_WORD*sizeof(char));
		scanf("%s",output_file);
		printf("%s\n","For default values for k,M,N,R,probes give -1");
		printf("%s\n","Give the parameter K:");
		scanf("%d",&K);
		printf("%s\n","Give the parameter M:");
		scanf("%d",&M);
		printf("%s\n","Give the parameter probes:");
		scanf("%d",&probes);
		printf("%s\n","Give the parameter N:");
		scanf("%d",&N);
		printf("%s\n","Give the parameter R:");
		scanf("%lf",&R);
		if(K==-1&&M==-1&&probes==-1&&N==-1&&R==-1){
			K=3;
			M=10;
			probes=2;
			N=1;
			R=1.0;
		}
	}
  	fp = fopen(input_file,"r"); /*anoigw to arxeio input_file to opoio periexei to synolo eikonwn moy(Dataset)*/
	input_info(fp, &number_of_images, &distances);
	image_table = image_creation(fp, number_of_images, distances);
	srand(time(NULL));
	exit_memory(query_file,input_file,output_file,fp,image_table,number_of_images);
	return 0;
}
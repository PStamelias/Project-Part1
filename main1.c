#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LENGTH_WORD 500
int main(int argc,char** argv){
	int arguments_number=argc-1;
	int K,L,N;
	double R;
	char* input_file;
	char* query_file;
	char* output_file;
	if(arguments_number==14){
		int coun1=0;
		int pos=1;
		int coun2=0;
		int coun3=0;
		int coun4=0;
		int coun5=0;
		int coun6=0;
		int coun7=0;
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
			else if(!strcmp(argv[pos],"-L")&&coun4==0){
				L=atoi(argv[pos+1]);
				coun4=1;
			}
			else if(!strcmp(argv[pos],"-N")&&coun5==0){
				N=atoi(argv[pos+1]);
				coun5=1;
			}
			else if(!strcmp(argv[pos],"-R")&&coun6==0){
				R=atoi(argv[pos+1]);
				coun6=1;
			}
			else if(!strcmp(argv[pos],"-o")&&coun6==0){
				output_file=malloc((strlen(argv[pos+1])+1)*sizeof(char));
				strcpy(output_file,argv[pos+1]);
				coun7=1;
			}
			pos++;
			if(coun1==1&&coun2==1&&coun3==1&&coun4==1&coun5==1&&coun6==1&&coun7==1)
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
		printf("%s\n","For default values for k,L,N,R give -1");
		printf("Give parameter K:");
		scanf("%d",&K);
		printf("Give parameter L:");
		scanf("%d",&L);
		printf("Give parameter N:");
		scanf("%d",&N);
		printf("Give parameter R:");
		scanf("%lf",&R);
		if(K==-1&&L==-1){
			K=4;
			L=5;
			N=1;
			R=1.0;
		}
	}
	printf("K=%d\n",K);
	printf("L=%d\n",L);
	printf("N=%d\n",N);
	printf("R=%f\n",R);
	printf("output_file=%s\n",output_file);
	printf("input_file=%s\n",input_file);
	printf("query_file=%s\n",query_file);
	free(output_file);
	free(query_file);
	free(input_file);
	return 0;
}
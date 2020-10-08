#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LENGTH_WORD 500
int main(int argc,char** argv){
	int arguments_number=argc-1;
	int pos=1;
	char* input_file;
	char* configuration_file;
	char* output_file;
	char* method;
	char* optional;
	int coun1=0;
	int coun2=0;
	int coun3=0;
	int coun4=0;
	int coun5=0;
	while(1){
		if(!strcmp("-i",argv[pos])&&coun1==0){
			input_file=malloc((strlen(argv[pos+1])+1)*sizeof(char));
			strcpy(input_file,argv[pos+1]);
			coun1=1;
		}
		else if(!strcmp("-c",argv[pos])&&coun2==0){
			configuration_file=malloc((strlen(argv[pos+1])+1)*sizeof(char));
			strcpy(configuration_file,argv[pos+1]);
			coun2=1;
		}
		else if(!strcmp("-o",argv[pos])&&coun3==0){
			output_file=malloc((strlen(argv[pos+1])+1)*sizeof(char));
			strcpy(output_file,argv[pos+1]);
			coun3=1;
		}
		else if(!strcmp("-m",argv[pos])&&coun4==0){
			method=malloc((strlen(argv[pos+1])+1)*sizeof(char));
			strcpy(method,argv[pos+1]);
			coun4=1;
		}
		else if(!strcmp("-complete",argv[pos])&&coun5==0){
			optional=malloc((strlen(argv[pos+1])+1)*sizeof(char));
			strcpy(optional,argv[pos+1]);
			coun5=1;
		}
		pos++;
		if(coun1==1&&coun2==1&&coun3==1&&coun4==1&&coun5==1)
			break;
	}
	printf("optional=%s\n",optional);
	printf("method=%s\n",method);
	printf("input_file=%s\n",input_file);
	printf("configuration_file=%s\n",configuration_file);
	printf("output_file=%s\n",output_file);
	return 0;
}
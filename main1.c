#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
#include "struct1.h"
#define MAX_LENGTH_WORD 500


int main(int argc,char** argv) {

	int arguments_number = argc-1; /*krataw to plhuos twn orismatwn(afairwntas to orisma ./lsh)*/
	int table_size=0;
	int K,L,N;
  double R;
  char command[MAX_LENGTH_WORD];
  bucket*** bucket_ptr_table; 
  int number_of_images=0; /*poses eikones exei to Dataset moy(to input_file moy dhladh)*/
  int distances = 0; /*poses einai oi diastaseis enos dianysmatos(mias eikonas dhladh)*/

	image_node* image_table;

	char* input_file;
	char* query_file;
	char* output_file;

	if(arguments_number != 0) { /*an exoyn douei ta orismata sthn grammh entolwn*/

     K = -1; /*arxikopoiw ta K, L se periptwsh poy den*/
		 L = -1; /*paroyn times apo thn grammh entolwn*/

		 for (int pos = 1; pos <= arguments_number-1; ) {  /*tsekarw ta pos = 1,3,5,7,9,11,13 giati se aytes tis*/
                                                       /*ueseis ua briskontai ta -d,-q,-k,-L,-o,-N,-R*/
			if(strcmp(argv[pos],"-d") == 0) {   /* an exw -d ayto shmainei oti to */
				input_file=malloc((strlen(argv[pos+1])+1)*sizeof(char)); /*epomeno orisma einai to input_file*/
				strcpy(input_file,argv[pos+1]);
			} else if(strcmp(argv[pos],"-q") == 0) { /*an exw -q*/
				query_file=malloc((strlen(argv[pos+1])+1)*sizeof(char));
				strcpy(query_file,argv[pos+1]);
			} else if(strcmp(argv[pos],"-o") == 0) { /*an exw -o*/
				output_file=malloc((strlen(argv[pos+1])+1)*sizeof(char));
				strcpy(output_file,argv[pos+1]);
			} else if(strcmp(argv[pos],"-k") == 0) { /*an exw -k*/
				K = atoi(argv[pos+1]);
			} else if(strcmp(argv[pos],"-L") == 0) { /*an exw -L*/
				L = atoi(argv[pos+1]);
			} else if(strcmp(argv[pos],"-N") == 0) { /*an exw -N*/
				N = atoi(argv[pos+1]);
			} else if(strcmp(argv[pos],"-R") == 0) { /*an exw -R*/
				R = atof(argv[pos+1]);
			}

			pos = pos + 2;

		 }

		 if((K == -1)&&(L == -1)) { /*an den douhke timh sta K,L tote*/
			 K = 4;                   /*sta K,L,N,R dinontai default times*/
			 L = 5;
			 N = 1;
			 R = 1.0;
		 }


	} else {  /*an den douhke kanena orisma sthn grammh entolwn kai ta zhtaei*/
            /*to programma kata thn diarkeia ths ekteleshs toy*/
		 printf("Give the input_file:");
		 input_file=malloc(MAX_LENGTH_WORD*sizeof(char));
		 scanf("%s",input_file);

		 printf("Give the query_file:");
		 query_file=malloc(MAX_LENGTH_WORD*sizeof(char));
		 scanf("%s",query_file);

		 printf("Give the output_file:");
		 output_file=malloc(MAX_LENGTH_WORD*sizeof(char));
		 scanf("%s",output_file);

		 printf("%s\n","For default values for k,L,N,R give -1 at k,L");

		 printf("Give parameter k:");
		 scanf("%d",&K);
		 printf("Give parameter L:");
		 scanf("%d",&L);

		 if((K == -1)&&(L == -1)) { /*an sta K,L douhhke -1 tote sta*/
			 K = 4;                   /*K,L,N,R dinontai default times*/
			 L = 5;
			 N = 1;
			 R = 1.0;
		 } else {    /*alliws synexise kanonika kai pare apo ton xrhsth kai tis times twn N kai R*/
			 printf("Give parameter N:");
			 scanf("%d",&N);
			 printf("Give parameter R:");
			 scanf("%lf",&R);
		 }

	}
	/*creating L hashtables*/
  FILE *fp;
  FILE* out;
  out =fopen(output_file,"a");
  fp = fopen(input_file,"r"); /*anoigw to arxeio input_file to opoio periexei to synolo eikonwn moy(Dataset)*/

	input_info(fp, &number_of_images, &distances); /*diabasa apo to input_file(diekths fp) toys 4 prwtoys akeraioys*/
	                                               /*kai phra poses eikones exei kai poses diastaseis exei ena dianysma(eikona)*/

  srand(time(NULL));

	int*** s_L_tables = create_s_numbers_ofLtables(L, K, 10, distances);  /*o s_L_tables perilambanei ta s sta opoia katalhgei kaue g synarthsh*/

	image_table = image_creation(fp, number_of_images, distances);

  fclose(fp); /*kleinw to arxeio input_file poy periexei to Dataset moy giati to exw diabasei ki exw topouethsei*/
              /*tis eikones poy perieixe to Dataset stis domes anazhthshs, dhladh toys pinakes katakermatismoy*/



	bucket_ptr_table=Hash_Table_Creation(image_table,L,number_of_images,&table_size);



	while(1){
		FILE* o=fopen(query_file,"r");
		int magic_num;
		int img_num;
		int rows_num;
		int columns_num;
		fread(&magic_num,sizeof(int),1,o);
		magic_num = ((magic_num>>24)&0xff)|((magic_num<<8)&0xff0000)|((magic_num>>8)&0xff00)|((magic_num<<24)&0xff000000);
		fread(&img_num,sizeof(int),1,o);
		img_num = ((img_num>>24)&0xff)|((img_num<<8)&0xff0000)|((img_num>>8)&0xff00)|((img_num<<24)&0xff000000);
		fread(&rows_num,sizeof(int),1,o);
		rows_num = ((rows_num>>24)&0xff)|((rows_num<<8)&0xff0000)|((rows_num>>8)&0xff00)|((rows_num<<24)&0xff000000);
		fread(&columns_num,sizeof(int),1,o);
		columns_num = ((columns_num>>24)&0xff)|((columns_num<<8)&0xff0000)|((columns_num>>8)&0xff00)|((columns_num<<24)&0xff000000);
		image_node node;
		node.pixels=malloc(columns_num*rows_num*sizeof(int));
		for(int i=0;i<img_num;i++){
			for(int j=0;j<columns_num*rows_num;j++){
				unsigned char b;
				fread(&b,sizeof(unsigned char),1,o);
				int pixel= (int)b; 
				node.pixels[j]=pixel;
			}
			clock_t t; 	
			t = clock(); 
			fprintf(out,"%s\n","R-near neighbors:");
			range_search(node,bucket_ptr_table,L,table_size,out,columns_num*rows_num,R);
			t = clock() - t; 
			double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
			fprintf(out,"Execution time of range_search=%f  sec\n",time_taken);
		}
		free(node.pixels);
		fclose(o);
		printf("%s\n","Type the name of new query file or type NO if you want to terminate the program");
		scanf("%s",command);
		if(!strcmp(command,"NO"))
			break;
		else{
			memset(query_file, 0, strlen(query_file));
			strcpy(command,query_file);
		}
	}
	fclose(out);
	exit_memory(query_file,output_file,input_file,number_of_images,image_table,L,K,s_L_tables,bucket_ptr_table,table_size); /*apeleyuerwnw thn mnhmh*/
	return 0;

}

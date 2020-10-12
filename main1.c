#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "struct1.h"
#define MAX_LENGTH_WORD 500

//CHANGE

int main(int argc,char** argv) {

	int arguments_number = argc-1; /*krataw to plhuos twn orismatwn(afairwntas to orisma ./lsh)*/

	int K,L,N;
  double R;

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

	image_table=image_creation(input_file);

  /*printf("\n\ninput_file = %s\n", input_file);
  printf("query_file = %s\n", query_file);
  printf("output_file = %s\n", output_file);
  printf("k = %d\n", K);
  printf("L = %d\n", L);
  printf("N = %d\n", N);
  printf("R = %lf\n", R);*/

	free(output_file);
	free(query_file);
	free(input_file);

	return 0;

}

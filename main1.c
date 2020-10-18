#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
#include "struct1.h"
#define MAX_LENGTH_WORD 500

//ALLAGH
int main(int argc,char** argv) {

	int arguments_number = argc-1; /*krataw to plhuos twn orismatwn(afairwntas to orisma ./lsh)*/

	int K,L,N;    /*to K prepei na einai toylaxiston 2(sthn prajh prepei na einai gyrw sto 4)*/
  double R;

  int number_of_images=0; /*poses eikones exei to Dataset moy(to input_file moy dhladh)*/
  int distances = 0; /*poses einai oi diastaseis enos dianysmatos(mias eikonas dhladh)*/
  int table_size = 0;

	image_node* image_table; /*einai enas pinakas megeuoys number_of_images poy periexei*/
	                         /*oles tis eikones poy diabasthkan apo to input_file*/

	bucket*** bucket_ptr_table; /*ua periexei toys ejwterikoys L pinakes katakermatismoy toy LSH*/

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

  fp = fopen(input_file,"r"); /*anoigw to arxeio input_file to opoio periexei to synolo eikonwn moy(Dataset)*/

	input_info(fp, &number_of_images, &distances); /*diabasa apo to input_file(diekths fp) toys 4 prwtoys akeraioys*/
	                                               /*kai phra poses eikones exei kai poses diastaseis exei ena dianysma(eikona)*/

	image_table = image_creation(fp, number_of_images, distances);

  srand(time(NULL));

	int w = 0; /*Uelw prwta na ypologisw to w*/
						 /*to w einai = (mesh apostash toy kaue shmeioy apo ton plhsiestero geitona)xparagwn*/
             /*opoy o paragwn einai kapoios akeraios ariumos sto diasthma [4,10]*/

  int deigma = 1000; /*gia na brw to w pairnw ena deigma poy einai oi 1000 prwtes eikones*/
	int min_dist = 0;

  for (int i = 0; i < deigma; ++i) {
  	/*min_dist = briskw gia mia eikona thn apostash ths apo ton plhsiestero geitona ths sto deigma*/
		min_dist = brute_force(image_table, i, deigma, distances);
		w = w + min_dist;

  }

	w = w/deigma;
  w = w*4; //to w bgainei peripoy 50000

	int*** s_L_tables = create_s_numbers_ofLtables(L, K, w, distances);  /*o s_L_tables perilambanei ta s sta opoia katalhgei kaue g synarthsh*/


  fclose(fp); /*kleinw to arxeio input_file poy periexei to Dataset moy giati to exw diabasei ki exw topouethsei*/
              /*tis eikones poy perieixe to Dataset stis domes anazhthshs, dhladh toys pinakes katakermatismoy*/

/////////////////////----------
  /*Se ayto to shmeio uelw na diabazw kaue eikona apo to image_table*/
	/*kai gia kaue pinaka katakermatismoy na ypologizw thn antistoixh synarthsh g*/
	/*p.x. ypologizw gia mia sygkekrimenh eikona ton unsigned int poy epistrefei h*/
  /*g2 vste na thn topouethsv sto katallhlo bucket ston 2o pinaka katakermatismoy*/

  int m = power(2,27) - 5;  /*m = 2^27 - 5*/
	int exponent = 32/K;
	int M = power(2,exponent);  /*M = 2^(32/K)*/

  int *m_modM;/*o pinakas aytos ua exei ola ta (m)modM poy ua xreiastw kata ton ypologismo twn h synarthsevn*/

	m_modM = create_mmodM(m, M, distances);



  bucket_ptr_table = Hash_Table_Creation(image_table, L, number_of_images, K, m_modM, distances, s_L_tables, w, M, &table_size);
  /*kataskeyasame toys L ejwterikoys pinakes katakermatismoy*/
////////////////////////////////////////////////////////////

	FILE* out;
  out =fopen(output_file,"a");

	char command[MAX_LENGTH_WORD];

	//operation
while(1) {

	FILE *fp_qr = fopen(query_file,"r");

	int qr_number_of_im;
	int qr_dist;

	image_node node;
  input_info(fp_qr, &qr_number_of_im, &qr_dist);
  //printf("qr_number_of_im=%d qr_dist=%d\n", qr_number_of_im, qr_dist);//to query_file exei 10000 eikones me diastaseis 784
	node.pixels = malloc(qr_dist*sizeof(int));

	for(int i = 0; i < 100; i++) { /*gia kaue eikona apo to query_file*///anti gia 100 eixa qr_number_of_im

		for(int j = 0; j < qr_dist; j++) {  /*bale arxika ston pinaka pixels toy node ta pixels ths*/

			unsigned char b;
			fread(&b, sizeof(unsigned char), 1, fp_qr);
			int pixel = (int)b;
			node.pixels[j] = pixel;

		}
		fprintf(out,"%s\n","R-near neighbors:");

		clock_t t;
		t = clock();
		range_search(node, bucket_ptr_table, L, table_size, out, qr_dist, R, K, m_modM, distances, s_L_tables, w, M);
		t = clock() - t;

		double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
		fprintf(out,"Execution time of range_search=%f  sec\n",time_taken);

	}

	free(node.pixels);
	fclose(fp_qr);

	printf("%s\n","Type the name of new query file or type NO if you want to terminate the program");
	scanf("%s",command);

	if(!strcmp(command,"NO"))
		break;
	else {
		memset(query_file, 0, strlen(query_file));
		strcpy(query_file, command);   /*ua asxolhuw me neo query_file an moy zhthuei apo ton xrhsth*/
	}

}


fclose(out); //ISWS XREIASTEI ALLAGH TO OUTPUT FILE^^^^^^^^^^66666666666^^^^^^^^^







/*int souma = 0;
  for (int i = 0; i < L; i++) {
		int eswt = 0;
		printf("pin=%d\n", i+1);
  	for (int j = 0; j < table_size; j++) {

			bucket *temp = bucket_ptr_table[i][j];
			while(1)
			{ if(temp==NULL) break;
				souma = souma + 1;
				eswt = eswt + 1;
				//printf("image_number = %d  g%d = %u  bucket = %d\n", temp -> image_info -> image_number, i+1, temp -> g, j);
			  temp = temp -> next;
			}

  	}
		printf("eswt = %d\n", eswt);

  }

printf("souma = %d\n", souma);*/




	//for (int i = 0; i < number_of_images; i++) { /*gia kaue eikona toy Dataset*/

	//	printf("\n\nimage_number%d:\n", i+1);
		//for (int j = 0; j < L; j++) { /*gia kaue pinaka katakermatismoy(ston opoio ua topouethsv thn eikona i)*/
	//		g = compute_g(&image_table[i], j, K, m_modM, distances, s_L_tables, w, M); /*ypologizw to antistoixo g ths eikonas*/
	/*		if(g < 0) { printf("arnhtiko g\n");break;
		             }
      printf("g%d = %u\n", j+1, g);
		}
		if(g<0) break;

	}*/


  free(m_modM);  //PREPEI NA APELEYUERWSW TON m_MODM!!

  exit_memory(query_file, output_file, input_file, number_of_images, image_table, L, K, s_L_tables, bucket_ptr_table, table_size);
	/*apeleyuerwnw thn mnhmh*/


	return 0;

}

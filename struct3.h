#include "struct2.h"

typedef struct P_info {
	int img_num;
	float P;
} Pnode;

/*typedef struct K_Info {
	int* img_assing;
	int coun_img_assing;
	image_node* K_clust;
} K_in;*/

int* initialization_kmeans(int, image_node*, int, int);
double randfrom(double, double);
//K_in* assignment_LLOYDS(int K,image_node* images,int* info_K,int number_of_images,int distances);
void Lloyds(int *, image_node*, image_node *, int, int, int);
void freeLSH(int *, bucket ***, int***, int, int, int);
void exit_memory_Cluster(FILE* inptr,FILE* outptr,char* input_file,char* configuration_file,char* output_file,char* method,int* K_clusters_num,image_node* image_table,int image_number);

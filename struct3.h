#include "struct2.h"
void exit_memory_cluster(char* input_file,char* configuration_file,char* output_file,char* method,char* optional,FILE* inptr,image_node* node,int num_img,int* Kmeans);
void conf_info(char* configuration_file,int* K,int* number_of_vector_hash_tables,int* number_of_vector_hash_functions,int* max_number_M_hypercube,int* number_of_hypercube_dimensions,int* number_of_probes);
int* initialization_kmeans(int K,image_node* image_table,int image_number);
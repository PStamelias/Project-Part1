#include "struct2.h"

typedef struct P_info {
	int img_num;
	float P;
} P;


void exit_memory_cluster(char*, char*, char*, char*, FILE*, image_node*, int, int*);
int* initialization_kmeans(int, image_node*, int, int);
double randfrom(double, double);

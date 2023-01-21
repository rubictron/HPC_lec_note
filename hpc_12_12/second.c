#include <stdio.h>
#include "omp.h"




int main() {

	int num_threads;

	omp_set_num_threads(omp_get_num_procs());
	#pragma omp parallel
		{int id = omp_get_thread_num(); 

	#pragma omp single 
		num_threads = omp_get_num_threads();
		}

		printf("%d \n",num_threads);

   return 0; 
}

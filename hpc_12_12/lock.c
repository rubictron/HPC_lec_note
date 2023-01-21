#include <stdio.h>
#include "omp.h"


int do_lots_of_work(int id){
int a;
	for(int i= 0;i<1000;i++){
		a += ;
	}
	return a;
}

int main() {

int id,tmp;
omp_lock_t lck;
omp_init_lock(&lck);
#pragma omp parallel private (tmp,id)
{
id = omp_get_thread_num();

// omp_set_lock(&lck);
	tmp = do_lots_of_work(id);
	printf("%d %d \n",id,tmp);
// omp_unset_lock(&lck); 
}

// omp_destroy_lock(&lck);


   return 0; 
}

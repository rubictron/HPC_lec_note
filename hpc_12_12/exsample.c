#include <stdio.h>
#include "omp.h"


int calculateArea(int r){

return r*r*(22/7);
}


int main() {

int id,tmp;
omp_lock_t lck;
omp_init_lock(&lck);	
int E[4];
#pragma omp parallel
{
	int i = 10*(omp_get_thread_num()+1);

	if(omp_get_thread_num()>1){
			i =40*(omp_get_thread_num()-1);
		}
	int a = calculateArea(i);

	
		E[omp_get_thread_num()] = a;
	

	printf("%d %d  %d\n",i,a,E[omp_get_thread_num()]);

		
}

omp_destroy_lock(&lck);	

printf("%d \n",(E[0]+E[1])*(E[2]+E[3]));

   return 0; 
}



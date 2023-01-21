#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){

	FILE *fp;
    int reader;
    char line[1000000];

	fp = fopen("file1.txt","r");

	if(fp == NULL ) {

		perror("doc1.txt:");
		printf("Error occured while opening. Error number is %d \n",errno);
		exit(0);

	}else{

		


      while(reader = fgets(line, sizeof(line), fp)){
      
      printf("%s",line );
      printf("...........................\n"); 

  }
  

		

		fclose(fp);




		
	}


return(0);
}
#include "headerParalell.h"


int main()
{   
	
	clock_t start, end;
  double cpu_time_used;
    
  start = clock();
  
  FILE* file = fopen("test2.txt", "r");
  char line[1000];

  char * regexString = "<a href=\"http://[^>]+>|<a href=\"https://[^>]+>";

  compileregex(regexString);
    

  char *reader;

  do{
      reader = fgets(line, sizeof(line), file);
      //printf("%s",line ); 
      findregex(line); 
  }
  while(reader);
   


  regfree(&regexCompiled);
  fclose(file);
   
   
  end = clock();

  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	 
  printf("\n\n Time is : %f s\n",cpu_time_used);

  return 0;
}
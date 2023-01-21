#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <regex.h>
#include <omp.h>
#include <pthread.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

size_t maxMatches = 20;
size_t maxGroups = 5;
regex_t regexCompiled;
regmatch_t groupArray[20];
unsigned int m;



int compileregex(char * regexString){
    if (regcomp(&regexCompiled, regexString, REG_EXTENDED))
    {
      printf("Could not compile regular expression.\n");
      return 1;
    }else{
        return 0;
    }
}



int findregex(char * cursor){
  int m =0;
        

        for (m = 0; m < maxMatches; m ++)
      {

      if (regexec(&regexCompiled, cursor, maxGroups, groupArray, 0))
        break;  // No more matches

      unsigned int g = 0;
      unsigned int offset = 0;


      for (g = 0; g < maxGroups; g++)
        {
          if (groupArray[g].rm_so == (size_t)-1)
            break;  // No more groups

          if (g == 0)
            offset = groupArray[g].rm_eo;

          char cursorCopy[strlen(cursor) + 1];
          strcpy(cursorCopy, cursor);
          cursorCopy[groupArray[g].rm_eo] = 0;

          printf(ANSI_COLOR_BLUE"Match %u, [%2u-%2u]: %s"ANSI_COLOR_RESET"\n",
                 m,
                 groupArray[g].rm_so, 
                 groupArray[g].rm_eo,
                 cursorCopy + groupArray[g].rm_so);
        }
        
      cursor += offset;
    }

}


void * threadFuncion(void * vtid){

    int x = *(int *)vtid;
    x=x-1;
  
   FILE* file = fopen("test.txt", "r");
  char line[500];
if(x>0)
fseek(file,x*sizeof(line),SEEK_SET);

  char *reader;

if(x<3){
    for(int l=0;l<5;l++){
      reader = fgets(line, sizeof(line), file);

      
      if(reader){

         // printf("tid:%d  : %s",x,line ); 
           findregex(line); 
      }
      else
      {
         
          break;
           
      }
      
   } 
}else{
    while (  reader = fgets(line, sizeof(line), file))
    {
       //printf("tid:%d  : %s",x,line ); 
        findregex(line); 
    }
    

}

  


  fclose(file);

  pthread_exit(0);

}


int main()
{   
  clock_t start, end;
  start = clock();


  int numOfThread =4;

  pthread_t  thread[numOfThread];

	
  double cpu_time_used;

  char * regexString = "<a href=\"http://[^>]+>|<a href=\"https://[^>]+>";

  compileregex(regexString);



  for(int t = 0;t<numOfThread;t++){

    pthread_create(&thread[t],NULL,threadFuncion,(void *)&t);

  }
    




   for(int t = 0;t<numOfThread;t++){
    pthread_join(thread[t],NULL);
  }

    regfree(&regexCompiled);
   
  end = clock();

  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	 
  printf("\n\n Time is : %f s\n",cpu_time_used);

  return 0;
}













 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <regex.h>
#include <omp.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


#define FILENAME "text.html"


int findregex(char * line);

    char * regexString = "<a href=\"http://[^>]+>|<a href=\"https://[^>]+>";
    size_t maxMatches = 5;
    size_t maxGroups = 20;
    regex_t regexCompiled;
    regmatch_t groupArray[20];
    unsigned int m;
    char * cursor;

int main(void)
{
  /* Open the file for reading */
  char *line_buf = NULL;
  size_t line_buf_size = 0;
  int line_count = 0;
  size_t line_size;
  FILE *fp = fopen(FILENAME, "r");
  if (!fp)
  {
    fprintf(stderr, "Error opening file '%s'\n", FILENAME);
    return EXIT_FAILURE;
  }

  /* Get the first line of the file. */
  line_size = getline(&line_buf, &line_buf_size, fp);

  /* Loop through until we are done with the file. */
  while (line_size > 1)
  {
    /* Increment our line count */
    line_count++;

    /* Show the line details */
    printf(ANSI_COLOR_YELLOW"line[%06d]:"ANSI_COLOR_RESET" chars=%06zd, buf size=%06zu, contents: %s\n", line_count,
        line_size, line_buf_size, line_buf);


        //findregex(line_buf);

    /* Get the next line */
    line_size = getline(&line_buf, &line_buf_size, fp);
  }





  /* Free the allocated line buffer */
  free(line_buf);
  line_buf = NULL;

  /* Close the file now that we are done with it */
  fclose(fp);

  return EXIT_SUCCESS;
}


int findregex(char * line){
  int m =0;
        cursor = line;

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

          printf(ANSI_COLOR_BLUE"Match %u, Group %u: [%2u-%2u]: %s"ANSI_COLOR_RESET"\n",
                 m,
                 g,
                 groupArray[g].rm_so, 
                 groupArray[g].rm_eo,
                 cursorCopy + groupArray[g].rm_so);
        }
      cursor += offset;
    }

}
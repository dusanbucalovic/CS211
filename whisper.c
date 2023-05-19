#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int
main (int argc, char *argv[])
{
  if (argc < 2)
    {
      printf ("...\n");
      return 0;
    }

  int i = 0, size = argc - 1;

  int len = 0;
  for (i = 1; i <= size; i++)
  {
    len = len + strlen(argv[i]) + 1;
  }
  len += 1;
 
  char *str = malloc (len*sizeof(char));
  strcpy(str, argv[1]);
  if(argc > 2){
    strcat (str, " ");
  }
 

  for (i = 2; i <= size; i++)
  {
    strcat (str, argv[i]);
    if (i < size)
	  {
	    strcat (str, " ");
	  }
  
  }

  for (int i = 0; str[i]; i++)
  {
    if (str[i] == '!')
	  {
	    str[i] = '.';
	  }
    else if (isalpha (str[i]))
	  {
	    str[i] = tolower (str[i]);
	  }
  }

  printf ("(%s)\n", str);
  free (str);
  return 0;
}





#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* values[] = {"88", "56", "28", "2", "25", "99", "18", "23", "42", "82", "95",
      "77", "45", "100", "13", "149", "125", "97", "120", "67", 0};
int cant_values = 21;

int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

int main(int argc, char const *argv[])
{
  short i = 0;
  int arr_size = atoi(argv[1]);
  int num_forks = cant_values / arr_size;

  pid_t pid = getpid();
  int greatest_value = 0;
  char** subset = (char**)malloc((arr_size + 1) * sizeof(char*));

  int index_slice = 0;
  int j = 0;
  for(i = 0; i < num_forks; i++)
  {
      if(pid > 0)//father
      {
        index_slice = arr_size * i;
        for(j = 0; j < arr_size; j++)
          subset[j] = values[i*arr_size+j];

        subset[arr_size] = '\0';

        pid = fork();
      }
  }

  if(pid == 0)
  {
    return execvp("./sort", subset);
  }
  else
  {
    int cpid = 0;
    short i = 0;
    int status = 0;
    int* status_arr = (int*)malloc(num_forks * sizeof(int*));
    for (i = 0; i < num_forks; i++)
    {
        cpid = wait(&status);
        status_arr[i] = WEXITSTATUS(status);
    }

    qsort(status_arr, num_forks, sizeof(int), cmpfunc);
    printf("The greatest of greatest is: %d\n", status_arr[num_forks-1]);
    free(status_arr);
    free(subset);
    exit(0);
  }
  return 0;
}

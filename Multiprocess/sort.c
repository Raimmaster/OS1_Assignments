#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

int main(int argc, char* argv[])
{
    int* subset = malloc((argc)*sizeof(int));
    int j;
    // printf("Cant: %d\n", argc);
    for(j = 0;j < argc; j++){
        subset[j] = atoi(argv[j]);
        // printf("num: %s\n", argv[j]);
    }

   qsort(subset, argc, sizeof(int), cmpfunc);

   printf("The greatest is: %d\n", (subset[argc - 1]));
   return subset[argc - 1];
}

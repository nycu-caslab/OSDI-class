 
#include <stdio.h>

typedef struct {
     char *data;
     int key;
} item;
 
item array[] = {
     {"Bill", 62},
     {"Hill", 60},
     {"Barcak", 42},
     {"Dicky", 105},
     {"W.", 1},
};
  
// Simple but buggy bubble sort
// Can you find the bugs?

void sort(item *a, int n)
{ 
      int i = 0, j = 0;
      int s;

      for(; i < n && s != 0; i++) {
               s = 0;
              for(j = 0; j < n; j++) {
                       if(a[j].key > a[j+1].key) {
                               item t = a[j];
                               a[j] = a[j+1];
                               a[j+1] = t;
                               s++;
                       }
               }
              n--;
       }
}
   
int main()
{

  // We include some conditionally compiles debug code to print out important data structures                                                                                   
  // Note that we use ifdefs to compile in the code using the flag name DEBUG                                                                                                   
  // gcc -g -o bug -DDEBUG buggy_sort1.c                                                                                                                                        

#ifdef DEBUG
  int i;

  printf("Test of Bubble Sort (bad code) Compiled: " __DATE__ " at " __TIME__ "\n");
  printf("This is line %d of file %s\n", __LINE__, __FILE__);

  for(i = 0; i < 5; i++)
    printf("TEST: Before sort array[%d] = {%s, %d}\n", i, array[i].data, array[i].key);
#endif

  sort(array,5);

#ifdef DEBUG
  for(i = 0; i < 5; i++)
    printf("TEST: After sort array[%d] = {%s, %d}\n", i, array[i].data, array[i].key);
#endif

    return(0);
}

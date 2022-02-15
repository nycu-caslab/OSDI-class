// FIRST BUG: uninitialized variable s -- set to 1

// No let's force the bug out into the open - but how?
// We used gdb to find if(a[j].key > a[j+1].key
// j+1 is beyond the array[] boundary - it is 4+1 = 5
// This causes a bus error. So let's fix it.

// SECOND BUG: Change for(j = 0; j < n; j++) { to for(j = 0; j < n - 1; j++) {

// OK. The second bug is more difficult to find but we found it using
// breakpoints and found that the inner loop does not run n times (5 times)
// Why, because of the  n--; line. It is a bug. It decrements n in antcipcatio
// of not have to go through the complete set of items.
// We still get a bus error.
// Let's comment out the line.

// THIRD BUG:    //  n--; commented this line out

// We used patching in gdb to change this without recompiling.

#include <stdio.h>

// Reading a byte beyond a byte array in this example lets the code run somewhat operationally
// normally. Errors occur at boundary conditions - i.e., at the edge of the data structure
// So lets increase the size of the data structure such that an illegal access will show up.
// Let's change data to a 4K array buffer. Any access beyond this boundary will show up.

#define SIZE 4096

typedef struct {
     char data[SIZE];
     int key;
} item;
 
item array[] = {
     {"Bill", 62},
     {"Hill", 60},
     {"Barcak", 42},
     {"John", 105},
     {"W.", 1},
};
  
// Simple but buggy bubble sort
// Can you find the bugs?
 
void sort(item *a, int n)
{ 
      int i = 0, j = 0;
      int s = 1;

      for(; i < n && s != 0; i++) {
               s = 0;
              for(j = 0; j < n-1 ; j++) {
                       if(a[j].key > a[j+1].key) {
                               item t = a[j];
                               a[j] = a[j+1];
                               a[j+1] = t;
                               s++;
                       }
               }
	      //  n--; commented this line out
       }
}
   
int main()
{

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

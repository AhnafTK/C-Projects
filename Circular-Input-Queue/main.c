#include<stdio.h>

int main(void){
    int array[10] = {0};
    float SUM = 0, avg = 0;
    int VALUES= 0, n = 0,INDEX_NEW = 0,INDEX_OLD = 0, NEWNUM = 0;
    int AVG_OVER;
   
    printf("Enter the number of values to be averaged over (N): "); // This is the total size of the array.
    scanf("%d", &n); // Gathers the total size of the array and stores it here.
    while(1){
        
        if (INDEX_NEW >= n){
             SUM = SUM - array[(INDEX_OLD++)%10];
        }
        printf("Enter a value: ");
        scanf("%d", &NEWNUM);
        array[(INDEX_NEW) % 10] = NEWNUM;
        SUM = SUM + NEWNUM;
        INDEX_NEW++;
        //VALUES = INDEX_NEW;
        avg = SUM/(INDEX_NEW - INDEX_OLD);   
        printf("Buffer contents:%4d %4d %4d %4d %4d %4d %4d %4d %4d %4d \n", array[0],array[1],array[2],array[3],array[4],array[5],array[6],array[7],array[8],array[9]);
        printf("Number of values entered: %d        Average over: %d       Average: %.2f    \n", INDEX_NEW,(INDEX_NEW - INDEX_OLD),avg);
        printf("sum: %f        new - old : %d       Average: %.2f    \n", SUM,(INDEX_NEW - INDEX_OLD),avg);

    }
}
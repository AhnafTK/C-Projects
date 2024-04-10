#include<stdio.h>

int main(void){
    int array[10] = {0};
    float SUM = 0, avg = 0;
    int VALUES= 0, n = 0,*pINDEX_NEW = &array[0],*pINDEX_OLD = &array[0], NEWNUM = 0, oldIncrement=0,AVG_OVER=0;
   
    printf("Enter the number of values to be averaged over (N): "); // This is the total size of the array.
    scanf("%d", &n); // Gathers the total size of the array and stores it here.
    while(1){
        
        if (VALUES>=n){
            pINDEX_OLD = &array[(oldIncrement++) % 10];
            SUM = SUM - *pINDEX_OLD;
            pINDEX_OLD++;
        }
        printf("Enter a value: ");
        scanf("%d", &NEWNUM); // get input
        pINDEX_NEW = &array[VALUES % 10]; // does the wrapping. when 10%10, points to &array[0]
        *pINDEX_NEW = NEWNUM; // add the input at the location in array that pINDEX_NEW is pointing to.
        pINDEX_NEW++; // The pointer shifts to the right.
        SUM=SUM+NEWNUM;
        VALUES++;
        AVG_OVER = (VALUES - oldIncrement);
        avg = SUM/AVG_OVER;   
        printf("Buffer contents:%4d %4d %4d %4d %4d %4d %4d %4d %4d %4d \n", array[0],array[1],array[2],array[3],array[4],array[5],array[6],array[7],array[8],array[9]);
        printf("Number of values entered: %d        Average over: %d       Average: %.2f    \n", VALUES,n,avg);    
    }
}
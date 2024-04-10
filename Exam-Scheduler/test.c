
#include <stdio.h>
#include <math.h>

unsigned long long int determineTestBitmask(int duration);
//unsigned long long int convertToBinary(int num);

typedef unsigned long long int uLLInt;
uLLInt week1[64] = {0};
uLLInt week2[64] = {0};
uLLInt binArray[64] = {0};
uLLInt orderedBin[64] = {0};
    uLLInt bitMask = 0x7FFFFFFFFFFFFFFF; 


uLLInt position = 224;
int day = 3;
int main(){
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    // gets the binary value of the position, but its flipped.
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    for (int i = 0 ; i<8; i++){
        binArray[i] = (position % 2);
        position = position / 2;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    // gets the flipped, and puts it in correct order. this is now ready to be put into the orderedBin array,
    // but needs to be shifted into the correct section.
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    int j = 0;
    for (int i = 7; i > 0; i--){
        orderedBin[j] = binArray[i];
        j++;

    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    // Place the orderedBin contents shifted correctly into week1/2 array
    // 1) get the day
    // 2) each day = 8 bits of movement
    // 3) set the index to correct place based on this and put the contents starting from there
    //////////////////////////////////////////////////////////////////////////////////////////////////////


/**
 * printing shit
 * 
 */
    printf("\n");

    for (int i = 0; i < 64 ; i++){
                printf("%lld ", orderedBin[i]);

    }
    printf("\n");
   // for (int i = 0; i < 8 ; i++){
                //printf("%lld ", binArray[i]);

    //}
    printf("\n");
}


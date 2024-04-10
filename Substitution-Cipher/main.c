
#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTH 26
/********************* Main Functions *************************/
void doFrequencyAnalysis(char *pCipherText, int *pCharFreq);
void sortFrequencyAddresses(int *pCharFreq, int **pAlphaSort);
void displayFrequencyAnalysis(int **pAlphaSort, int *pCharFreq);
void swapCipherTextChars(char *pCipher);
/********************* Helper methods ************************/
void bubbleSort(int **pAlphaSort);
void copyAddressToAlpha(int *pCharFreq, int **pAlphaSort);
void displayAlphaForTest(int **pAlphaSort);
void printCipher(char *pCipher);
/*************************************************************/
//Main function. Intializes the arrays and pointers. Runs in a while loop infinitly, until stopped by user.
int main(void){
    system("clear");
    char cipherText[] = "VX UST USZTT ALQSWNTM WPTNUWXWTP DJ DLZBVH, VNT HLM QVAFBTUT, UST MTQVNP HLM AWMMWNR UST FZWNUWNR ATQSLNWMA, LNP UST USWZP BLQGTP DVUS UST FZWNUWNR";
    while(1){
        int charFreq[MAX_LENGTH] = {0}, *alphaSort[MAX_LENGTH] = {'\0'}, **pAlphaSort = &alphaSort[0],*pCharFreq = &charFreq[0];
        char *pCipher = &cipherText[0];
        doFrequencyAnalysis(pCipher, pCharFreq);
        sortFrequencyAddresses(pCharFreq, pAlphaSort);
        printCipher(pCipher);
        displayFrequencyAnalysis(pAlphaSort, pCharFreq);
        swapCipherTextChars(pCipher);
    }
}
//Takes pointers to the cipher array and char frequency array. Uses ascii to determine the position of the letter being read in the charFreq array.
//By subtracting the current char by A (ascii 65), the result gives the appropiate index. position for the charfreq array.
//ex : I(73) - A(65) = 8, charfreq[8] is where occurances of I is stored
void doFrequencyAnalysis(char *pCipher, int *pCharFreq){
    while((*pCipher)!='\0'){
        if (*pCipher == ' ' || *pCipher == ',') pCipher++;
        *(pCharFreq+(*pCipher - 'A')) += 1; pCipher++;
    }
}
// sorts the frequency, then stores the addresses in alphasort
void sortFrequencyAddresses(int *pCharFreq, int **pAlphaSort){
    copyAddressToAlpha(pCharFreq,pAlphaSort); // copy the address of pCharFreq into alphaSort
    bubbleSort(pAlphaSort);     // uses bubble sort to sort alpha sort array, greatest to least
}
//Used to display the frequency of the letters of the cipher text.
//Iterates through the addresses in the pAlpha and the addresses in pChar.
//Subtracts the two and adds 'A' to find the proper index. 
//double dereference to use the value to print.
void displayFrequencyAnalysis(int **pAlphaSort, int *pCharFreq){
    printf("\n\n=============== Frequencies ===============\n");
    for (int i = 0; i < MAX_LENGTH; i++){
        int result = *pAlphaSort - pCharFreq + 'A';
        printf(" %c : %d\n", result, **pAlphaSort);
        pAlphaSort++;
    }
}
//Method to perform a sorting in the Alpha sort array. Uses bubble sort, using greatest to least ordering.
void bubbleSort(int **pAlphaSort){
    for (int i = 0; i < MAX_LENGTH - 1; i++){
        for (int j = 0; j < ((MAX_LENGTH - 1) - i); j++){
            if (**(pAlphaSort + j) < **(pAlphaSort + (j + 1))){
                int *temp = *(pAlphaSort + j);
                *(pAlphaSort + j) = *(pAlphaSort + (j + 1));
                *(pAlphaSort + (j + 1)) = temp;
            }
        }
    }
}
//Copies the address of Char freq's into alphasort.
//Iterates 26 times, for each letter of the alphabets.
void copyAddressToAlpha(int *pCharFreq, int **pAlphaSort){
     for (int i = 0; i < MAX_LENGTH; i++){
        *pAlphaSort = pCharFreq; pAlphaSort++; pCharFreq++;
    }
}
//Prints the cipher text. Iterates through the text using pCipher, and continues until the value being read is \0
//while it runs, it prints the current value and increments the pointer.
void printCipher(char *pCipher){
    while(*pCipher!='\0'){
        printf("%c", *pCipher); pCipher++;
    }
}
//Swaps the text chars using two variables.toSwap: the variable being swapped.swapWith: swapping the toSwap with this.
//As it reads through the text using pCipher, if the value being read == swapWith, then swap it with toSwap. else if the value being read == toSwap, then replace with swapWith, this way the bidirectional swapping is done. then the pointer is incremented.
void swapCipherTextChars(char *pCipher){
    char toSwap = '0', swapWith = '0';
    printf("\nEnter a char to subsitute: "); scanf(" %c",&toSwap);
    printf("\nSwap this character with: "); scanf(" %c", &swapWith);
    while (*pCipher!='\0'){
        if (*pCipher == swapWith) *pCipher = toSwap;
        else if (*pCipher == toSwap) *pCipher = swapWith;
        pCipher++;
    }
}
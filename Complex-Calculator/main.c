#include <stdlib.h>
#include <stdio.h>
#include "MathOps.h"

#define Exit 0
#define Load 1
#define Copy 2
#define Display 3
#define Conjugate 4
#define Add 5
#define Subtract 6
#define Multiply 7
#define Divide 8

#define PROMPT_USER_TO(menuItem) printf("%d. %s complex numbers\n", menuItem, #menuItem);\

Complex stack[SIZE] = {0};
Complex *stackHead = &stack[1];
Complex *pc0 = &stack[0];
Complex *pc1 = &stack[1];
int headIndex = 1;

static int count = 0;
static int countOp = 0;
//struct Complex result = {0,0};
//Complex *pResult = &result;

// Forward declarations
// TODO: add other forward declarations, as required
static int displayMenu();
static void executeMenuItem(int menuItem);
static int chooseComplexNumberTo(char *);
static void display(Complex *pointerHead);

// DO NOT CHANGE THIS FUNCTION
int main(void){   
   int choice = Exit;
   printf("Welcome to the complex number calculator\n\n");
   do{
       choice = displayMenu();
 	   executeMenuItem(choice);
   } while (choice != Exit);

   printf("Program exited\n");
   exit(EXIT_SUCCESS);
}

// display menu options, prompt the user to enter a choice, and return the value selected
// DO NOT CHANGE THIS FUNCTION
static int displayMenu(){  
    int input = Exit;
    printf("Select one of the following:\n\n");
    PROMPT_USER_TO(Load)
    PROMPT_USER_TO(Copy)
    PROMPT_USER_TO(Display)
    PROMPT_USER_TO(Conjugate)
    PROMPT_USER_TO(Add)
    PROMPT_USER_TO(Subtract)
    PROMPT_USER_TO(Multiply)
    PROMPT_USER_TO(Divide)
    printf("%d. Exit Program\n", Exit);
    scanf("%d", &input);
    return input;
}

// DO NOT CHANGE THIS FUNCTION
static void executeMenuItem(int menuItem)
{
    Complex c = {0, 0};                                        // c is used for temporary storage of Complex numbers; it is not used in calculations
    static Complex c0 = {0, 0}, c1 = {0, 0}, cResult = {0, 0}; // Use these values for all operations below
    // Note that cResult is never used in calculations directly, only to store the result of calculations

    switch (menuItem)
    {
    case Exit:
        break; // do not edit this; 'Exit' is handled in the 'while' statement

    case Load: // load c0 or c1 with real and imaginary values
        c = loadComplex();
        stack[count % SIZE] = c;
        count++;
    
        break;

    case Copy:
        copy(stackHead);

        break;
    // display the content of the entire stack
    case Display: 
        display(stackHead);
        break;  

    case Conjugate:
        complexConjugate(stackHead);
        break;

    case Add: // add c0 + c1 and store to cResult
        stackHead = &stack[(headIndex++) % SIZE];
        pc1 = &stack[(headIndex-1)%SIZE];
        pc0 = &stack[(headIndex-2)%SIZE];
        *(stackHead) = performAdd(pc1,pc0);
        pc0->real = 0;
        pc0->imag = 0; 
        break;

    case Subtract: // subtract c1 - c0 and store to cResult
       stackHead = &stack[(headIndex++) % SIZE];
        pc1 = &stack[(headIndex-1)%SIZE];
        pc0 = &stack[(headIndex-2)%SIZE];
        *(stackHead) = performSubtract(pc1,pc0);
        pc0->real = 0;
        pc0->imag = 0;
    /**
       stackHead = &stack[(headIndex++) % SIZE];
        pc1 = &stack[(headIndex-1)%SIZE];
        pc0 = &stack[(headIndex-2)%SIZE];
        *(stackHead) = subtract(pc1,pc0);
        pc0->real = 0;
        pc0->imag = 0; 
        **/   
    break;

    case Multiply:
      stackHead = &stack[(headIndex++) % SIZE];
        pc1 = &stack[(headIndex-1)%SIZE];
        pc0 = &stack[(headIndex-2)%SIZE];
        *(stackHead) = performMultiply(pc1,pc0);
        pc0->real = 0;
        pc0->imag = 0;
        break;

    case Divide:
        stackHead = &stack[(headIndex++) % SIZE];
        pc1 = &stack[(headIndex-1)%SIZE];
        pc0 = &stack[(headIndex-2)%SIZE];
        *(stackHead) = performDivide(pc1,pc0);
        pc0->real = 0;
        pc0->imag = 0;
        break;

    default:
        printf("Bad menu value entered; ");
    }
    printf("\n");
}



// DO NOT CHANGE THIS FUNCTION
static int chooseComplexNumberTo(char *operation)
{
    int choice = 0;
    printf("\nWhich complex number do you wish to %s? (enter 0 or 1): ", operation);
    scanf("%d", &choice);
    return choice;
}

// TODO: add all additional funtions here, as specified above in the executeMenuItem() method.


// check the # decimal places it goes
static void display(Complex *pointerHead)
{

    //printf("DISPLAY STARTING WITH HEAD\n");
        for (int i = 0 ; i < 4; i++){
            char sign = (stack[(i + headIndex)%SIZE].imag >= 0.0)?'+':'-';
            printf("%lf %c %lfi \n",stack[(i+headIndex) % SIZE].real, sign, stack[(i+headIndex)%SIZE].imag = stack[(i+headIndex)%SIZE].imag < 0?stack[(i+headIndex)%SIZE].imag * -1:stack[(i+headIndex)%SIZE].imag);

   }
    
    
}


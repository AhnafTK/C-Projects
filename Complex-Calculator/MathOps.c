
#include <stdio.h>
#include "MathOps.h"
#include <assert.h>

extern Complex stack[SIZE]; // look for this variable elsewhere (main.c)
extern int headIndex; // look for this variable elsewhere (main.c)

Complex loadComplex()
{
    Complex cTemp;
    char sign;
    char i;
    printf("\tEnter complex number as'a + Bi' (e.g. 3.4 - 27.1i) : ");
    scanf("%lf %c %lf%c", &cTemp.real, &sign, &cTemp.imag,&i);
    if (sign == '-')
        cTemp.imag = -cTemp.imag;
    fflush(stdin);
    return cTemp;
}

void complexConjugate(Complex *pointer)
{
    pointer->imag = pointer->imag * -1;
}

Complex copy(Complex *stackHead){
    stackHead = &stack[SIZE-1]; // -> points to 3 
    stack[(headIndex+(SIZE-1)) % SIZE] = *stackHead; // -> 0 + 3 % 3 = 0, stack[0] = value at stackHead (which is value at stack[3])
    stackHead = &stack[SIZE-1]; // -> points to 3 
  
}

static Complex add(Complex *pC1, Complex *pC0){
    Complex cResult;
    Complex *pCResult = &cResult;
    cResult.real = pC1->real + pC0->real; // adding reals
    cResult.imag = pC1->imag + pC0->imag; // adding imag
    return *pCResult;
}

static Complex subtract(Complex *pointer1, Complex *pointer2){
    Complex cResult;
    Complex *pCResult = &cResult;
    cResult.real = pointer1->real - pointer2->real; // adding reals
    cResult.imag = pointer1->imag - pointer2->imag; // adding imag
    return *pCResult;
}

static Complex multiply(Complex *pointer1, Complex *pointer0){
    Complex cResult;
    Complex *pCResult = &cResult;
    cResult.real = ((pointer0->real * pointer1->real)-pointer0->imag*pointer1->imag);
    cResult.imag = ((pointer0->imag * pointer1->imag)+(pointer1->real*pointer0->imag));
    return *pCResult;
}
static Complex divide (Complex *pointer1, Complex *pointer0){

    Complex conjugated = *pointer0;
    Complex *pConj = &conjugated;
    complexConjugate(pConj);

    Complex nume = multiply(pointer1,pConj);
    Complex denom = multiply(pointer0,pConj);
    assert(denom.real > 0 || denom.imag > 0);

    printf("%lf %lf\n\n", conjugated.real, conjugated.imag);
    Complex cResult;
    Complex *pCResult = &cResult;
    

   // printf("%lf %lf\n", conjugated.real, conjugated.imag);

    cResult.real = nume.real / denom.real;
    cResult.imag = nume.imag / denom.real;
    return  *pCResult;
}

Complex performAdd(Complex *pC1, Complex *pC0){
    return add(pC1, pC0);
}
Complex performSubtract(Complex *pC1, Complex *pC0){
    return subtract(pC1, pC0);
}
Complex performMultiply(Complex *pC1, Complex *pC0){
    return multiply(pC1, pC0);
}
Complex performDivide(Complex *pC1, Complex *pC0){
    return divide(pC1, pC0);
}

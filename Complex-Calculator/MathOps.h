
typedef struct{
    double real;
    double imag;
} Complex;
#define SIZE 4


extern Complex copy(Complex *);
extern void complexConjugate(Complex *);
extern Complex loadComplex();

extern Complex performAdd(Complex *, Complex *);
extern Complex performSubtract(Complex *, Complex *);
extern Complex performMultiply(Complex *, Complex *);
extern Complex performDivide(Complex *, Complex *);



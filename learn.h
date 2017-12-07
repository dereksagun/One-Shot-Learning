#ifndef LEARN_H_
#define LEARN_H_

void print(double** xinput, double** yinput, int row, int col);
double ** x1(double** xinput, int row, int col);
double ** transpose(double** xinput, int row, int col);
void testprint(double** test, int row, int col);
void printfinal(double** final, int row);
double** inverse(double** matrix, int newcol);
double** multiply(double** m1, double** m2, int row1, int col1, int col2);


#endif

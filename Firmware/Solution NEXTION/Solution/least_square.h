/*
 * least_square.h
 *
 * Created: 01/09/2017 23:10:29
 *  Author: Rodolfo
 */ 


#ifndef LEAST_SQUARE_H_
#define LEAST_SQUARE_H_

void print_matrix(int m, int n, float A[][2]);
void print_vector_float(int m, float *b);
void print_vector_int(int m, int *b);
int QR(int m, int n, float A[][2], float *sigma, float *gamma, int *p);
int backrow(int n, float A[][2], float *b);
int permutation(int n, float *v, int *p, int inverse);
int solveLeastSquare(int m, int n, float A[][2], float *b, float *sigma, float *gamma, int *p, int r);
float residue(int m, int r, float *b);
void testLeastSquare();

#endif /* LEAST_SQUARE_H_ */
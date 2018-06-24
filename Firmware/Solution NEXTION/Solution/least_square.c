/*
 * least_square.c
 *
 * Created: 01/09/2017 22:58:52
 *  Author: Rodolfo
 */ 

 #include "indicator.h"
 #include "software_uart.h"
 #include "least_square.h"
 #include <math.h>

 void testLeastSquare() {
	 int m, n, p[MAX_CALIBRATION_POINTS], r;
	 float A[MAX_CALIBRATION_POINTS][2], b[MAX_CALIBRATION_POINTS], sigma[MAX_CALIBRATION_POINTS], gamma[MAX_CALIBRATION_POINTS];

	 m = 2;
	 n = 2;
	 A[0][0] = 1.0;
	 A[0][1] = 1.0;
	 A[1][0] = 1.0;
	 A[1][1] = 2.0;
	 
	 b[0] = 5.0;
	 b[1] = 8.0;

	 print_matrix(m, n, A);
	 softwareSerialPrint("\n\n");
	 //print_vector_float(m, a1);
	 //print_vector_float(m, a2);
	 print_vector_float(m, b);

	 //b = {5.0, 8.0};
//
	 r = QR(m, n, A, sigma, gamma, p);
	 solveLeastSquare(m, n, A, b, sigma, gamma, p, r);
//////
	 softwareSerialPrint("solucao de minimos quadrados: "); print_vector_float(n, b);
	 //softwareSerialPrint("residuo do sistema: "); printf("%g\n", residue(m, r, b));
 }

 void print_matrix(int m, int n, float A[][2]) {
	 int i, j;
	 for (i=0; i<m; i++) {
		 for (j=0; j<n; j++) {
			softwareSerialPrintFloat(A[i][j], 1);
			softwareSerialPrint(" ");
		}
		 softwareSerialPrint("\n");
	 }
 }

 void print_vector_float(int m, float *b) {
	 int i;
	 for (i=0; i<m; i++) {
		softwareSerialPrintFloat(b[i], 6);
		softwareSerialPrint(" ");
	}
	 softwareSerialPrint("\n");
 }

 void print_vector_int(int m, int *b) {
	 int i;
	 for (i=0; i<m; i++) {
		 softwareSerialPrintInt(b[i]);
		 softwareSerialPrint(" ");
	 }
	 softwareSerialPrint("\n");
 }

 int QR(int m, int n, float A[][2], float *sigma, float *gamma, int *p) {
	 int i, j, k=0, l, max_vetor;
	 float max, f, max_norma, aux;
	 /* laço que calcula a norma de todos os vetores da matriz */
	 for (j=0; j<n; j++) {
		 sigma[j] = 0.0;
		 for (i=0; i<m; i++) sigma[j] += fabs(A[i][j]*A[i][j]);
		 sigma[j] = sqrt(sigma[j]);
		 gamma[j] = 0.0;
		 p[j] = j;
	 }
	 /* laço externo que itera o algoritmo decomposição QR em toda a matriz A */
	 for (k=0; k<n; k++) {
		 max = 0.0;
		 /* se não é a primeira iteração, recalcula a norma dos vetores, com uma dimensão menor do que a iteração anterior */
		 if (k>0) for (j=k; j<n; j++) sigma[j] = sqrt(fabs(sigma[j]*sigma[j]-A[k-1][j]*A[k-1][j]));
		 /* laço que procura o vetor de maior norma da submatriz da iteração (para colocar os vetores de norma 0 à direita da matriz, se existirem) */
		 for (l=k, max_norma = sigma[l], max_vetor = l; l<n; l++) {
			 if (max_norma < sigma[l]) { max_norma = sigma[l]; max_vetor = l; }
		 }
		 if (max_norma <= EPSILON) return k;
		 /* troca os vetores de lugar, e armazena essa informação no vetor permutação p */
		 if (max_vetor != k) {
			 p[k] = max_vetor;
			 for (i=0; i<m; i++) {
				 aux = A[i][k];
				 A[i][k] = A[i][max_vetor];
				 A[i][max_vetor] = aux;
			 }
			 aux = sigma[k];
			 sigma[k] = sigma[max_vetor];
			 sigma[max_vetor] = aux;
		 }
		 /* seleciona o maior elemento em módulo do vetor, para normalizá-lo */
		 for (i=k; i<m; i++) if (fabs(A[i][k])>max) max = fabs(A[i][k]);
		 if (fabs(max) <= EPSILON) gamma[k] = 0.0;
		 else {
			 /* calcula e armazena o vetor u em cima da matriz A, e calcula e armazena o gamma em vetor separado */
			 for (i=k; i<m; i++) A[i][k] /= max;
			 sigma[k] /= max;
			 if (A[k][k] < 0) sigma[k] = (-1)*sigma[k];
			 A[k][k] += sigma[k];
			 gamma[k] = 1.0/(sigma[k]*A[k][k]);
			 sigma[k] *= max;
			 
			 /* aplica a matriz Q em todo o restante da matriz, sem calcular a matriz Q propriamente, e sim (a - gamma*u*(ut*a)), onde a são os vetores da matriz A */
			 for (j=k+1; j<n; j++) {
				 f = 0.0;
				 for (i=k; i<m; i++) f += A[i][k]*A[i][j];
				 f *= gamma[k];
				 for (i=k; i<m; i++) A[i][j] -= f*A[i][k];
			 }
		 }
	 }
	 /* o valor que essa função devolve é a dimensão de R11 */
	 return k;
 }

 int backrow(int n, float A[][2], float *b) {
	 int i, j;
	 for (i= n-1; i>=0; i--) {
		 for (j=n-1; j>i; j--) {
			 b[i] -= A[i][j]*b[j];
		 }
		 b[i] /= A[i][i];
	 }
	 return 0;
 }

 int permutation(int n, float *v, int *p, int inverse) { /* permuta os elementos do vetor de acordo com o vetor de permutação p */
	 int i;
	 float aux;
	 if (!inverse) {
		 for (i=0; i<n; i++) {
			 aux = v[p[i]];
			 v[p[i]] = v[i];
			 v[i] = aux;
		 }
		 } else {
		 for (i = n-1; i>=0; i--) {
			 aux = v[p[i]];
			 v[p[i]] = v[i];
			 v[i] = aux;
		 }
	 }
	 return 0;
 }

 int solveLeastSquare(int m, int n, float A[][2], float *b, float *sigma, float *gamma, int *p, int r) {
	 int i, j;
	 float f, aux;
	 /* aplica a matriz Q no vetor b, sem calcular a matriz Q propriamente, e sim (b - gamma*u*(ut*b)) */
	 for (j=0; j<r; j++) {
		 f = 0.0;
		 for (i=j; i<m; i++) f += A[i][j]*b[i];
		 f *= gamma[j];
		 for (i=j; i<m; i++) b[i] -= f*A[i][j];
	 }
	 /* coloca os (-sigma) na diogonal da matriz (reconstruindo a R) */
	 for (i=0; i<r; i++) {
		 aux = (-1) * sigma[i];
		 sigma[i] = A[i][i];
		 A[i][i] = aux;
	 }
	 /* se a matriz a for de posto-imcompleto, temos que minimizar || c - R11x1 - R12x2 ||, nesta implementação, suponho que x2 = 0, e resolvo o sistema c - R11x = 0 */
	 backrow(r, A, b);
	 /* laço que recoloca os (sigma) no vetor de sigma, e coloca os elemtos de u no lugar novamente */
	 for (i=0; i<r; i++) {
		 aux = sigma[i];
		 sigma[i] = (-1) * A[i][i];
		 A[i][i] = aux;
	 }
	 /* permuta o vetor da solução de mínimos quadrados */
	 permutation(r, b, p, 1);
	 return 0;
 }

 float residue(int m, int r, float *b) {
	 float resid = 0.0;
	 int i;
	 for (i=r; i<m; i++) {
		 resid += b[i]*b[i];
	 }
	 resid = sqrt(resid);
	 return resid;
 }

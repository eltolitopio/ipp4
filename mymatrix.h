#pragma once

#include <stddef.h>

struct matrix_private;
typedef struct matrix_private matrix;

int initmatrix(matrix **m, const int x, const int y);
int fillmatrix(matrix *const m);
int printmatrix(const matrix *const m);
double averagematrix(const matrix *const m);
int printaboveaveragematrix(const matrix *const m);
int submatrix(matrix *const a, const matrix *const b);
void freematrix(matrix *const m);

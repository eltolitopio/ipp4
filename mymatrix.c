#include "mymatrix.h"
#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SLEEP_EMULATOR
// #undef SLEEP_EMULATOR

struct matrix_private {
    int8_t **base;
    int x;
    int y;
};

#ifdef SLEEP_EMULATOR
// 500 mcs delay
const struct timespec rqtp = {0, 500000 * 0};
#endif

int initmatrix(matrix **m, const int x, const int y) {
    *m = (matrix *) malloc(sizeof(matrix));
    (*m)->base = (int8_t **) malloc(sizeof((*m)->base[0]) * (size_t) x);
    for (int i = 0; i < x; ++i) {
        (*m)->base[i] = (int8_t *) malloc(sizeof((*m)->base[0][0]) * (size_t) y);
    }
    (*m)->x = x;
    (*m)->y = y;
    return 0;
}

int fillmatrix(matrix *const m) {
    for (int i = 0; i < m->x; ++i) {
        for (int j = 0; j < m->y; ++j) {
            m->base[i][j] = rand() % (abs(CHAR_MIN) + CHAR_MAX) + CHAR_MIN;
        }
    }
    return 0;
}

int printmatrix(const matrix *const m) {
    for (int i = 0; i < m->x; ++i) {
        for (int j = 0; j < m->y; ++j) {
            printf("% 5d ", m->base[i][j]);
        }
        printf("\b\n");
    }
    return 0;
}

int submatrix(matrix *const a, const matrix *const b) {
#pragma omp parallel for collapse(2)
    for (int i = 0; i < a->x; ++i) {
        for (int j = 0; j < a->y; ++j) {
#ifdef SLEEP_EMULATOR
            /* hard work emulation */
            nanosleep(&rqtp, NULL);
#endif
            a->base[i][j] -= b->base[i][j];
        }
    }
    return 0;
}

double averagematrix(const matrix *const m) {
    double s = 0;
#pragma omp parallel for collapse(2) reduction(+ : s)
    for (int i = 0; i < m->x; ++i) {
        for (int j = 0; j < m->y; ++j) {
#ifdef SLEEP_EMULATOR
            /* hard work emulation */
            nanosleep(&rqtp, NULL);
#endif
            s += m->base[i][j];
        }
    }
    return s / (m->x * m->y);
}

int printaboveaveragematrix(const matrix *const m) {
    double average = averagematrix(m);
    printf("for average = %lf:\n", average);
    for (int i = 0; i < m->x; ++i) {
        for (int j = 0; j < m->y; ++j) {
            if (m->base[i][j] > average) {
                printf("[%d][%d] = %d\n", i, j, m->base[i][j]);
            }
        }
    }
    return 0;
}

void freematrix(matrix *const m) {
    for (int i = 0; i < m->x; ++i) {
        free(m->base[i]);
    }
    free(m->base);
    free(m);
}



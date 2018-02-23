#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include "definitions.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "matrix.h"

const decimal EPSD = 0.1;

decimal sigmoid(decimal x);
decimal logic_gate(decimal x);
decimal random_norm(decimal unused);
void print_mat(matrix x);

long encode_matl(matrix x, int code);
matrix decode_datal(long x, int code, int mat_len);

inline int HashFunc1(long x){ return x % 1000; }
inline decimal random_norm(){ return EPSD * (2.0 * (rand() / RAND_MAX) - 1); }
inline void srand_with_time(){ srand(time(nullptr)); }
inline decimal sqr_dec(decimal x){ return x * x; }
inline decimal sigmoid_deriv(decimal y){ return (1 - y) * y; }
inline long roundpos(decimal x){ return (long) (x +0.5); }
inline decimal abs_dec(decimal x){ return (x > 0) ? x : -x; }

inline int are_equal_dec(decimal x, decimal y, decimal eps){
    return (abs_dec(x - y) < eps) ? 1 : 0;
}


#endif // UTILS_H_INCLUDED



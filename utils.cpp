#include "utils.h"


decimal sigmoid(decimal x){
    return 1 / (1 + exp(-x));
}

decimal logic_gate(decimal x){
    return (x > 0.5) ? 1.0 : 0;
}

decimal random_norm(decimal unused){
    return EPSD * (2.0 * (((decimal)rand()) / RAND_MAX) - 1);
}

void print_mat(matrix x)
{
    int i, j;
    for (i = 0; i < x.m; i++){
        for (j = 0; j < x.n; j++)
            printf("%.4lf ", x.tab[i][j]);
        printf("\n");
    }
}


long encode_matl(matrix x, int code)
{
    long mult = 1;
    long res = 0;
    for (int i = x.n - 1; i >= 0; i--){
        res += roundpos(x.tab[0][i]) * mult;
        mult *= code;
    }
    return res;
}


matrix decode_datal(long x, int code, int mat_len)
{
    matrix res = matrix(1, mat_len);
    for (int i = mat_len - 1; i >= 0; i--){
        res.tab[0][i] = x % code;
        x /= code;
    }
    return res;
}



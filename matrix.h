#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include "definitions.h"


class matrix;

class buffer{
public:
    int ind1;
    matrix* mat;
    buffer(){};
    decimal &operator[](int index2);
};


class matrix{
public:
    int m, n;
    decimal **tab;

    matrix operator = (matrix);
    buffer operator[](int index1);
    matrix();
    matrix(int m, int n);
    matrix(matrix const& obj);
    ~matrix();
};

const matrix null_mat = {0, 0};

matrix operator + (matrix, matrix);
matrix operator - (matrix, matrix);
matrix operator * (matrix, matrix);
matrix operator * (matrix, decimal);
matrix operator * (decimal, matrix);
matrix operator & (matrix, matrix);
matrix operator ! (matrix);

matrix transfrm(matrix x, decimal (*f)(decimal));
matrix connect_mat(matrix a, matrix b);
matrix get_str(matrix x, int strn);
matrix plus_str(matrix x, matrix str);

decimal norm_square(matrix x);
decimal norm_abs(matrix x);



#endif // MATRIX_H_INCLUDED

#include "matrix.h"


matrix::matrix()
{
    tab = nullptr;
}


matrix::matrix(int strs, int cols)
{
    int i, j;
    m = strs;
    n = cols;
    tab = new decimal* [m];
    for (i = 0; i < m; i++){
        tab[i] = new decimal [n];
        for (j = 0; j < n; j++)
            tab[i][j] = 0;
    }
}


matrix::matrix(matrix const& obj)
{
    m = obj.m;
    n = obj.n;
    tab = new decimal* [m];
    for (int i = 0; i < m; i++){
        tab[i] = new decimal [n];
        for (int j = 0; j < n; j++)
            tab[i][j] = obj.tab[i][j];
    }
}


matrix::~matrix()
{
    for (int i = 0; i < m; i++)
        delete [] tab[i];
    delete [] tab;
}


matrix matrix::operator=(matrix x)
{
    int i, j;
    if (tab != nullptr){
        for (int i = 0; i < m; i++)
            delete [] tab[i];
        delete [] tab;
    }
    m = x.m;
    n = x.n;
    tab = new decimal* [m];
    for (i = 0; i < m; i++){
        tab[i] = new decimal [n];
        for (j = 0; j < n; j++)
            tab[i][j] = x.tab[i][j];
    }
    return *this;
}



buffer matrix::operator[](int index1)
{
    buffer buf;
    buf.ind1 = index1;
    buf.mat = this;
    return buf;
}

decimal &buffer::operator[](int index2)
{
    decimal &res = mat->tab[ind1][index2];
    return  res;
}



matrix operator+ (matrix a, matrix b)
{
    if (a.m != b.m || a.n != b.n){
        LOGE("Error: + ");
        return matrix(0, 0);
    }
    int i, j;
    matrix c = matrix(a.m, a.n);
    for (i = 0; i < c.m; i++)
        for (j = 0; j < c.n; j++)
            c.tab[i][j] = a.tab[i][j] + b.tab[i][j];
    return c;
}



matrix operator- (matrix a, matrix b)
{
    if (a.m != b.m || a.n != b.n){
        LOGE("Error: - ");
        return matrix(0, 0);
    }
    int i, j;
    matrix c = matrix(a.m, a.n);
    for (i = 0; i < c.m; i++)
        for (j = 0; j < c.n; j++)
            c.tab[i][j] = a.tab[i][j] - b.tab[i][j];
    return c;
}



matrix operator* (matrix a, matrix b)
{
    if (a.n != b.m){
        LOGE("Error: * ");
        return matrix(0, 0);
    }
    int i, j, k, km = a.n;
    matrix c = matrix(a.m, b.n);
    for (i = 0; i < c.m; i++)
        for (j = 0; j < c.n; j++){
            c.tab[i][j] = 0;
            for (k = 0; k < km; k++)
                c.tab[i][j] += a.tab[i][k] * b.tab[k][j];
        }
    return c;
}


matrix operator! (matrix x)
{
    int i, j;
    matrix y = matrix(x.n, x.m);
    for (i = 0; i < y.m; i++)
        for (j = 0; j < y.n; j++)
            y.tab[i][j] = x.tab[j][i];
    return y;
}


matrix operator* (matrix x, decimal mult)
{
    int i, j;
    for (i = 0; i < x.m; i++)
        for (j = 0; j < x.n; j++)
            x.tab[i][j] *= mult;
    return x;
}


matrix operator* (decimal mult, matrix x)
{
    int i, j;
    for (i = 0; i < x.m; i++)
        for (j = 0; j < x.n; j++)
            x.tab[i][j] *= mult;
    return x;
}


matrix operator& (matrix a, matrix b)
{
    if (a.m != b.m || a.n != b.n){
        LOGE("Error: & ");
        return matrix(0, 0);
    }
    matrix c = matrix(a.m, a.n);
    int i, j;
    for (i = 0; i < c.m; i++)
        for (j = 0; j < c.n; j++)
            c.tab[i][j] = a.tab[i][j] * b.tab[i][j];
    return c;
}



matrix connect_mat(matrix a, matrix b)
{
    if (a.n != b.n){
        LOGE("Error: , ");
        return matrix(0, 0);
    }
    matrix c= matrix(a.m + b.m, a.n);
    int i, j;
    for (i = 0; i < a.m; i++)
        for (j = 0; j < c.n; j++)
            c.tab[i][j] = a.tab[i][j];
    for (i = 0; i < b.m; i++)
        for (j = 0; j < c.n; j++)
            c.tab[a.m + i][j] = b.tab[i][j];
    return c;
}


matrix get_str(matrix x, int strn)
{
    matrix c = matrix(1, x.n);
    int i;
    for (i = 0; i < x.n; i++)
        c.tab[0][i] = x.tab[strn][i];
    return c;
}



matrix transfrm(matrix x, decimal (*f)(decimal))
{
    int i, j;
    for (i = 0; i < x.m; i++)
        for (j = 0; j < x.n; j++)
            x.tab[i][j] = f(x.tab[i][j]);
    return x;
}

matrix plus_str(matrix x, matrix str)
{
    if (x.n != str.n){
        LOGE("Error: plus str ");
        return matrix(0, 0);
    }
    int i, j;
    for (i = 0; i < x.m; i++)
        for (j = 0; j < x.n; j++)
            x.tab[i][j] += str.tab[0][j];
    return x;
}



decimal norm_square(matrix x)
{
    int i, j;
    decimal norm = 0;
    for (i = 0; i < x.m; i++)
        for (j = 0; j < x.n; j++)
            norm += x.tab[i][j] * x.tab[i][j];
    return norm;
}



decimal norm_abs(matrix x)
{
    int i, j;
    decimal norm = 0;
    for (i = 0; i < x.m; i++)
        for (j = 0; j < x.n; j++)
            norm += ((x.tab[i][j] > 0) ? x.tab[i][j] : -x.tab[i][j]);
    return norm;
}








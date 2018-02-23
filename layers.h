#ifndef LAYERS_H_INCLUDED
#define LAYERS_H_INCLUDED

#include "matrix.h"
#include "utils.h"

#define HAS_BIAS true
#define NO_BIAS false

class Layer{
    matrix dW;
public:
    bool has_bias;
    int n, next_n;     // neurons number
    matrix X;  //neuron values
    matrix W;  //weight
    matrix B;  //bias

    matrix pass_layer(matrix sign, decimal (*activ_func)(decimal));
    void change_weight(matrix err_grad, decimal study_spd, decimal am);
    matrix get_next_error_mat(matrix err_grad, decimal (*deriv_act_func)(decimal));
    void make_rand_weight_layer(int n_, int next_n_, bool has_bias_);

    Layer();
    Layer(Layer const& obj);
    Layer(int n_, int next_n_, matrix W_);
    Layer(int n_, int next_n_, matrix W_, matrix B_);
};



#endif // LAYERS_H_INCLUDED

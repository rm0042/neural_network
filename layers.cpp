#include "layers.h"


Layer::Layer(){}



Layer::Layer(int n_, int next_n_, matrix W_, matrix B_)
{
    n = n_;
    next_n = next_n_;
    W = W_;
    dW = matrix(n, next_n);
    B = B_;
    has_bias = true;
}

Layer::Layer(int n_, int next_n_, matrix W_)
{
    n = n_;
    next_n = next_n_;
    W = W_;
    dW = matrix(n, next_n);
    has_bias = false;
}


Layer::Layer(Layer const& obj)
{
    has_bias = obj.has_bias;
    n = obj.n;
    next_n = obj.next_n;
    W = obj.W;
    dW = matrix(n, next_n);
    if (has_bias)
        B = obj.B;
}


void Layer::make_rand_weight_layer(int n_, int next_n_, bool has_bias_)
{
    n = n_;
    next_n = next_n_;
    has_bias = has_bias_;
    srand_with_time();
    if (has_bias == HAS_BIAS){
        B = matrix(1, next_n);
        B = transfrm(B, random_norm);
    }
    W = matrix(n, next_n);
    dW = matrix(n, next_n);
    W = transfrm(W, random_norm);
}



matrix Layer::pass_layer(matrix in, decimal (*activ_func)(decimal))
{
    matrix out;
    X = transfrm(in, activ_func);
    out = X * W;
    if (has_bias) out = plus_str(out, B);
    return out;
}



matrix Layer::get_next_error_mat(matrix err_grad, decimal (*deriv_act_func)(decimal))
{
    matrix next_grad = (err_grad * (!W)) & transfrm(X, deriv_act_func);
    return next_grad;
}



void Layer::change_weight(matrix err_grad, decimal study_spd, decimal am)
{
    matrix weight_grad = (!X) * err_grad;
    W = W + (am * dW);
    dW = study_spd * weight_grad;
    W = W + study_spd * weight_grad;
    if (has_bias) B = B - study_spd * err_grad;
}












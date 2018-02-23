#include "neuralblocks.h"


NeuralBlock::NeuralBlock(){}

NeuralBlock::NeuralBlock(int max_layers_)
{
    max_layers = max_layers_;
    layers_num = 0;
    layers = new Layer [max_layers];
}

NeuralBlock::~NeuralBlock(){
    delete [] layers;
}

void NeuralBlock::InitBlock(int max_layers_)
{
    if (layers != nullptr) delete [] layers;
    max_layers = max_layers_;
    layers_num = 0;
    layers = new Layer [max_layers];
}


void NeuralBlock::AddLayers(int layers_add, int neurons_in_layer, bool has_bias_)
{
    if (layers_num > 0)
        layers[layers_num - 1].make_rand_weight_layer(layers[layers_num - 1].n, neurons_in_layer,
                                                      layers[layers_num - 1].has_bias);
    for (int i = layers_num; i < layers_num + layers_add - 1; i++)
        layers[i].make_rand_weight_layer(neurons_in_layer, neurons_in_layer, has_bias_);
    layers[layers_num + layers_add - 1].n = neurons_in_layer;
    layers[layers_num + layers_add - 1].has_bias = has_bias_;
    layers_num += layers_add;
}


matrix NeuralBlock::GetResult(matrix signal)
{
    for (int i = 0; i < layers_num - 1; i++)
        signal = layers[i].pass_layer(signal, sigmoid);
    return signal;
}



void NeuralBlock::BackProp(matrix result, matrix ideal_ans)
{
    matrix err = (ideal_ans - result) & transfrm(result, sigmoid_deriv);
    matrix err_buf;
    for (int i = layers_num - 2; i >= 0; i--){
        err_buf = layers[i].get_next_error_mat(err, sigmoid_deriv);
        layers[i].change_weight(err, study_speed, study_mtm);
        err = err_buf;
    }
}


void NeuralBlock::InitCommonParams(decimal init_study_spd, decimal study_mtm_){
    study_mtm = study_mtm_;
    study_speed = init_study_spd;
}


matrix NeuralBlock::MoveEpoch(matrix enter, matrix ideal_ans)
{
    matrix result = GetResult(enter);
    result = transfrm(result, sigmoid);
    BackProp(result, ideal_ans);
    return result;
}





#ifndef NEURALBLOCKS_H_INCLUDED
#define NEURALBLOCKS_H_INCLUDED

#include "layers.h"


class NeuralBlock{
    int max_layers;
    int layers_num;
public:
    Layer* layers;
    decimal study_speed;
    decimal study_mtm;

    NeuralBlock();
    NeuralBlock(int max_layers_);
    ~NeuralBlock();
    void InitBlock(int max_layers_);
    void AddLayers(int layers_num, int neurons_in_layer, bool has_bias_);
    void InitCommonParams(decimal init_study_spd, decimal study_mtm_);
    matrix GetResult(matrix signal);
    void BackProp(matrix result, matrix ideal_ans);
    matrix MoveEpoch(matrix enter, matrix ideal_ans);
};




#endif // NEURALBLOCKS_H_INCLUDED

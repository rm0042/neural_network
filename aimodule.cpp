#include "aimodule.h"

template class aimodule<def_data>;



template <class data>
aimodule<data>::aimodule(int maxneuralblocks){
    maxnetsnum = maxneuralblocks;
    networks = new NeuralBlock [maxnetsnum];
    number_of_networks = 0;
}

template <class data>
aimodule<data>::aimodule(int maxneuralblocks, tmemory<data>* _memory){
    maxnetsnum = maxneuralblocks;
    networks = new NeuralBlock [maxnetsnum];
    number_of_networks = 0;
    memory_ = _memory;
}


template <class data>
aimodule<data>::~aimodule(){
    delete [] networks;
    if (memory_ != nullptr) memory_->CleanMemory();
}


template <class data>
void aimodule<data>::AddNeuralBlock(int maxlayers){
    networks[number_of_networks++].InitBlock(maxlayers);
}


template <class data>
void aimodule<data>::AttachMemory(tmemory<data>* _memory, int cells_num){
    if (_memory == nullptr){
        memory_ = new tmemory<data>;
        memory_->AllocMemory(cells_num);
    } else memory_ = _memory;
}


template <class data>
matrix aimodule<data>::GetAction(int network_number, matrix stat){
    if (network_number > number_of_networks - 1) return null_mat;
    return networks[network_number].GetResult(stat);
}


template <class data>
void aimodule<data>::RewardStateAction(int network_number, matrix stat, decimal pleas, decimal eps, int maxDepth){
    data outstate = encodef_(stat, code_info);
    tmem<data>* chain;
    int i = 0, j;
    while ((i <= maxDepth) && ((chain = (*memory_).Findmem(outstate)) != nullptr)){
        networks[network_number].study_speed = pleas;
        for (j = 0; j < epoches_to_learn_; j++)
            networks[network_number].MoveEpoch(decodef_(chain->inst, code_info, stat.n),
                                                decodef_(chain->act, code_info, stat.n));
        pleas *= eps;
        outstate = chain->inst;
        i++;
    }
}


template <class data>
void aimodule<data>::SetLearnParams(int epoches_to_learn, decimal net_inertion)
{
    epoches_to_learn_ = epoches_to_learn;
    study_mtm = net_inertion;
}


template <class data>
void aimodule<data>::RemActResChain(matrix instat, matrix act, matrix outstat)
{
    memory_->Addmem(encodef_(instat, code_info), encodef_(act, code_info),
                    encodef_(outstat, code_info));
}

template <class data>
void aimodule<data>::RemActResChain(data instat, data act, data outstat)
{
    memory_->Addmem(instat, act, outstat);
}


template <class data>
void aimodule<data>::SetCodeParams(int codeinfo, int(*hashf)(data), data(*encodef)(matrix, int),
                                            matrix(*decodef)(data, int, int))
{
    code_info = codeinfo;
    memory_->hash_func = hashf_ = hashf;
    encodef_ = encodef;
    decodef_ = decodef;
}








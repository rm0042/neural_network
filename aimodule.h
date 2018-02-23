#ifndef IIMODULE_H_INCLUDED
#define IIMODULE_H_INCLUDED

#include "memory.h"
#include "neuralblocks.h"

template <class data = def_data> class aimodule{
private:
    int maxnetsnum;
    int number_of_networks;
public:
    tmemory<data>* memory_;
    NeuralBlock* networks;

    int(*hashf_)(data);
    data(*encodef_)(matrix, int);
    matrix(*decodef_)(data, int, int);
    int code_info;

    int epoches_to_learn_;
    decimal study_mtm;

    aimodule(int maxneuralblocks);
    aimodule(int maxneuralblocks, tmemory<data>* _memory);
    ~aimodule();

    void AddNeuralBlock(int maxlayers);
    void AttachMemory(tmemory<data>* _memory, int cells_num = MAXCELLS);
    void SetCodeParams(int codeinfo, int(*hashf)(data), data(*encodef)(matrix, int),
                                            matrix(*decodef)(data, int, int));
    void SetLearnParams(int epoches_to_learn, decimal net_inertion);

    void RewardStateAction(int network_number, matrix stat, decimal pleas,
                             decimal eps, int maxDepth);
    void RemActResChain(matrix instat, matrix act, matrix outstat);
    void RemActResChain(data instat, data act, data outstat);

    matrix GetAction(int network_number, matrix stat);
};

#endif // IIMODULE_H_INCLUDED

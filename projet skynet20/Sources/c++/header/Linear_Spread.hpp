#ifndef LINEAR_SPREAD_HPP_INCLUDED
#define LINEAR_SPREAD_HPP_INCLUDED

#include <vector>
#include <thread>
#include <cmath>
#include <chrono>

#include "RNL_Math.hpp"
#include "RNL_type.hpp"

class LSpread
{
    public:

        enum Spread_Type{CPU=0,MT_CPU,GPU,MT_GPU};
        enum Function{HEAVISIDE=0,IDENTITE,IDENTITE_COURBEE,SIGMOIDE_LOGISTIQUE,TANGENTE_HYPERBOLIQUE,EXPONENTIEL,SINUS,SOFT_PLUS,GAUSSIENNE,ReLU,PReLU,ELU,SOFT_EXP};

        LSpread(void);
        ~LSpread(void);

        void Spread(RNL & IA);

        void set_hidden_layer_func(Function);
        void set_spread_type(Spread_Type);
        void set_out_layer_func(Function);
        void set_alpha(float);

    private:
        float func_act(float ,Function ,float );

        void CPU_Spread(RNL & );
        void MT_CPU_Spread(RNL & );

        void Thread_CPU_Spread(RNL &,unsigned int ,unsigned int );

        Function Layer;
        Function Out;

        float alpha;

        Spread_Type S_t;

};

#endif // LINEAR_SPREAD_HPP_INCLUDED

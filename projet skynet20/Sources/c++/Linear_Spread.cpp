#include "header/Linear_Spread.hpp"

using std::vector;
using std::thread;


LSpread::LSpread(void):Layer(LSpread::SIGMOIDE_LOGISTIQUE),Out(LSpread::SIGMOIDE_LOGISTIQUE),S_t(Spread_Type::CPU),alpha(1)
{

}

LSpread::~LSpread(void)
{

}

void LSpread::set_hidden_layer_func(Function __hlf__)
{
    this->Layer=__hlf__;
}

void LSpread::set_out_layer_func(Function __olf__)
{
    this->Out=__olf__;
}

void LSpread::set_spread_type(Spread_Type __st__)
{
    this->S_t=__st__;
}

void LSpread::set_alpha(float __alpha__)
{
    this->alpha=__alpha__;
}

/////////////////////////////////////////////////
/// spread
/////////////////////////////////////////////////

void LSpread::Spread(RNL & IA)
{
    if(this->S_t==this->CPU)
        this->CPU_Spread(IA);

    else if(this->S_t==this->MT_CPU)
        this->MT_CPU_Spread(IA);
}

/////////////////////////////////////////////////
///private methode
/// spread
/////////////////////////////////////////////////
/////////////////////////////////////////////////
///simple cpu methode
/////////////////////////////////////////////////

void LSpread::CPU_Spread(RNL & IA)
{
    for(auto i=0u; i < IA.W_size();i++)
    {
        IA.get_O(i+1)=0;

        for(auto j=0u; j < IA.get_O(i+1).size() ;j++)
        {
            for(auto h=0u; h<IA.get_O(i).size() ;h++)
                IA.get_O(i+1)[j]+=IA.get_O(i)[h]*IA.get_W(i)[h][j];

            IA.get_O(i+1)[j]=func_act(IA.get_O(i+1)[j]+IA.get_B(i)[j],((i+1)!=IA.W_size())?this->Layer:this->Out,this->alpha);
        }
        //*IA.get_O(i+1)=func_act(*IA.get_O(i+1)+*IA.get_B(i),((i+1)!=IA.W_size())?this->Layer:this->Out,this->alpha);
    }
}
/////////////////////////////////////////////////
///cpu methode with multi threading
/////////////////////////////////////////////////
void LSpread::MT_CPU_Spread(RNL & IA)
{
    /*vector<thread> th_Spread;
    for(auto i=0u; i < IA.W_size();i++)
    {
        th_Spread.clear();

        for(auto j=0u; j<IA.O(i+1)->size() ;j++)
            th_Spread.push_back(thread(&LSpread::Thread_CPU_Spread,*this,std::ref(IA),i,j));

        for(auto v=0u;v<th_Spread.size();v++)
            th_Spread[v].join();
    }*/
}
void LSpread::Thread_CPU_Spread(RNL & IA,unsigned int i,unsigned int j)
{
    /*IA.O(i+1)->at(j)=0;

    for(auto h=0u; h<IA.O(i)->size() ;h++)
        IA.O(i+1)->at(j)+=IA.O(i)->at(h)*IA.W(i)->at(h*IA.O(i+1)->size()+j);

    IA.O(i+1)->at(j)=func_act(IA.O(i+1)->at(j)+IA.W(i)->at(IA.B_index(i)+j),((i+1)!=IA.W_size())?this->Layer:this->Out,this->alpha);*/
}

/////////////////////////////////////////////////
///defined function of activated
/////////////////////////////////////////////////
float LSpread::func_act(float x,Function f_a,float alpha)
{
    switch(f_a)
    {
        case Function::EXPONENTIEL:
            return Exponentielle<1>(-x);
            break;

        case Function::GAUSSIENNE:
            return Exponentielle<1>(Puissance<2>(-x));
            break;

        case Function::HEAVISIDE:
            return x>=0?1:0;
            break;

        case Function::IDENTITE:
            return x;
            break;

        case Function::SIGMOIDE_LOGISTIQUE:
            return 1/(1+Exponentielle<1>(-x));
            break;

        case Function::SINUS:
            return sin(x);
            break;

        case Function::SOFT_PLUS:
            return log(1+Exponentielle<1>(x));
            break;

        case Function::TANGENTE_HYPERBOLIQUE:
            return tanh(x);
            break;

        case Function::IDENTITE_COURBEE:
            return (sqrt(Puissance<2>(x)+1)-1)/2+x;
            break;

        case Function::ReLU:
            return x<0?0:x;
            break;

        case Function::PReLU:
            return x<0?(alpha*x):x;
            break;

        case Function::ELU:
            return x<0?(alpha*(Exponentielle<1>(x)-1)):x;
            break;

        case Function::SOFT_EXP:
            if(alpha<0)
                return -(log(1-alpha*(x+alpha)))/alpha;
            else if(alpha==0)
                return x;
            else if(alpha>0)
                return (Exponentielle<1>(alpha*x)-1)/alpha+alpha;
            break;

        default:
            return -INFINITY;
            break;
    }
    return -INFINITY;
}

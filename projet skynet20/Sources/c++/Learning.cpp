#include "header/Learning.hpp"

Learning::Learning(void):_auto_stop_(false),_epsilon_(1),_Eps_type_(Progress_type::CONST),
_Alpha_type_(Progress_type::CONST),_auto_build_(false),_inertie_(false),_save_learning_stats_(false),_path_file_("")
{

}
Learning::~Learning(void)
{

}


/////////////////////////////////////////////////
///Set the factor and methode of progression
/////////////////////////////////////////////////

void Learning::set_epsilon(Progress_type E_t,float epsilon)
{
    this->_epsilon_=epsilon;
    this->_Eps_type_=E_t;
}


/////////////////////////////////////////////////
///Set the factor, and enable methode of progression
/////////////////////////////////////////////////

void Learning::set_inertie(Progress_type alpha_t,bool inertie,float alpha)
{
    this->_Alpha_type_=alpha_t;
    this->_inertie_=inertie;
    this->_alpha_=alpha;
}


/////////////////////////////////////////////////
///Set number of iteration max for learning
/////////////////////////////////////////////////

void Learning::set_it(long int it)
{
    this->_It_=it;
}


/////////////////////////////////////////////////
///get the normalize percentage error
/////////////////////////////////////////////////

float Learning::get_error(void)
{
    return this->_Error_;
}


/////////////////////////////////////////////////
///select the calculating device
/////////////////////////////////////////////////

unsigned int Learning::Learn(RNL & IA,IO_rnl const & IO,LSpread & work)
{
    return this->CPU_learn(IA,IO,work);
}


/////////////////////////////////////////////////
///Enable and set auto stop
/////////////////////////////////////////////////

void Learning::set_auto_stop(bool __as__, float __tx__,unsigned int __prec__)
{
    this->_auto_stop_=__as__;
    this->_tx_error_=__tx__;
    this->_prec_=__prec__;
}


/////////////////////////////////////////////////
///Enable and set save of learning
/////////////////////////////////////////////////
void Learning::set_save_as(bool __sa__,std::string const & __path_file__)
{
    this->_save_learning_stats_=__sa__;
    this->_path_file_=__path_file__;
}

/////////////////////////////////////////////////
///Algo of simple CPU device
/////////////////////////////////////////////////
#include <fstream>
float Learning::CPU_learn(RNL & IA,IO_rnl const & IO,LSpread & work)
{
    if(IA.good())
    {
        /*RNL pop(IA);
        RNL::rnl_t pop_delta(this->delta);
        vector<Matrice<float>> pop_mat(this->delta2);*/

        //init delta
        delta.clear();
        for(auto i=IA.W_size();i>0;i--)
        {
            delta.push_back(std::vector<float>(IA.get_O(i).size(),0));
        }


        std::ofstream Of;

        if(this->_save_learning_stats_)
        {
            Of.open(this->_path_file_);
            Of << "Iteration" <<'\t'<<" Error " <<std::endl;
        }

        for(_I_=0;_I_<this->_It_;_I_++)
        {
            this->_Error_=0;

            for(auto exp=size_t(0);exp<IO.size();exp++)
            {
                IA.set_in(IO[exp].front());

                work.Spread(IA);

                Matrice<float> out(std::vector<float>(IO[exp].back())) ;

                if(this->_auto_stop_ && _I_%((this->_Eps_type_==LINEAR_ERROR || this->_Alpha_type_==LINEAR_ERROR)?1:this->_prec_)==0)
                {
                    for(auto out2=size_t(0);out2<IO[exp].back().size();out2++)
                        this->_Error_+=sqrt(Puissance<2>(IO[exp].back()[out2]-IA.get_out(out2)))/(IO.size()*IO[exp].back().size());
                }

                if(this->_inertie_)
                {
                   /* pop=IA;
                    pop_delta=this->delta;
                    pop_mat=this->delta2;*/
                }

                this->update_Delta(IA,out);
                this->update_W(IA);
                this->update_B(IA);

                if(this->_inertie_)
                {
                    /**this->_delta_last_=pop_delta;
                    *this->_RNL_last_=pop;
                    *this->_delta_last_2=pop_mat;*/
                }
            }
              /////////////////////////////////////////////////
            /// test the error to stop learning
            /////////////////////////////////////////////////

            if(this->_auto_stop_ && _I_%((this->_Eps_type_==LINEAR_ERROR || this->_Alpha_type_==LINEAR_ERROR)?1:this->_prec_)==0)
            {


                if(this->_Error_<=this->_tx_error_?true:false)//optimizable
                    break;

                if(this->_save_learning_stats_)
                    Of << this->_I_<<'\t'<<this->_Error_ <<std::endl;
            }
        }
    }
    return this->_Error_;
}


/////////////////////////////////////////////////
///Update weights (neuronal connections)
/////////////////////////////////////////////////

void Learning::update_W(RNL & IA)
{
    for(auto i=size_t(0);i<IA.W_size();i++)
    {
        Matrice<float> temp=IA.get_O(i)*this->Fact_Progress(this->_epsilon_);

        for(auto j=size_t(0);j<IA.get_O(i).size();j++)
            for(auto n=size_t(0);n<IA.get_O(i+1).size();n++)
            {
                if(!this->_inertie_ || this->_I_==0)
                    IA.get_W(i)[j][n]+=temp[j]*delta[delta.size()-1-i][n];
            }
    }
}


/////////////////////////////////////////////////
///Update biais
/////////////////////////////////////////////////

void Learning::update_B(RNL & IA)
{
    for(auto i=size_t(0);i<IA.W_size();i++)
        for(auto j=size_t(0);j<IA.get_O(i+1).size();j++)
            if(!this->_inertie_ || this->_I_==0)
                IA.get_B(i)[j]+=this->Fact_Progress(this->_epsilon_)*1*delta[delta.size()-i-1][j];

}


/////////////////////////////////////////////////
///Update delta of error
/////////////////////////////////////////////////

void Learning::update_Delta(RNL & IA,Matrice<float> & Win_out)
{
    for(auto i=IA.W_size();i>0;i--)
    {
        if(i!=IA.O_size()-1)
        {
            for(auto j=0u;j<IA.get_O(i).size();j++)
            {
                /// calculate the error of deep-layer

                Matrice<float> sr=IA.get_W(i)[j]*delta[IA.W_size()-i-1];

                delta[IA.W_size()-i][j]=IA.get_O(i)[j]*(1-IA.get_O(i)[j])*Matrice<float>::sum(sr);
            }
        }
        else
        {
            /// calculate the error of out layer

            delta[IA.W_size()-i]=Win_out-IA.get_O(i);
        }
    }
}


/////////////////////////////////////////////////
///Function of factor of progression
/////////////////////////////////////////////////

float Learning::Fact_Progress(float y)
{
    switch(this->_Eps_type_)
    {
    case Progress_type::CONST :
        return y;
        break;

    case Progress_type::LINEAR_IT :
        return 1/static_cast<double>(this->_It_)*this->_I_+1+1/static_cast<double>(this->_It_);
        break;

    case Progress_type::LINEAR_ERROR :
        return this->_Error_;
        break;

    case Progress_type::LOG :
        return 1/(100*(this->_I_/this->_It_)+1);
        break;

    default :
        return y;
        break;
    }

    return y;
}

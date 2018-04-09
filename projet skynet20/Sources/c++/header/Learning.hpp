#ifndef LEARNING_HPP_INCLUDED
#define LEARNING_HPP_INCLUDED

#include "IORNL.hpp"
#include "Linear_Spread.hpp"

class Learning
{
public:
    enum Progress_type{CONST=0,LINEAR_IT,LINEAR_ERROR,LOG};

    Learning(void);
    ~Learning(void);

    /////////////////////////////////////////////////
    /// Don't copy
    /////////////////////////////////////////////////

    Learning(Learning&)=delete;
    Learning operator=(Learning&)=delete;

    /////////////////////////////////////////////////
    ///Set the factor and methode of progression
    /////////////////////////////////////////////////
    void set_epsilon(Progress_type =LINEAR_IT,float =1.0 );

    /////////////////////////////////////////////////
    ///Set the factor, and enable methode of progression
    /////////////////////////////////////////////////
    void set_inertie(Progress_type,bool,float =1.0);

    /////////////////////////////////////////////////
    ///Set number of iteration max for learning
    /////////////////////////////////////////////////
    void set_it(long int =100u);

    /////////////////////////////////////////////////
    ///Enable and set auto stop
    /////////////////////////////////////////////////
    void set_auto_stop(bool= true,float= 0.05,unsigned int =10u);

    /////////////////////////////////////////////////
    ///Enable and set save of learning
    /////////////////////////////////////////////////
    void set_save_as(bool= false,std::string const & ="");

    /////////////////////////////////////////////////
    ///get the normalize percentage error
    /////////////////////////////////////////////////
    float get_error(void);

    /////////////////////////////////////////////////
    ///select the calculating device
    /////////////////////////////////////////////////
    unsigned int Learn(RNL &,IO_rnl const &,LSpread &);

private:


    /////////////////////////////////////////////////
    ///Algo of simple CPU device
    /////////////////////////////////////////////////
    float CPU_learn(RNL &,IO_rnl const & IO,LSpread &);

    /////////////////////////////////////////////////
    ///Update the weights (neuronal connections)
    /////////////////////////////////////////////////
    void update_W(RNL & IA);

    /////////////////////////////////////////////////
    ///Update the biais
    /////////////////////////////////////////////////
    void update_B(RNL & IA);

    /////////////////////////////////////////////////
    ///Update the delta of error
    /////////////////////////////////////////////////
    void update_Delta(RNL & ,Matrice<float>  &);

    /////////////////////////////////////////////////
    /// test the error to stop learning
    /////////////////////////////////////////////////
    bool premature_stop(RNL &,IO_rnl const &,LSpread &);

    /////////////////////////////////////////////////
    ///Function of factor of progression
    /////////////////////////////////////////////////
    float Fact_Progress(float);


    //!< attribut

    float _Error_;
    float _epsilon_;
    float _alpha_;
    float _tx_error_;

    long int _It_;
    long int _I_;

    unsigned int _prec_;

    bool _auto_build_;
    bool _inertie_;
    bool _auto_stop_;
    bool _save_learning_stats_;

    std::string _path_file_;

    /*std::unique_ptr<RNL> _RNL_last_;
    std::unique_ptr<std::vector<Matrice<float>>> _delta_last_2;*/

    std::vector<Matrice<float>> delta;

    Progress_type _Eps_type_;
    Progress_type _Alpha_type_;
};


#endif // LEARNING_HPP_INCLUDED

#include "header/auto_building.hpp"

Auto_Building::Auto_Building(void)
{

}
Auto_Building::~Auto_Building(void)
{

}


/////////////////////////////////////////////////
/// automatique building network
/////////////////////////////////////////////////
void Auto_Building::building(RNL & __rnl__,IO_rnl &__io__, LSpread &__ls__,Learning &__learn__)
{
    switch(this->_St_)
    {
        case LSpread::CPU:
            this->building_cpu(__io__,__ls__,__learn__);
            break;

        default:
            break;
    }

    __rnl__=this->_temp_RNL_;

    this->clear();
}

/////////////////////////////////////////////////
/// set device for calculate
/////////////////////////////////////////////////
void Auto_Building::set_spreed_device(LSpread::Spread_Type __St__)
{
    this->_St_=__St__;
}


/////////////////////////////////////////////////
/// clear the memory
/////////////////////////////////////////////////
void Auto_Building::clear()
{
    this->_temp_RNL_.clear();
}

/////////////////////////////////////////////////
/// calculate with cpu device
/////////////////////////////////////////////////
void Auto_Building::building_cpu(IO_rnl &__io__, LSpread &__ls__,Learning &__learn__)
{
    this->init_temp(__io__);

    bool erreur(true);

    while(erreur)
    {

        __learn__.Learn(this->_temp_RNL_,__io__,__ls__);

        if(__learn__.get_error()!=0.0)
        {
            this->add_hidden_layer();
        }
        else
            break;

    }
}

/////////////////////////////////////////////////
/// initialize tempory memory
/////////////////////////////////////////////////
void Auto_Building::init_temp(IO_rnl &__io__)
{
    this->clear();

    this->_temp_RNL_.Add_O(RNL::Init_O<float>(__io__.at(0).front().size()));
    this->_temp_RNL_.Add_O(RNL::Init_O<float>(__io__.at(0).back().size()));

    this->_temp_RNL_.Add_B(RNL::Init_B<float>(__io__.at(0).back().size(),RNL::NORMAL));

    this->_temp_RNL_.Add_W(RNL::Init_W<float>(__io__.at(0).front().size(),__io__.at(0).back().size(),RNL::NORMAL));
}

/////////////////////////////////////////////////
/// add layer for auto building
/////////////////////////////////////////////////
void Auto_Building::add_hidden_layer(void)
{
    this->_temp_RNL_.get_O(1)=RNL::Init_O<float>(2);
    this->_temp_RNL_.Add_O(RNL::Init_O<float>(4));

    this->_temp_RNL_.get_W(0)=RNL::Init_W<float>(2,2,RNL::NORMAL);
    this->_temp_RNL_.Add_W(RNL::Init_W<float>(2,4,RNL::NORMAL));

    this->_temp_RNL_.get_B(0)=RNL::Init_B<float>(2,RNL::NORMAL);
    this->_temp_RNL_.Add_B(RNL::Init_B<float>(4,RNL::NORMAL));

}


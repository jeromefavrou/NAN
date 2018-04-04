#include "header/RNL_type.hpp"
using namespace std;

/**--Constructor--**/
RNL::RNL(void)
{
    this->clear_error();
}

RNL RNL::operator=(RNL const & __rnl__)
{
    this->clear();

    this->_W_=__rnl__.Cget_W();
    this->_B_=__rnl__.Cget_B();
    this->_O_=__rnl__.Cget_O();

    return *this;
}

/**--Destructor--**/
RNL::~RNL(void)
{
}

void RNL::clear_error(void)
{
    this->rnl_e[0].stat=0;
    this->rnl_e[1].stat=0;
    this->rnl_e[2].stat=0;

    this->rnl_e[0].warn.clear();
    this->rnl_e[1].warn.clear();
    this->rnl_e[2].warn.clear();
}

void RNL::clear(void)
{
    this->_B_.clear();
    this->_O_.clear();
    this->_W_.clear();
}

bool RNL::save_as(string const & file)//export
{
    ofstream Of;

    Of.exceptions(ofstream::failbit | ofstream::badbit);

    try
    {
        /*unsigned int __size__=this->size();

        if(__size__==0)
            throw logic_error("rnl.data size = 0");

        Of.open(file,ios::out | ios::binary);

        float header(RNL_HEAD);
        Of.write(reinterpret_cast<char *>(&header),sizeof(float));

        Of.write(reinterpret_cast<char *>(&__size__),sizeof(unsigned int));

        for(auto i=0u;i<this->size();i++)
        {
             __size__=rnl_data[i].size();
             Of.write(reinterpret_cast<char *>(&__size__),sizeof(unsigned int));
             Of.write(reinterpret_cast<char *>(rnl_data[i].data()),sizeof(*rnl_data[i].data())*__size__);
        }
        this->rnl_e[2].stat=0;*/

        return true;
    }
    catch(system_error& e)
    {
        this->rnl_e[2].stat=1;
        this->rnl_e[2].warn=file+" cannot be open -> "+string(e.what());

        return false;
    }
    catch(exception const & e)
    {
        this->rnl_e[0].stat=1;
        this->rnl_e[0].warn=string(e.what());

        return false;
    }

    this->rnl_e[0].stat=1;

    return false;
}

bool RNL::import(string const & file)
{

    ifstream If;

    If.exceptions(ifstream::failbit | ifstream::badbit);

    try
    {
       /* If.open(file);

        unsigned int __size_array__(0);

        this->clear();

        float header(0);

        If.read(reinterpret_cast<char *>(&header),sizeof(float));

        if(header!=RNL_HEAD)
            throw std::system_error(ENOTSUP, std::generic_category(),file+" don't RNL file");

        If.read(reinterpret_cast<char *>(&__size_array__),sizeof(unsigned int));

        for(auto i=0u;i<__size_array__&&If;i++)
        {
            unsigned int __size__(0);

            If.read(reinterpret_cast<char *>(&__size__),sizeof(unsigned int));
            vector<float> __data__(__size__,0);

            If.read(reinterpret_cast<char *>(__data__.data()),sizeof(*__data__.data())*__size__);

            *this+=__data__;
        }
        this->rnl_e[1].stat=0;*/

        return true;
    }
    catch(system_error& e)
    {
        this->rnl_e[1].stat=1;
        this->rnl_e[1].warn=file+" cannot be open -> "+string(e.what());

        return false;
    }
    catch(exception const & e)
    {
        this->rnl_e[0].stat=1;
        this->rnl_e[0].warn=string(e.what());

        return false;
    }

    this->rnl_e[0].stat=1;

    return false;
}

/**--Getteur--**/

rnl_error RNL::get_error()const noexcept
{
    return this->rnl_e;
}

void RNL::Add_O(Matrice<float> const & O)
{
    this->_O_.push_back(O);
}
void RNL::Add_B(Matrice<float> const & B)
{
    this->_B_.push_back(B);
}
void RNL::Add_W(Matrice<Matrice<float>> const & W)
{
    this->_W_.push_back(W);
}

Matrice<Matrice<float>>& RNL::get_W(size_t __i__)
{
    return this->_W_[__i__];
}
Matrice<float>& RNL::get_O(size_t __i__)
{
    return this->_O_[__i__];
}
Matrice<float>& RNL::get_B(size_t __i__)
{
    return this->_B_[__i__];
}

vector<Matrice<Matrice<float>>> RNL::Cget_W(void) const noexcept
{
    return this->_W_;
}
vector<Matrice<float>> RNL::Cget_O(void) const noexcept
{
    return this->_O_;
}
vector<Matrice<float>> RNL::Cget_B(void) const noexcept
{
    return this->_B_;
}

std::vector<Matrice<Matrice<float>>>::size_type RNL::W_size(void) const noexcept
{
    return this->_W_.size();
}
std::vector<Matrice<float>>::size_type RNL::O_size(void) const noexcept
{
    return this->_O_.size();
}
std::vector<Matrice<float>>::size_type RNL::B_size(void) const noexcept
{
    return this->_B_.size();
}

bool RNL::set_in(vector<float> const & in)
{
    if(in.size()==this->_O_.front().size() && this->_O_.size()!=0)
    {
        this->_O_.front()=in;

        this->rnl_e[0].stat=0;

        return true;
    }
    else
    {
        this->rnl_e[0].stat=1;
        this->rnl_e[0].warn=" incompatible size of RNL::set_in";
        return false;
    }
}
float RNL::get_out(size_t __i__)
{
    return this->_O_.back()[__i__];
}

bool RNL::good(void)
{
    return !this->rnl_e[0].stat&&!this->rnl_e[1].stat&&!this->rnl_e[2].stat?true:false;
}

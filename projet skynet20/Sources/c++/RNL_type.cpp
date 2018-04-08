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


/////////////////////////////////////////////////
///clear error stat
/////////////////////////////////////////////////
void RNL::clear_error(void)
{
    this->rnl_e[0].stat=0;
    this->rnl_e[1].stat=0;
    this->rnl_e[2].stat=0;

    this->rnl_e[0].warn.clear();
    this->rnl_e[1].warn.clear();
    this->rnl_e[2].warn.clear();
}


/////////////////////////////////////////////////
///clear data equi reset
/////////////////////////////////////////////////
void RNL::clear(void)
{
    this->_B_.clear();
    this->_O_.clear();
    this->_W_.clear();
}


/////////////////////////////////////////////////
///export data
/////////////////////////////////////////////////
bool RNL::save_as(string const & file)//export
{
    ofstream Of;

    Of.exceptions(ofstream::failbit | ofstream::badbit);

    try
    {
        unsigned int __size__=0;

        if(this->_O_.size()==0)
            throw logic_error("rnl.data size = 0");

        Of.open(file,ios::out | ios::binary);

        /**write header*/
        float header(RNL_HEAD);

        Of.write(reinterpret_cast<char *>(&header),sizeof(float));

        /**write _O_.size()*/
        __size__=this->_O_.size();

        Of.write(reinterpret_cast<char *>(&__size__),sizeof(unsigned int));

        for(auto i=size_t(0);i<this->_O_.size();i++)
        {
            __size__=this->get_O(i).size();

            Of.write(reinterpret_cast<char *>(&__size__),sizeof(unsigned int));
        }

        /**write _B_*/
        __size__=this->_B_.size();

        Of.write(reinterpret_cast<char *>(&__size__),sizeof(unsigned int));

        for(auto i=size_t(0);i<this->_B_.size();i++)
        {
            __size__=this->get_B(i).size();

            Of.write(reinterpret_cast<char *>(&__size__),sizeof(unsigned int));

            Of.write(reinterpret_cast<char *>(this->get_B(i).get_data().data()),sizeof(float)*__size__);
        }

        /**write _W_*/
        __size__=this->_W_.size();

        Of.write(reinterpret_cast<char *>(&__size__),sizeof(unsigned int));

        for(auto i=size_t(0);i<this->_W_.size();i++)
        {
            __size__=this->get_W(i).size();

            Of.write(reinterpret_cast<char *>(&__size__),sizeof(unsigned int));

            for(auto j=size_t(0);j<this->get_W(i).size();j++)
            {
                __size__=this->get_W(i).at(j).size();

                Of.write(reinterpret_cast<char *>(&__size__),sizeof(unsigned int));

                Of.write(reinterpret_cast<char *>(this->get_W(i).at(j).get_data().data()),sizeof(float)*__size__);
            }
        }

        this->rnl_e[2].stat=0;

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


/////////////////////////////////////////////////
///import data
/////////////////////////////////////////////////
bool RNL::import(string const & file)
{

    ifstream If;

    If.exceptions(ifstream::failbit | ifstream::badbit);

    try
    {
        If.open(file);

        unsigned int __size_array__(0);

        this->clear();

        /**read header*/
        float header(0);

        If.read(reinterpret_cast<char *>(&header),sizeof(float));

        if(header!=RNL_HEAD)
            throw std::system_error(ENOTSUP, std::generic_category(),file+" don't RNL file");

        /**read _O_.size()*/
        If.read(reinterpret_cast<char *>(&__size_array__),sizeof(unsigned int));

        unsigned int tmp_size=__size_array__;

        for(auto i=0u;i<tmp_size;i++)
        {
            If.read(reinterpret_cast<char *>(&__size_array__),sizeof(unsigned int));

            this->Add_O(Init_O<float>(__size_array__));
        }

        /**read _B_*/
        If.read(reinterpret_cast<char *>(&__size_array__),sizeof(unsigned int));

        tmp_size=__size_array__;

        for(auto i=0u;i<tmp_size;i++)
        {
            If.read(reinterpret_cast<char *>(&__size_array__),sizeof(unsigned int));

            this->Add_B(Init_B<float>(__size_array__,NORMAL));

            vector<float> __data__(__size_array__,0);

            If.read(reinterpret_cast<char *>(__data__.data()),sizeof(*__data__.data())*__size_array__);

            Matrice<float> __mat_data__(__data__);

            this->get_B(i)=__mat_data__;
        }

        /**read _W_*/
        If.read(reinterpret_cast<char *>(&__size_array__),sizeof(unsigned int));

        tmp_size=__size_array__;

        this->_W_=vector<Matrice<Matrice<float>>>(__size_array__);

        for(auto i=0u;i<tmp_size;i++)
        {
            If.read(reinterpret_cast<char *>(&__size_array__),sizeof(unsigned int));

            unsigned temp_size2=__size_array__;

            vector<Matrice<float>> _mat_data_;

            for(auto j=0u;j<temp_size2;j++)
            {
                If.read(reinterpret_cast<char *>(&__size_array__),sizeof(unsigned int));

                vector<float> __data__(__size_array__,0);

                If.read(reinterpret_cast<char *>(__data__.data()),sizeof(*__data__.data())*__size_array__);

                Matrice<float> matr_temp(__data__);

                _mat_data_.push_back(matr_temp);
            }

            this->get_W(i)=_mat_data_;
        }

        this->rnl_e[1].stat=0;

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


/////////////////////////////////////////////////
///getter of error
/////////////////////////////////////////////////
rnl_error RNL::get_error()const noexcept
{
    return this->rnl_e;
}


/////////////////////////////////////////////////
///check free memory
/////////////////////////////////////////////////
void RNL::memory_check(size_t __aloc__) throw(string)
{
    Memory_stat mem_s;
    mem_s.update_info();

    if(__aloc__>mem_s.MemFree)
        throw string("Insufficient memory");
}


/////////////////////////////////////////////////
///additive neuronal layer
/////////////////////////////////////////////////
void RNL::Add_O(Matrice<float> const & O) throw(string)
{
    this->memory_check(O.size()*sizeof(float));

    this->_O_.push_back(O);
}


/////////////////////////////////////////////////
///additive biais layer
/////////////////////////////////////////////////
void RNL::Add_B(Matrice<float> const & B) throw(string)
{
    this->memory_check(B.size()*sizeof(float));

    this->_B_.push_back(B);
}


/////////////////////////////////////////////////
///additive weight layer
/////////////////////////////////////////////////
void RNL::Add_W(Matrice<Matrice<float>> const & W) throw(string)
{
    this->memory_check(W.size()*W.get_data()[0].size()*sizeof(float));

    this->_W_.push_back(W);
}


/////////////////////////////////////////////////
///reference getter of weight layer
/////////////////////////////////////////////////
Matrice<Matrice<float>>& RNL::get_W(size_t __i__)
{
    return this->_W_[__i__];
}


/////////////////////////////////////////////////
///reference getter of neuronal layer
/////////////////////////////////////////////////
Matrice<float>& RNL::get_O(size_t __i__)
{
    return this->_O_[__i__];
}


/////////////////////////////////////////////////
///reference getter of biais layer
/////////////////////////////////////////////////
Matrice<float>& RNL::get_B(size_t __i__)
{
    return this->_B_[__i__];
}


/////////////////////////////////////////////////
///fix data getter of weight layer
/////////////////////////////////////////////////
vector<Matrice<Matrice<float>>> RNL::Cget_W(void) const noexcept
{
    return this->_W_;
}


/////////////////////////////////////////////////
///fix data getter of neuronal layer
/////////////////////////////////////////////////
vector<Matrice<float>> RNL::Cget_O(void) const noexcept
{
    return this->_O_;
}


/////////////////////////////////////////////////
///fix data getter of biais layer
/////////////////////////////////////////////////
vector<Matrice<float>> RNL::Cget_B(void) const noexcept
{
    return this->_B_;
}


/////////////////////////////////////////////////
///get size of neuronal layer
/////////////////////////////////////////////////
std::vector<Matrice<Matrice<float>>>::size_type RNL::W_size(void) const noexcept
{
    return this->_W_.size();
}


/////////////////////////////////////////////////
///get size of weight layer
/////////////////////////////////////////////////
std::vector<Matrice<float>>::size_type RNL::O_size(void) const noexcept
{
    return this->_O_.size();
}


/////////////////////////////////////////////////
///get size of biais layer
/////////////////////////////////////////////////
std::vector<Matrice<float>>::size_type RNL::B_size(void) const noexcept
{
    return this->_B_.size();
}


/////////////////////////////////////////////////
///set input values
/////////////////////////////////////////////////
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


/////////////////////////////////////////////////
///get output value
/////////////////////////////////////////////////
float RNL::get_out(size_t __i__)
{
    return this->_O_.back()[__i__];
}


/////////////////////////////////////////////////
///check if there is not error
/////////////////////////////////////////////////
bool RNL::good(void)
{
    return !this->rnl_e[0].stat&&!this->rnl_e[1].stat&&!this->rnl_e[2].stat?true:false;
}

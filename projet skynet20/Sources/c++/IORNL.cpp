#include "header/IORNL.hpp"

/////////////////////////////////////////////////
///constructor and operator up
/////////////////////////////////////////////////

using std::vector;
using std::string;
using std::ifstream;
using std::ofstream;
using std::system_error;
using std::logic_error;
using std::exception;
using std::ios;
using std::generic_category;

IO_rnl::IO_rnl()
{
    this->clear_error();
    this->io_indexe=0;
}
IO_rnl::~IO_rnl()
{
}

IO_rnl IO_rnl::operator+=(IO_type const &io_t)
{
    this->io_data.push_back(io_t);

    return *this;
}

IO_rnl::IO_type IO_rnl::operator[](unsigned int const indexe) const
{
    return this->io_data[indexe];
}

/////////////////////////////////////////////////
///function asc
/////////////////////////////////////////////////
IO_rnl::IO_type IO_rnl::at(unsigned int const indexe) const
{
    return this->io_data[indexe];
}
void IO_rnl::clear(void)
{
    this->reset();
    this->io_data.clear();
}
size_t IO_rnl::size(void) const
{
    this->io_data.size();
}
IO_rnl IO_rnl::add_IO(IO_type const & io_t)
{
    this->io_data.push_back(io_t);

    return *this;
}
void IO_rnl::reset(void)
{
    this->io_indexe=0;
}

/////////////////////////////////////////////////
///data io standard binairy file
/////////////////////////////////////////////////

bool IO_rnl::import(string const & file)
{
    ifstream If;

    If.exceptions(ifstream::failbit | ifstream::badbit);

    try
    {
        If.open(file);

        float header(0);
        If.read(reinterpret_cast<char *>(&header),sizeof(float));

        if(header!=IO_HEAD)
            throw system_error(ENOTSUP, generic_category(),file+" don't IO_RNL file");

        this->clear();

        unsigned int __size_array__(0);
        If.read(reinterpret_cast<char *>(&__size_array__),sizeof(unsigned int));

        for(auto i=0u;i<__size_array__&&If;i++)
        {
            unsigned int __sizeI__(0);
            unsigned int __sizeO__(0);

            If.read(reinterpret_cast<char *>(&__sizeI__),sizeof(unsigned int));
            vector<float> __dataI__(__sizeI__,0);
            If.read(reinterpret_cast<char *>(__dataI__.data()),sizeof(*__dataI__.data())*__sizeI__);

            If.read(reinterpret_cast<char *>(&__sizeO__),sizeof(unsigned int));
            vector<float> __dataO__(__sizeO__,0);
            If.read(reinterpret_cast<char *>(__dataO__.data()),sizeof(*__dataO__.data())*__sizeO__);

            IO_type I_t;
            I_t[Iin]=__dataI__;
            I_t[Iout]=__dataO__;

            *this+=I_t;
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

bool IO_rnl::save_as(string const & file)
{
    ofstream Of;

    Of.exceptions(ofstream::failbit | ofstream::badbit);

    try
    {
        unsigned int __size__=this->size();

        if(__size__==0)
            throw logic_error("io_rnl.data size = 0");

        Of.open(file,ios::out | ios::binary);

        float header(IO_HEAD);
        Of.write(reinterpret_cast<char *>(&header),sizeof(float));

        Of.write(reinterpret_cast<char *>(&__size__),sizeof(unsigned int));

        for(auto i=0u;i<this->size();i++)
        {
             unsigned int __sizeI__=io_data[i][Iin].size();
             unsigned int __sizeO__=io_data[i][Iout].size();

             Of.write(reinterpret_cast<char *>(&__sizeI__),sizeof(unsigned int));
             Of.write(reinterpret_cast<char *>(io_data[i][Iin].data()),sizeof(*io_data[i][Iin].data())*__sizeI__);

             Of.write(reinterpret_cast<char *>(&__sizeO__),sizeof(unsigned int));
             Of.write(reinterpret_cast<char *>(io_data[i][Iout].data()),sizeof(*io_data[i][Iout].data())*__sizeO__);
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


void IO_rnl::clear_error(void)
{
    this->rnl_e[0].stat=0;
    this->rnl_e[1].stat=0;
    this->rnl_e[2].stat=0;

    this->rnl_e[0].warn.clear();
    this->rnl_e[1].warn.clear();
    this->rnl_e[2].warn.clear();
}
rnl_error IO_rnl::get_error()const
{
    return this->rnl_e;
}

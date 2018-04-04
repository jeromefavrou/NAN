#ifndef IORNL_HPP_INCLUDED
#define IORNL_HPP_INCLUDED

#include <array>
#include <vector>
#include <fstream>

#include "RNL_error.hpp"

class IO_rnl
{
public:

    #define IO_HEAD float(82918681)
    #define Iin int(0)
    #define Iout int(1)

    typedef std::array<std::vector<float>,2>IO_type;

    IO_rnl();
    ~IO_rnl();

    IO_rnl operator+=(IO_type const &);

    IO_type operator[](unsigned int const) const;

    void clear(void);
    size_t size(void) const;
    IO_type at(unsigned int const) const;


    IO_rnl add_IO(IO_type const &);
    bool import(std::string const &);
    bool save_as(std::string const &);
    void reset(void);

    void clear_error(void);
    rnl_error get_error()const;

private:
    unsigned int io_indexe;

    std::vector<IO_type> io_data;

    rnl_error rnl_e;
};

#endif // IORNL_HPP_INCLUDED

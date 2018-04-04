#ifndef RNL_ERROR_HPP_INCLUDED
#define RNL_ERROR_HPP_INCLUDED

#include <array>
#include <string>

typedef struct
{
    bool stat:1;
    std::string warn;
}ebool;

typedef std::array<ebool,3> rnl_error;

std::string rnl_error_to_str(rnl_error const & e);


#endif // RNL_ERROR_HPP_INCLUDED

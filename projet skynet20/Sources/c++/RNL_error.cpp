#include "header/RNL_error.hpp"

using std::string;

string rnl_error_to_str(rnl_error const & e)
{
    string str("");
    if(e[0].stat==1)
        str+=string("\n--error--\n")+string("other error: ")+e[0].warn+string("\n");
    if(e[1].stat==1)
        str+=string("\n--error--\n")+string("import echec: ")+e[1].warn+string("\n");
    if(e[2].stat==1)
        str+=string("\n--error--\n")+string("export echec: ")+e[2].warn+string("\n");

    return str;
}

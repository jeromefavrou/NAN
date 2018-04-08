#ifndef I_E_HPP_INCLUDED
#define I_E_HPP_INCLUDED
#include <iostream>
#include <array>

void import(RNL &skynet,IO_rnl &Win_out, std::string const & path)
{
    if(Win_out.import(path+"4_logic_funct.io_pt.bin"))
        std::cout <<"import IO with succes\n" <<std::endl;
    else
        std::cout <<"import IO without succes\n" <<std::endl;

    if(skynet.import(path+"4_logic_funct.data_pt.bin"))
        std::cout <<"import RNL with succes\n" <<std::endl;
    else
        std::cout <<"import RNL without succes\n" <<std::endl;
}
void save_as(RNL &skynet,IO_rnl &Win_out, std::string const & path)
{
    if(skynet.save_as(path+"4_logic_funct.data_pt.bin"))
        std::cout <<"export RNL with succes" <<std::endl;
    else
        std::cout <<"export RNL without succes" <<std::endl;

    if(Win_out.save_as(path+"4_logic_funct.io_pt.bin"))
        std::cout <<"export IO with succes" <<std::endl;
    else
        std::cout <<"export IO without succes" <<std::endl;
}

void display(RNL &IA,IO_rnl &Win_out,LSpread &propag)
{
    std::array<std::string,4> name{"XOR","OR","AND","NAND"};

    if(IA.good())
    {
        for(auto i=size_t(0);i<IA.get_O(IA.O_size()-1).size();i++)
        {
            std::cout<<name[i]<<std::endl;
            for(auto exp=size_t(0);exp<Win_out.size();exp++)
            {
                IA.set_in(Win_out[exp].front());

                propag.Spread(IA);

                std::cout << Win_out[exp].front()[0] <<Win_out[exp].front()[1] <<" : "<< IA.get_out(i) <<std::endl;
            }
            std::cout<<std::endl;
        }
    }
}

#endif // I_E_HPP_INCLUDED

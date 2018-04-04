#ifndef RNL_TYPE_HPP_INCLUDED
#define RNL_TYPE_HPP_INCLUDED

#include <string>
#include <vector>
#include <random>
#include <iostream>
#include <fstream>

#include "RNL_error.hpp"
#include "matrice.hpp"
/**class d'erreur pour save_ import**/

class RNL
{
public:

    #define RNL_HEAD float(36236280)

    enum poid_distribution{NORMAL,UNIFORM};

    /**--Constructor--**/

    RNL(void);

    RNL operator=(RNL const &);
    /**--Destructor--**/
    ~RNL(void);

    /**--Function--**/
    void Add_O(Matrice<float> const & O);
    void Add_B(Matrice<float> const & B);
    void Add_W(Matrice<Matrice<float>> const & W);

    Matrice<Matrice<float>>& get_W(size_t);
    Matrice<float>& get_O(size_t);
    Matrice<float>& get_B(size_t);

    std::vector<Matrice<Matrice<float>>> Cget_W(void) const noexcept;
    std::vector<Matrice<float>> Cget_O(void) const noexcept;
    std::vector<Matrice<float>> Cget_B(void) const noexcept;

    void clear(void);
    void clear_error(void);

    /// depreciete
    bool save_as(std::string const &); //export
    /// depreciete
    bool import(std::string const &); //import
    bool good(void);

    /**--Getter--**/
    rnl_error get_error()const noexcept;

    bool set_in(std::vector<float> const &);
    float get_out(size_t __i__);

    std::vector<Matrice<float>>::size_type O_size(void) const noexcept;
    std::vector<Matrice<Matrice<float>>>::size_type W_size(void) const noexcept;
    std::vector<Matrice<float>>::size_type B_size(void) const noexcept;



    /**--static--**/

    template<typename __T__> static Matrice<__T__> Init_O(size_t __n__)
    {
        return Matrice<__T__>(std::vector<__T__>(__n__,0));
    }
    template<typename __T__> static Matrice<__T__> Init_B(size_t __n__,poid_distribution __pd__)
    {
        std::vector<__T__> tmp(__n__);
        std::random_device rd;

        float centre(0);

        if(__pd__==NORMAL)
            centre=0;
        else if(__pd__==UNIFORM)
            centre=0.5;

        for(auto It=tmp.begin();It!=tmp.end();It++)
        {
            std::mt19937 gen(rd());
            std::uniform_real_distribution<> dis(centre-0.5, centre+0.5);

            *It=dis(gen);
        }

        return Matrice<__T__>(tmp);
    }
    template<typename __T__> static Matrice<Matrice<__T__>> Init_W(size_t __i__,size_t __o__,poid_distribution __pd__)
    {
        std::vector<Matrice<__T__>> tmp(__i__);

        for(auto It=tmp.begin();It!=tmp.end();It++)
        {
            std::vector<__T__> tmp2(__o__);

            std::random_device rd;

            float centre(0);

            if(__pd__==NORMAL)
                centre=0;
            else if(__pd__==UNIFORM)
                centre=0.5;

            for(auto It2=tmp2.begin();It2!=tmp2.end();It2++)
            {
                std::mt19937 gen(rd());
                std::uniform_real_distribution<> dis(centre-0.5, centre+0.5);

                *It2=dis(gen);
            }

            *It=Matrice<__T__>(tmp2);
        }

        return Matrice<Matrice<__T__>>(tmp);
    }


private:
    std::vector<Matrice<float>> _O_,_B_;
    std::vector<Matrice<Matrice<float>>> _W_;

    rnl_error rnl_e;

};

#endif // RNL_TYPE_HPP_INCLUDED

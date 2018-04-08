#ifndef RNL_TYPE_HPP_INCLUDED
#define RNL_TYPE_HPP_INCLUDED


#include <vector>
#include <random>
#include <iostream>

#include "Memory_stats.hpp"
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

    /////////////////////////////////////////////////
    ///additive neuronal layer
    /////////////////////////////////////////////////
    void Add_O(Matrice<float> const & O) throw(std::string);

    /////////////////////////////////////////////////
    ///additive biais layer
    /////////////////////////////////////////////////
    void Add_B(Matrice<float> const & B) throw(std::string);

    /////////////////////////////////////////////////
    ///additive weight layer
    /////////////////////////////////////////////////
    void Add_W(Matrice<Matrice<float>> const & W) throw(std::string);

    /////////////////////////////////////////////////
    ///reference getter of weight layer
    /////////////////////////////////////////////////
    Matrice<Matrice<float>>& get_W(size_t);

    /////////////////////////////////////////////////
    ///reference getter of neuronal layer
    /////////////////////////////////////////////////
    Matrice<float>& get_O(size_t);

    /////////////////////////////////////////////////
    ///reference getter of biais layer
    /////////////////////////////////////////////////
    Matrice<float>& get_B(size_t);

    /////////////////////////////////////////////////
    ///fix data getter of weight layer
    /////////////////////////////////////////////////
    std::vector<Matrice<Matrice<float>>> Cget_W(void) const noexcept;

    /////////////////////////////////////////////////
    ///fix data getter of neuronal layer
    /////////////////////////////////////////////////
    std::vector<Matrice<float>> Cget_O(void) const noexcept;

    /////////////////////////////////////////////////
    ///fix data getter of biais layer
    /////////////////////////////////////////////////
    std::vector<Matrice<float>> Cget_B(void) const noexcept;

    /////////////////////////////////////////////////
    ///clear data equi reset
    /////////////////////////////////////////////////
    void clear(void);

    /////////////////////////////////////////////////
    ///clear error stat
    /////////////////////////////////////////////////
    void clear_error(void);

    /////////////////////////////////////////////////
    ///export data
    /////////////////////////////////////////////////
    bool save_as(std::string const &);

    /////////////////////////////////////////////////
    ///import data
    /////////////////////////////////////////////////
    bool import(std::string const &);

    /////////////////////////////////////////////////
    ///check if there is not error
    /////////////////////////////////////////////////
    bool good(void);

    /////////////////////////////////////////////////
    ///getter of error
    /////////////////////////////////////////////////
    rnl_error get_error()const noexcept;

    /////////////////////////////////////////////////
    ///set input values
    /////////////////////////////////////////////////
    bool set_in(std::vector<float> const &);

    /////////////////////////////////////////////////
    ///get output value
    /////////////////////////////////////////////////
    float get_out(size_t __i__);

    /////////////////////////////////////////////////
    ///get size of neuronal layer
    /////////////////////////////////////////////////
    std::vector<Matrice<float>>::size_type O_size(void) const noexcept;

    /////////////////////////////////////////////////
    ///get size of weight layer
    /////////////////////////////////////////////////
    std::vector<Matrice<Matrice<float>>>::size_type W_size(void) const noexcept;

    /////////////////////////////////////////////////
    ///get size of biais layer
    /////////////////////////////////////////////////
    std::vector<Matrice<float>>::size_type B_size(void) const noexcept;

    /**--static--**/
    /////////////////////////////////////////////////
    ///initialize neuronal layer
    /////////////////////////////////////////////////
    template<typename __T__> static Matrice<__T__> Init_O(size_t __n__)
    {
        return Matrice<__T__>(std::vector<__T__>(__n__,0));
    }

    /////////////////////////////////////////////////
    ///initialize biais layer
    /////////////////////////////////////////////////
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

    /////////////////////////////////////////////////
    ///initialize weight layer
    /////////////////////////////////////////////////
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

    /////////////////////////////////////////////////
    ///check free memory
    /////////////////////////////////////////////////
    inline void memory_check(size_t) throw(std::string);

    /////////////////////////////////////////////////
    ///data
    /////////////////////////////////////////////////
    std::vector<Matrice<float>> _O_,_B_;
    std::vector<Matrice<Matrice<float>>> _W_;

    /////////////////////////////////////////////////
    ///error
    /////////////////////////////////////////////////
    rnl_error rnl_e;

};

#endif // RNL_TYPE_HPP_INCLUDED

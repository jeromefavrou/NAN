#ifndef MATRICE_HPP_INCLUDED
#define MATRICE_HPP_INCLUDED

#include <vector>
#include <iterator>

template <typename __T__> class Matrice
{
public:
    Matrice(void)
    {
    }
    Matrice(std::vector<__T__> __data__):_data_(__data__)
    {
    }
    Matrice(Matrice const & __cpy__):_data_(__cpy__.get_data())
    {
    }
    ~Matrice()
    {
    }

    inline Matrice operator=(Matrice const & __cpy__)
    {
        this->_data_=__cpy__.get_data();
        return *this;
    }

    inline Matrice operator=(__T__ const & __init__)
    {
        for(auto It=this->_data_.begin();It!=this->_data_.end();It++)
            *It=__init__;

       /*for(auto & It : this->_data_)
            It=__init__;*/

        return *this;
    }

    inline Matrice operator*=(Matrice const & __mult__)
    {
        auto It=this->_data_.begin();
        auto It2=__mult__.get_ptr_data().begin();

        for(;It!=this->_data_.end() && It2!=__mult__.get_ptr_data().end();It++,It2++)
            *It*=*It2;

        return *this;
    }

    inline Matrice operator*=(__T__ const & __mult__)
    {

        for(auto It=this->_data_.begin();It!=this->_data_.end();It++)
            *It*=__mult__;

        return *this;
    }

    inline Matrice operator+=(Matrice  const & __add__)
    {
        /*auto It=this->_data_.begin();
        auto It2=__add__.get_ptr_data().begin();

        for(;It!=this->_data_.end() && It2!=__add__.get_ptr_data().end();It++,It2++)
            *It+=*It2;*/

        for(auto i=0;i<__add__.size();i++)
            this->_data_[i]+=__add__.get_data()[i];

        return *this;
    }

    inline Matrice operator+=(__T__ const & __add__)
    {
        for(auto It=this->_data_.begin();It!=this->_data_.end();It++)
            *It+=__add__;

        return *this;
    }

    inline Matrice operator*(Matrice  & __mult__)
    {
        auto tmp=*this;
       /* auto It=tmp.get_ptr_data().begin();
        auto It2=__mult__.get_ptr_data().begin();

        for(;It!=tmp.get_ptr_data().end() && It2!=__mult__.get_ptr_data().end();It++,It2++)
            *It*=*It2;*/

        for(auto i=0;i<__mult__.size();i++)
            tmp[i]*=__mult__[i];

        return tmp;
    }

    inline Matrice operator*(__T__  const & __mult__)
    {
        auto tmp=*this;

        for(auto It=tmp.get_ptr_data().begin();It!=tmp.get_ptr_data().end();It++)
            *It*=__mult__;

        return tmp;
    }

    inline Matrice operator+(Matrice & __add__)
    {
        auto tmp=*this;
        auto It=tmp.get_ptr_data().begin();
        auto It2=__add__.get_ptr_data().begin();

        for(;It!=tmp.get_ptr_data().end() && It2!=__add__.get_ptr_data().end();It++,It2++)
            *It+=*It2;

        return tmp;
    }

    inline Matrice operator-(Matrice  & __sub__)
    {
        auto tmp=*this;
       /* auto It=tmp.get_ptr_data().begin();
        auto It2=__sub__.get_data().begin();

        for(;It!=tmp.get_ptr_data().end() && It2!=__sub__.get_data().end();It++,It2++)
            *It-=*It2;*/

        for(auto i=0;i<__sub__.size();i++)
            tmp[i]-=__sub__[i];

        return tmp;
    }

    inline Matrice operator+(__T__ const & __add__)
    {
        auto tmp=*this;

        for(auto It=tmp.get_ptr_data().begin();It!=tmp.end();It++)
            *It+=__add__;

        return tmp;
    }

    inline Matrice operator-(__T__ const & __sub__)
    {
        auto tmp=*this;

        for(auto It=tmp.get_ptr_data().begin();It!=tmp.end();It++)
            *It-=__sub__;

        return tmp;
    }
    inline __T__ & operator[](size_t __i__)
    {
        return this->_data_[__i__];
    }
    inline static __T__ sum(Matrice & __sum__)
    {
        __T__ tmp(0);

        /*for(auto It=__sum__.get_ptr_data().begin();It!=__sum__.get_ptr_data().end();It++)
            tmp+=*It;*/

        for(auto & sum : __sum__.get_ptr_data())
            tmp+=sum;

        return tmp;
    }

    inline size_t size()const noexcept
    {
        return this->_data_.size();
    }

    inline __T__ & at(size_t __i__)
    {
        return this->_data_.at(__i__);
    }

    inline std::vector<__T__> get_data()const noexcept
    {
        return this->_data_;
    }

    inline std::vector<__T__> & get_ptr_data()
    {
        return this->_data_;
    }

private:

    std::vector<__T__> _data_;


};

#endif // MATRICE_HPP_INCLUDED

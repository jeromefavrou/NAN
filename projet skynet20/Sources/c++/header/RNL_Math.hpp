#ifndef RNL_MATH_HPP_INCLUDED
#define RNL_MATH_HPP_INCLUDED

template <int I> inline double Factorielle()
{
    return I * Factorielle<I - 1>();
}
template <> inline double Factorielle<0>()
{
    return 1.0;
}

template <int N> inline double Puissance(double x)
{
    return x * Puissance<N - 1>(x);
}
template <> inline double Puissance<0>(double x)
{
    return 1.0;
}

template <int I> inline double Exp_(double x)
{
    return Exp_<I - 1>(x) + Puissance<I>(x) / Factorielle<I>();
}
template <> inline double Exp_<0>(double x)
{
    return 0.0;
}

template <int N> inline double Exponentielle(double x)
{
    return x < 0.0 ? 1.0 / Exp_<N>(-x) : Exp_<N>(x);
}

#endif // RNL_MATH_HPP_INCLUDED
